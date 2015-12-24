// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2015 The Peercoin developers
// Copyright (c) 2014-2015 The Paycoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "main.h"
#include "net.h"
#include "init.h"
#include "ui_interface.h"
#include "base58.h"
#include "bitcoinrpc.h"

#undef printf
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/filesystem/fstream.hpp>
typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> SSLStream;

#define printf OutputDebugStringF

using namespace std;
using namespace boost;
using namespace boost::asio;
using namespace json_spirit;

void ThreadRPCServer2(void* parg);

// Key used by getwork/getblocktemplate miners.
// Allocated in StartRPCThreads, free'd in StopRPCThreads
CReserveKey* pMiningKey = NULL;

static std::string strRPCUserColonPass;

Object JSONRPCError(int code, const string& message)
{
    Object error;
    error.push_back(Pair("code", code));
    error.push_back(Pair("message", message));
    return error;
}

int64 AmountFromValue(const Value& value)
{
    double dAmount = value.get_real();
    if (dAmount <= 0.0 || dAmount > MAX_MONEY)
        throw JSONRPCError(-3, "Invalid amount");
    int64 nAmount = roundint64(dAmount * COIN);
    if (!MoneyRange(nAmount))
        throw JSONRPCError(-3, "Invalid amount");
    return nAmount;
}

Value ValueFromAmount(int64 amount)
{
    return (double)amount / (double)COIN;
}

string HexBits(unsigned int nBits)
{
    union {
        int32_t nBits;
        char cBits[4];
    } uBits;
    uBits.nBits = htonl((int32_t)nBits);
    return HexStr(BEGIN(uBits.cBits), END(uBits.cBits));
}

///
/// Note: This interface may still be subject to change.
///

string CRPCTable::help(string strCommand) const
{
    string strRet;
    set<rpcfn_type> setDone;
    for (map<string, const CRPCCommand*>::const_iterator mi = mapCommands.begin(); mi != mapCommands.end(); ++mi)
    {
        const CRPCCommand *pcmd = mi->second;
        string strMethod = mi->first;
        // We already filter duplicates, but these deprecated screw up the sort order
        if (strMethod.find("label") != string::npos)
            continue;
        if (strCommand != "" && strMethod != strCommand)
            continue;
        try
        {
            Array params;
            rpcfn_type pfn = pcmd->actor;
            if (setDone.insert(pfn).second)
                (*pfn)(params, true);
        }
        catch (std::exception& e)
        {
            // Help text is returned in an exception
            string strHelp = string(e.what());
            if (strCommand == "")
                if (strHelp.find('\n') != string::npos)
                    strHelp = strHelp.substr(0, strHelp.find('\n'));
            strRet += strHelp + "\n";
        }
    }
    if (strRet == "")
        strRet = strprintf("help: unknown command: %s\n", strCommand.c_str());
    strRet = strRet.substr(0,strRet.size()-1);
    return strRet;
}

Value help(const Array& params, bool fHelp)
{
    if (fHelp || params.size() > 1)
        throw runtime_error(
            "help [command]\n"
            "List commands, or get help for a command.");

    string strCommand;
    if (params.size() > 0)
        strCommand = params[0].get_str();

    return tableRPC.help(strCommand);
}


Value stop(const Array& params, bool fHelp)
{
    if (fHelp || params.size() != 0)
        throw runtime_error(
            "stop\n"
            "Stop Paycoin server.");
    // Shutdown will take long enough that the response should get back
    StartShutdown();
    return "Paycoin server stopping";
}

Value getgenerate(const Array& params, bool fHelp)
{
    if (fHelp || params.size() != 0)
        throw runtime_error(
            "getgenerate\n"
            "Returns true or false.");

    return GetBoolArg("-gen");
}

Value setgenerate(const Array& params, bool fHelp)
{
    if (fHelp || params.size() < 1 || params.size() > 2)
        throw runtime_error(
            "setgenerate <generate> [genproclimit]\n"
            "<generate> is true or false to turn generation on or off.\n"
            "Generation is limited to [genproclimit] processors, -1 is unlimited.");

    bool fGenerate = true;
    if (params.size() > 0)
        fGenerate = params[0].get_bool();

    if (params.size() > 1)
    {
        int nGenProcLimit = params[1].get_int();
        mapArgs["-genproclimit"] = itostr(nGenProcLimit);
        if (nGenProcLimit == 0)
            fGenerate = false;
    }
    mapArgs["-gen"] = (fGenerate ? "1" : "0");

    GenerateBitcoins(fGenerate, pwalletMain);
    return Value::null;
}

Value gethashespersec(const Array& params, bool fHelp)
{
    if (fHelp || params.size() != 0)
        throw runtime_error(
            "gethashespersec\n"
            "Returns a recent hashes per second performance measurement while generating.");

    if (GetTimeMillis() - nHPSTimerStart > 8000)
        return (boost::int64_t)0;
    return (boost::int64_t)dHashesPerSec;
}

// paycoin: get network Gh/s estimate
Value getnetworkghps(const Array& params, bool fHelp)
{
    if (fHelp || params.size() != 0)
        throw runtime_error(
            "getnetworkghps\n"
            "Returns a recent Ghash/second network mining estimate.");

    if (pindexBest != NULL && pindexBest->nTime > POW_END_TIME)
        return (double)0.00f;

    int64 nTargetSpacingWorkMin = 30;
    int64 nTargetSpacingWork = nTargetSpacingWorkMin;
    int64 nInterval = 72;
    CBlockIndex* pindex = pindexGenesisBlock;
    CBlockIndex* pindexPrevWork = pindexGenesisBlock;
    while (pindex)
    {
        // Exponential moving average of recent proof-of-work block spacing
        if (pindex->IsProofOfWork())
        {
            int64 nActualSpacingWork = pindex->GetBlockTime() - pindexPrevWork->GetBlockTime();
            nTargetSpacingWork = ((nInterval - 1) * nTargetSpacingWork + nActualSpacingWork + nActualSpacingWork) / (nInterval + 1);
            nTargetSpacingWork = max(nTargetSpacingWork, nTargetSpacingWorkMin);
            pindexPrevWork = pindex;
        }
        pindex = pindex->pnext;
    }
    double dNetworkGhps = GetDifficulty() * 4.294967296 / nTargetSpacingWork;
    return dNetworkGhps;
}

double GetPoSKernelPS2(const CBlockIndex* pindex)
{
    int nPoSInterval = 72;
    double dStakeKernelsTriedAvg = 0;
    int nStakesHandled = 0, nStakesTime = 0;

    const CBlockIndex* pindexPrevStake = NULL;

    while (pindex && nStakesHandled < nPoSInterval)
    {
        if (pindex->IsProofOfStake())
        {
            dStakeKernelsTriedAvg += GetDifficulty(pindex) * 4294967296.0;
            nStakesTime += pindexPrevStake ? (pindexPrevStake->nTime - pindex->nTime) : 0;
            pindexPrevStake = pindex;
            nStakesHandled++;
        }

        pindex = pindex->pprev;
    }

    return nStakesTime ? dStakeKernelsTriedAvg / nStakesTime : 0;
}

double GetPoSKernelPS() {
    return GetPoSKernelPS2(pindexBest);
}

Value getmininginfo(const Array& params, bool fHelp)
{
    if (fHelp || params.size() != 0)
        throw runtime_error(
            "getmininginfo\n"
            "Returns an object containing mining-related information.");

    uint64 nMinWeight = 0, nMaxWeight = 0, nWeight = 0;
    pwalletMain->GetStakeWeight(*pwalletMain, nMinWeight, nMaxWeight, nWeight);

    Object obj, weight;

    obj.push_back(Pair("blocks",        (int)nBestHeight));
    obj.push_back(Pair("currentblocksize",(uint64_t)nLastBlockSize));
    obj.push_back(Pair("currentblocktx",(uint64_t)nLastBlockTx));
    obj.push_back(Pair("difficulty",    (double)GetDifficulty()));
    obj.push_back(Pair("errors",        GetWarnings("statusbar")));
    obj.push_back(Pair("generate",      GetBoolArg("-gen")));
    obj.push_back(Pair("genproclimit",  (int)GetArg("-genproclimit", -1)));
    obj.push_back(Pair("hashespersec",  gethashespersec(params, false)));
    obj.push_back(Pair("netstakeweight", GetPoSKernelPS()));
    weight.push_back(Pair("minimum",    (uint64_t)nMinWeight));
    weight.push_back(Pair("maximum",    (uint64_t)nMaxWeight));
    weight.push_back(Pair("combined",  (uint64_t)nWeight));
    obj.push_back(Pair("stakeweight", weight));
    obj.push_back(Pair("networkghps",   getnetworkghps(params, false)));
    obj.push_back(Pair("pooledtx",      (uint64_t)mempool.size()));
    obj.push_back(Pair("testnet",       fTestNet));
    return obj;
}

Value getwork(const Array& params, bool fHelp)
{
    if (fHelp || params.size() > 1)
        throw runtime_error(
            "getwork [data]\n"
            "If [data] is not specified, returns formatted hash data to work on:\n"
            "  \"midstate\" : precomputed hash state after hashing the first half of the data (DEPRECATED)\n" // deprecated
            "  \"data\" : block data\n"
            "  \"hash1\" : formatted hash buffer for second hash (DEPRECATED)\n" // deprecated
            "  \"target\" : little endian hash target\n"
            "If [data] is specified, tries to solve the block and returns true if it was successful.");

    if (vNodes.empty())
        throw JSONRPCError(-9, "Paycoin is not connected!");

    if (IsInitialBlockDownload())
        throw JSONRPCError(-10, "Paycoin is downloading blocks...");

    if (pindexBest != NULL && pindexBest->nTime > POW_END_TIME)
        throw JSONRPCError(-10, "Paycoin is currently on pure PoS state");


    typedef map<uint256, pair<CBlock*, CScript> > mapNewBlock_t;
    static mapNewBlock_t mapNewBlock;
    static vector<CBlock*> vNewBlock;

    if (params.size() == 0)
    {
        // Update block
        static unsigned int nTransactionsUpdatedLast;
        static CBlockIndex* pindexPrev;
        static int64 nStart;
        static CBlock* pblock;
        if (pindexPrev != pindexBest ||
            (nTransactionsUpdated != nTransactionsUpdatedLast && GetTime() - nStart > 60))
        {
            if (pindexPrev != pindexBest)
            {
                // Deallocate old blocks since they're obsolete now
                mapNewBlock.clear();
                BOOST_FOREACH(CBlock* pblock, vNewBlock)
                    delete pblock;
                vNewBlock.clear();
            }

            // Clear pindexPrev so future getworks make a new block, despite any failures from here on
            pindexPrev = NULL;

            // Store the pindexBest used before CreateNewBlock, to avoid races
            nTransactionsUpdatedLast = nTransactionsUpdated;
            CBlockIndex* pindexPrevNew = pindexBest;
            nStart = GetTime();

            // Create new block
            pblock = CreateNewBlock(*pMiningKey, pwalletMain);
            if (!pblock)
                throw JSONRPCError(-7, "Out of memory");
            vNewBlock.push_back(pblock);

            // Need to update only after we know CreateNewBlock succeeded
            pindexPrev = pindexPrevNew;
        }

        // Update nTime
        pblock->UpdateTime(pindexPrev);
        pblock->nNonce = 0;

        // Update nExtraNonce
        static unsigned int nExtraNonce = 0;
        IncrementExtraNonce(pblock, pindexPrev, nExtraNonce);

        // Save
        mapNewBlock[pblock->hashMerkleRoot] = make_pair(pblock, pblock->vtx[0].vin[0].scriptSig);

        // Prebuild hash buffers
        char pmidstate[32];
        char pdata[128];
        char phash1[64];
        FormatHashBuffers(pblock, pmidstate, pdata, phash1);

        uint256 hashTarget = CBigNum().SetCompact(pblock->nBits).getuint256();

        Object result;
        result.push_back(Pair("midstate", HexStr(BEGIN(pmidstate), END(pmidstate)))); // deprecated
        result.push_back(Pair("data",     HexStr(BEGIN(pdata), END(pdata))));
        result.push_back(Pair("hash1",    HexStr(BEGIN(phash1), END(phash1)))); // deprecated
        result.push_back(Pair("target",   HexStr(BEGIN(hashTarget), END(hashTarget))));
        return result;
    }
    else
    {
        // Parse parameters
        vector<unsigned char> vchData = ParseHex(params[0].get_str());
        if (vchData.size() != 128)
            throw JSONRPCError(-8, "Invalid parameter");
        CBlock* pdata = (CBlock*)&vchData[0];

        // Byte reverse
        for (int i = 0; i < 128/4; i++)
            ((unsigned int*)pdata)[i] = ByteReverse(((unsigned int*)pdata)[i]);

        // Get saved block
        if (!mapNewBlock.count(pdata->hashMerkleRoot))
            return false;
        CBlock* pblock = mapNewBlock[pdata->hashMerkleRoot].first;

        pblock->nTime = pdata->nTime;
        pblock->nNonce = pdata->nNonce;
        pblock->vtx[0].vin[0].scriptSig = mapNewBlock[pdata->hashMerkleRoot].second;
        pblock->hashMerkleRoot = pblock->BuildMerkleTree();

        assert(pwalletMain != NULL);
        if (!pblock->SignBlock(*pwalletMain))
            throw JSONRPCError(-100, "Unable to sign block, wallet locked?");

        return CheckWork(pblock, *pwalletMain, *pMiningKey);
    }
}

Value getblocktemplate(const Array& params, bool fHelp)
{
    if (fHelp || params.size() > 1)
        throw runtime_error(
            "getblocktemplate [params]\n"
            "Returns data needed to construct a block to work on:\n"
            "  \"version\" : block version\n"
            "  \"previousblockhash\" : hash of current highest block\n"
            "  \"transactions\" : contents of non-coinbase transactions that should be included in the next block\n"
            "  \"coinbaseaux\" : data that should be included in coinbase\n"
            "  \"coinbasevalue\" : maximum allowable input to coinbase transaction, including the generation award and transaction fees\n"
            "  \"target\" : hash target\n"
            "  \"mintime\" : minimum timestamp appropriate for next block\n"
            "  \"curtime\" : current timestamp\n"
            "  \"mutable\" : list of ways the block template may be changed\n"
            "  \"noncerange\" : range of valid nonces\n"
            "  \"sigoplimit\" : limit of sigops in blocks\n"
            "  \"sizelimit\" : limit of block size\n"
            "  \"bits\" : compressed target of next block\n"
            "  \"height\" : height of the next block\n"
            "See https://en.bitcoin.it/wiki/BIP_0022 for full specification.");

    std::string strMode = "template";
    if (params.size() > 0)
    {
        const Object& oparam = params[0].get_obj();
        const Value& modeval = find_value(oparam, "mode");
        if (modeval.type() == str_type)
            strMode = modeval.get_str();
        else if (modeval.type() == null_type)
        {
            /* Do nothing */
        }
        else
            throw JSONRPCError(-8, "Invalid mode");
    }

    if (strMode != "template")
        throw JSONRPCError(-8, "Invalid mode");

    {
        if (vNodes.empty())
            throw JSONRPCError(-9, "Paycoin is not connected!");

        if (IsInitialBlockDownload())
            throw JSONRPCError(-10, "Paycoin is downloading blocks...");

        if (pindexBest != NULL && pindexBest->nTime > POW_END_TIME)
            throw JSONRPCError(-10, "Paycoin is currently on pure PoS state");

        // Update block
        static unsigned int nTransactionsUpdatedLast;
        static CBlockIndex* pindexPrev;
        static int64 nStart;
        static CBlock* pblock;
        if (pindexPrev != pindexBest ||
            (nTransactionsUpdated != nTransactionsUpdatedLast && GetTime() - nStart > 5))
        {
            // Clear pindexPrev so future calls make a new block, despite any failures from here on
            pindexPrev = NULL;

            // Store the pindexBest used before CreateNewBlock, to avoid races
            nTransactionsUpdatedLast = nTransactionsUpdated;
            CBlockIndex* pindexPrevNew = pindexBest;
            nStart = GetTime();

            // Create new block
            if(pblock)
            {
                delete pblock;
                pblock = NULL;
            }
            pblock = CreateNewBlock(*pMiningKey, pwalletMain);
            if (!pblock)
                throw JSONRPCError(-7, "Out of memory");

            // Need to update only after we know CreateNewBlock succeeded
            pindexPrev = pindexPrevNew;
        }

        // Update nTime
        pblock->UpdateTime(pindexPrev);
        pblock->nNonce = 0;

        Array transactions;
        map<uint256, int64_t> setTxIndex;
        int i = 0;
        CTxDB txdb("r");
        BOOST_FOREACH (CTransaction& tx, pblock->vtx)
        {
            uint256 txHash = tx.GetHash();
            setTxIndex[txHash] = i++;

            if (tx.IsCoinBase())
                continue;

            Object entry;

            CDataStream ssTx(SER_NETWORK, PROTOCOL_VERSION);
            ssTx << tx;
            entry.push_back(Pair("data", HexStr(ssTx.begin(), ssTx.end())));

            entry.push_back(Pair("hash", txHash.GetHex()));

            MapPrevTx mapInputs;
            map<uint256, CTxIndex> mapUnused;
            bool fInvalid = false;
            if (tx.FetchInputs(txdb, mapUnused, false, false, mapInputs, fInvalid))
            {
                entry.push_back(Pair("fee", (int64_t)(tx.GetValueIn(mapInputs) - tx.GetValueOut())));

                Array deps;
                BOOST_FOREACH (MapPrevTx::value_type& inp, mapInputs)
                {
                    if (setTxIndex.count(inp.first))
                        deps.push_back(setTxIndex[inp.first]);
                }
                entry.push_back(Pair("depends", deps));

                int64_t nSigOps = tx.GetLegacySigOpCount();
                nSigOps += tx.GetP2SHSigOpCount(mapInputs);
                entry.push_back(Pair("sigops", nSigOps));
            }

            transactions.push_back(entry);
        }

        Object aux;
        aux.push_back(Pair("flags", HexStr(COINBASE_FLAGS.begin(), COINBASE_FLAGS.end())));

        uint256 hashTarget = CBigNum().SetCompact(pblock->nBits).getuint256();

        static Array aMutable;
        if (aMutable.empty())
        {
            aMutable.push_back("time");
            aMutable.push_back("transactions");
            aMutable.push_back("prevblock");
        }

        Object result;
        result.push_back(Pair("version", pblock->nVersion));
        result.push_back(Pair("previousblockhash", pblock->hashPrevBlock.GetHex()));
        result.push_back(Pair("transactions", transactions));
        result.push_back(Pair("coinbaseaux", aux));
        result.push_back(Pair("coinbasevalue", (int64_t)pblock->vtx[0].vout[0].nValue));
        result.push_back(Pair("target", hashTarget.GetHex()));
        result.push_back(Pair("mintime", (int64_t)pindexPrev->GetMedianTimePast()+1));
        result.push_back(Pair("mutable", aMutable));
        result.push_back(Pair("noncerange", "00000000ffffffff"));
        result.push_back(Pair("sigoplimit", (int64_t)MAX_BLOCK_SIGOPS));
        result.push_back(Pair("sizelimit", (int64_t)MAX_BLOCK_SIZE));
        result.push_back(Pair("curtime", (int64_t)pblock->nTime));
        result.push_back(Pair("bits", HexBits(pblock->nBits)));
        result.push_back(Pair("height", (int64_t)(pindexPrev->nHeight+1)));

        return result;
    }
}

Value submitblock(const Array& params, bool fHelp)
{
    if (fHelp || params.size() < 1 || params.size() > 2)
        throw runtime_error(
            "submitblock <hex data> [optional-params-obj]\n"
            "[optional-params-obj] parameter is currently ignored.\n"
            "Attempts to submit new block to network.\n"
            "See https://en.bitcoin.it/wiki/BIP_0022 for full specification.");

    vector<unsigned char> blockData(ParseHex(params[0].get_str()));
    CDataStream ssBlock(blockData, SER_NETWORK, PROTOCOL_VERSION);
    CBlock block;
    try {
        ssBlock >> block;
    }
    catch (std::exception &e) {
        throw JSONRPCError(-22, "Block decode failed");
    }

    // Paycoin: sign block
    if (!block.SignBlock(*pwalletMain))
        throw JSONRPCError(-100, "Unable to sign block, wallet locked?");

    bool fAccepted = CheckWork(&block, *pwalletMain, *pMiningKey);
    if (!fAccepted)
        return "rejected"; // TODO: report validation state

    return Value::null;
}

Value gettxout(const Array& params, bool fHelp)
{
    if (fHelp || params.size() < 2 || params.size() > 3)
        throw runtime_error(
            "gettxout \"txid\" n ( includemempool )\n"
            "\nReturns details about an unspent transaction output.\n"
            "\nArguments:\n"
            "1. \"txid\" (string, required) The transaction id\n"
            "2. n (numeric, required) vout value\n"
            "3. includemempool (boolean, optional) Whether to included the mem pool\n"
            "\nResult:\n"
            "{\n"
            " \"bestblock\" : \"hash\", (string) the block hash\n"
            " \"confirmations\" : n, (numeric) The number of confirmations\n"
            " \"value\" : x.xxx, (numeric) The transaction value in btc\n"
            " \"scriptPubKey\" : { (json object)\n"
            " \"asm\" : \"code\", (string) \n"
            " \"hex\" : \"hex\", (string) \n"
            " \"reqSigs\" : n, (numeric) Number of required signatures\n"
            " \"type\" : \"pubkeyhash\", (string) The type, eg pubkeyhash\n"
            " \"addresses\" : [ (array of string) array of bitcoin addresses\n"
            " \"bitcoinaddress\" (string) bitcoin address\n"
            " ,...\n"
            " ]\n"
            " },\n"
            " \"version\" : n, (numeric) The version\n"
            " \"coinbase\" : true|false (boolean) Coinbase or not\n"
            "}\n");

    Object ret;

    std::string strHash = params[0].get_str();
    uint256 hash(strHash);
    int n = params[1].get_int();
    bool fMempool = true;
    if (params.size() > 2)
        fMempool = params[2].get_bool();

    if (n < 0)
        return Value::null;

    COutPoint outpoint = COutPoint(hash, n);
    bool fFound = false, fInMempool = false;
    uint256 hashBlock;
    int nConfirmations = 0;
    CTransaction tx;

    if(fMempool)
    {
        LOCK(mempool.cs);
        if (mempool.mapNextTx.count(outpoint))
            return Value::null;
        if (mempool.exists(hash))
        {
            tx = mempool.lookup(hash);
            if (n >= tx.vout.size())
                return Value::null;
            fFound = true;
            fInMempool = true;
        }
    }

    if(!fFound)
    {
        CTxDB txdb("r");
        CTxIndex txindex;
        if (!txdb.ReadTxIndex(hash, txindex))
            return Value::null;
        if (n >= txindex.vSpent.size())
            return Value::null;
        if (!txindex.vSpent[n].IsNull())
            return Value::null;
        if (!tx.ReadFromDisk(txindex.pos))
            return Value::null;
        CBlock block;
        if (block.ReadFromDisk(txindex.pos.nFile, txindex.pos.nBlockPos, false))
        {
            hashBlock = block.GetHash();
            map<uint256, CBlockIndex*>::iterator mi = mapBlockIndex.find(hashBlock);
            if (mi != mapBlockIndex.end() && (*mi).second)
            {
                CBlockIndex* pindex = (*mi).second;
                if (pindex->IsInMainChain())
                {
                    nConfirmations = 1 + nBestHeight - pindex->nHeight;
                }
            }
        }
    }

    ret.push_back(Pair("bestblock", fInMempool ? "" : hashBlock.GetHex()));
    ret.push_back(Pair("confirmations", nConfirmations));
    ret.push_back(Pair("value", ValueFromAmount(tx.vout[n].nValue)));
    ret.push_back(Pair("version", tx.nVersion));
    Object o;
    ScriptPubKeyToJSON(tx.vout[n].scriptPubKey, o);
    ret.push_back(Pair("scriptPubKey", o));
    ret.push_back(Pair("coinbase", tx.IsCoinBase()));
    ret.push_back(Pair("coinstake", tx.IsCoinStake()));

    return ret;
}

//
// Call Table
//

static const CRPCCommand vRPCCommands[] =
{ //  name                      function                 safe mode?
  //  ------------------------  -----------------------  ----------
    { "help",                   &help,                   true },
    { "stop",                   &stop,                   true },
    { "getblockcount",          &getblockcount,          true },
    { "listaddressbook",        &listaddressbook,        false },
    { "getconnectioncount",     &getconnectioncount,     true },
    { "getpeerinfo",            &getpeerinfo,            true },
    { "getdifficulty",          &getdifficulty,          true },
    { "getgenerate",            &getgenerate,            true },
    { "setgenerate",            &setgenerate,            true },
    { "gethashespersec",        &gethashespersec,        true },
    { "getnetworkghps",         &getnetworkghps,         true },
    { "getinfo",                &getinfo,                true },
    { "getmininginfo",          &getmininginfo,          true },
    { "getnewaddress",          &getnewaddress,          true },
    { "getaccountaddress",      &getaccountaddress,      true },
    { "setaccount",             &setaccount,             true },
    { "getaccount",             &getaccount,             false },
    { "getaddressesbyaccount",  &getaddressesbyaccount,  true },
    { "sendtoaddress",          &sendtoaddress,          false },
    { "getreceivedbyaddress",   &getreceivedbyaddress,   false },
    { "getreceivedbyaccount",   &getreceivedbyaccount,   false },
    { "listminting",            &listminting,            false },
    { "listreceivedbyaddress",  &listreceivedbyaddress,  false },
    { "listreceivedbyaccount",  &listreceivedbyaccount,  false },
    { "backupwallet",           &backupwallet,           true },
    { "keypoolrefill",          &keypoolrefill,          true },
    { "walletpassphrase",       &walletpassphrase,       true },
    { "walletpassphrasechange", &walletpassphrasechange, false },
    { "walletlock",             &walletlock,             true },
    { "encryptwallet",          &encryptwallet,          false },
    { "validateaddress",        &validateaddress,        true },
    { "getbalance",             &getbalance,             false },
    { "move",                   &movecmd,                false },
    { "sendfrom",               &sendfrom,               false },
    { "sendmany",               &sendmany,               false },
    { "addmultisigaddress",     &addmultisigaddress,     false },
    { "createmultisig",         &createmultisig,         true },
    { "getblock",               &getblock,               false },
    { "getblockhash",           &getblockhash,           false },
    { "gettransaction",         &gettransaction,         false },
    { "listtransactions",       &listtransactions,       false },
    { "listaddressgroupings",   &listaddressgroupings,   false },
    { "signmessage",            &signmessage,            false },
    { "verifymessage",          &verifymessage,          false },
    { "getwork",                &getwork,                true },
    { "listaccounts",           &listaccounts,           false },
    { "settxfee",               &settxfee,               false },
    { "getblocktemplate",       &getblocktemplate,       true },
    { "submitblock",            &submitblock,            false },
    { "listsinceblock",         &listsinceblock,         false },
    { "dumpprivkey",            &dumpprivkey,            false },
    { "importprivkey",          &importprivkey,          false },
    { "getcheckpoint",          &getcheckpoint,          true },
    { "reservebalance",         &reservebalance,         false},
    { "checkwallet",            &checkwallet,            false},
    { "repairwallet",           &repairwallet,           false},
    { "makekeypair",            &makekeypair,            false},
    { "sendalert",              &sendalert,              false},
    { "listunspent",            &listunspent,            false},
    { "getrawtransaction",      &getrawtransaction,      false},
    { "createrawtransaction",   &createrawtransaction,   false},
    { "decoderawtransaction",   &decoderawtransaction,   false},
    { "signrawtransaction",     &signrawtransaction,     false},
    { "sendrawtransaction",     &sendrawtransaction,     false},
    { "gettxout",               &gettxout,               true },
    { "getrawmempool",          &getrawmempool,          true },
    { "clearorphans",           &clearorphans,           true },
    { "getscrapeaddress",       &getscrapeaddress,       true },
    { "listscrapeaddresses",    &listscrapeaddresses,    true },
    { "setscrapeaddress",       &setscrapeaddress,       true },
    { "deletescrapeaddress",    &deletescrapeaddress,    true },
    { "listmicroprimedata",     &listmicroprimedata,     true }
};

CRPCTable::CRPCTable()
{
    unsigned int vcidx;
    for (vcidx = 0; vcidx < (sizeof(vRPCCommands) / sizeof(vRPCCommands[0])); vcidx++)
    {
        const CRPCCommand *pcmd;

        pcmd = &vRPCCommands[vcidx];
        mapCommands[pcmd->name] = pcmd;
    }
}

const CRPCCommand *CRPCTable::operator[](string name) const
{
    map<string, const CRPCCommand*>::const_iterator it = mapCommands.find(name);
    if (it == mapCommands.end())
        return NULL;
    return (*it).second;
}

//
// HTTP protocol
//
// This ain't Apache.  We're just using HTTP header for the length field
// and to be compatible with other JSON-RPC implementations.
//

string HTTPPost(const string& strMsg, const map<string,string>& mapRequestHeaders)
{
    ostringstream s;
    s << "POST / HTTP/1.1\r\n"
      << "User-Agent: paycoin-json-rpc/" << FormatFullVersion() << "\r\n"
      << "Host: 127.0.0.1\r\n"
      << "Content-Type: application/json\r\n"
      << "Content-Length: " << strMsg.size() << "\r\n"
      << "Connection: close\r\n"
      << "Accept: application/json\r\n";
    BOOST_FOREACH(const PAIRTYPE(string, string)& item, mapRequestHeaders)
        s << item.first << ": " << item.second << "\r\n";
    s << "\r\n" << strMsg;

    return s.str();
}

string rfc1123Time()
{
    char buffer[64];
    time_t now;
    time(&now);
    struct tm* now_gmt = gmtime(&now);
    string locale(setlocale(LC_TIME, NULL));
    setlocale(LC_TIME, "C"); // we want POSIX (aka "C") weekday/month strings
    strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S +0000", now_gmt);
    setlocale(LC_TIME, locale.c_str());
    return string(buffer);
}

static string HTTPReply(int nStatus, const string& strMsg)
{
    if (nStatus == 401)
        return strprintf("HTTP/1.0 401 Authorization Required\r\n"
            "Date: %s\r\n"
            "Server: paycoin-json-rpc/%s\r\n"
            "WWW-Authenticate: Basic realm=\"jsonrpc\"\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 296\r\n"
            "\r\n"
            "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"\r\n"
            "\"http://www.w3.org/TR/1999/REC-html401-19991224/loose.dtd\">\r\n"
            "<HTML>\r\n"
            "<HEAD>\r\n"
            "<TITLE>Error</TITLE>\r\n"
            "<META HTTP-EQUIV='Content-Type' CONTENT='text/html; charset=ISO-8859-1'>\r\n"
            "</HEAD>\r\n"
            "<BODY><H1>401 Unauthorized.</H1></BODY>\r\n"
            "</HTML>\r\n", rfc1123Time().c_str(), FormatFullVersion().c_str());
    const char *cStatus;
         if (nStatus == 200) cStatus = "OK";
    else if (nStatus == 400) cStatus = "Bad Request";
    else if (nStatus == 403) cStatus = "Forbidden";
    else if (nStatus == 404) cStatus = "Not Found";
    else if (nStatus == 500) cStatus = "Internal Server Error";
    else cStatus = "";
    return strprintf(
            "HTTP/1.1 %d %s\r\n"
            "Date: %s\r\n"
            "Connection: close\r\n"
            "Content-Length: %d\r\n"
            "Content-Type: application/json\r\n"
            "Server: paycoin-json-rpc/%s\r\n"
            "\r\n"
            "%s",
        nStatus,
        cStatus,
        rfc1123Time().c_str(),
        strMsg.size(),
        FormatFullVersion().c_str(),
        strMsg.c_str());
}

int ReadHTTPStatus(std::basic_istream<char>& stream)
{
    string str;
    getline(stream, str);
    vector<string> vWords;
    boost::split(vWords, str, boost::is_any_of(" "));
    if (vWords.size() < 2)
        return 500;
    return atoi(vWords[1].c_str());
}

int ReadHTTPHeader(std::basic_istream<char>& stream, map<string, string>& mapHeadersRet)
{
    int nLen = 0;
    for (;;)
    {
        string str;
        std::getline(stream, str);
        if (str.empty() || str == "\r")
            break;
        string::size_type nColon = str.find(":");
        if (nColon != string::npos)
        {
            string strHeader = str.substr(0, nColon);
            boost::trim(strHeader);
            boost::to_lower(strHeader);
            string strValue = str.substr(nColon+1);
            boost::trim(strValue);
            mapHeadersRet[strHeader] = strValue;
            if (strHeader == "content-length")
                nLen = atoi(strValue.c_str());
        }
    }
    return nLen;
}

int ReadHTTP(std::basic_istream<char>& stream, map<string, string>& mapHeadersRet, string& strMessageRet)
{
    mapHeadersRet.clear();
    strMessageRet = "";

    // Read status
    int nStatus = ReadHTTPStatus(stream);

    // Read header
    int nLen = ReadHTTPHeader(stream, mapHeadersRet);
    if (nLen < 0 || nLen > (int)MAX_SIZE)
        return 500;

    // Read message
    if (nLen > 0)
    {
        vector<char> vch(nLen);
        stream.read(&vch[0], nLen);
        strMessageRet = string(vch.begin(), vch.end());
    }

    return nStatus;
}

bool HTTPAuthorized(map<string, string>& mapHeaders)
{
    string strAuth = mapHeaders["authorization"];
    if (strAuth.substr(0,6) != "Basic ")
        return false;
    string strUserPass64 = strAuth.substr(6); boost::trim(strUserPass64);
    string strUserPass = DecodeBase64(strUserPass64);
    return strUserPass == strRPCUserColonPass;
}

//
// JSON-RPC protocol.  Bitcoin speaks version 1.0 for maximum compatibility,
// but uses JSON-RPC 1.1/2.0 standards for parts of the 1.0 standard that were
// unspecified (HTTP errors and contents of 'error').
//
// 1.0 spec: http://json-rpc.org/wiki/specification
// 1.2 spec: http://groups.google.com/group/json-rpc/web/json-rpc-over-http
// http://www.codeproject.com/KB/recipes/JSON_Spirit.aspx
//

string JSONRPCRequest(const string& strMethod, const Array& params, const Value& id)
{
    Object request;
    request.push_back(Pair("method", strMethod));
    request.push_back(Pair("params", params));
    request.push_back(Pair("id", id));
    return write_string(Value(request), false) + "\n";
}

Object JSONRPCReplyObj(const Value& result, const Value& error, const Value& id)
{
    Object reply;
    if (error.type() != null_type)
        reply.push_back(Pair("result", Value::null));
    else
        reply.push_back(Pair("result", result));
    reply.push_back(Pair("error", error));
    reply.push_back(Pair("id", id));
    return reply;
}

string JSONRPCReply(const Value& result, const Value& error, const Value& id)
{
    Object reply = JSONRPCReplyObj(result, error, id);
    return write_string(Value(reply), false) + "\n";
}

void ErrorReply(std::ostream& stream, const Object& objError, const Value& id)
{
    // Send error reply from json-rpc error object
    int nStatus = 500;
    int code = find_value(objError, "code").get_int();
    if (code == -32600) nStatus = 400;
    else if (code == -32601) nStatus = 404;
    string strReply = JSONRPCReply(Value::null, objError, id);
    stream << HTTPReply(nStatus, strReply) << std::flush;
}

bool ClientAllowed(const string& strAddress)
{
    if (strAddress == asio::ip::address_v4::loopback().to_string())
        return true;
    const vector<string>& vAllow = mapMultiArgs["-rpcallowip"];
    BOOST_FOREACH(string strAllow, vAllow)
        if (WildcardMatch(strAddress, strAllow))
            return true;
    return false;
}

//
// IOStream device that speaks SSL but can also speak non-SSL
//
class SSLIOStreamDevice : public iostreams::device<iostreams::bidirectional> {
public:
    SSLIOStreamDevice(SSLStream &streamIn, bool fUseSSLIn) : stream(streamIn)
    {
        fUseSSL = fUseSSLIn;
        fNeedHandshake = fUseSSLIn;
    }

    void handshake(ssl::stream_base::handshake_type role)
    {
        if (!fNeedHandshake) return;
        fNeedHandshake = false;
        stream.handshake(role);
    }
    std::streamsize read(char* s, std::streamsize n)
    {
        handshake(ssl::stream_base::server); // HTTPS servers read first
        if (fUseSSL) return stream.read_some(asio::buffer(s, n));
        return stream.next_layer().read_some(asio::buffer(s, n));
    }
    std::streamsize write(const char* s, std::streamsize n)
    {
        handshake(ssl::stream_base::client); // HTTPS clients write first
        if (fUseSSL) return asio::write(stream, asio::buffer(s, n));
        return asio::write(stream.next_layer(), asio::buffer(s, n));
    }
    bool connect(const std::string& server, const std::string& port)
    {
        ip::tcp::resolver resolver(stream.get_io_service());
        ip::tcp::resolver::query query(server.c_str(), port.c_str());
        ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        ip::tcp::resolver::iterator end;
        boost::system::error_code error = asio::error::host_not_found;
        while (error && endpoint_iterator != end)
        {
            stream.lowest_layer().close();
            stream.lowest_layer().connect(*endpoint_iterator++, error);
        }
        if (error)
            return false;
        return true;
    }

private:
    bool fNeedHandshake;
    bool fUseSSL;
    SSLStream& stream;
};

void ThreadRPCServer(void* parg)
{
    // getwork/getblocktemplate mining rewards paid here:
    pMiningKey = new CReserveKey(pwalletMain);

    try
    {
        vnThreadsRunning[THREAD_RPCSERVER]++;
        ThreadRPCServer2(parg);
        vnThreadsRunning[THREAD_RPCSERVER]--;
    }
    catch (std::exception& e) {
        vnThreadsRunning[THREAD_RPCSERVER]--;
        PrintException(&e, "ThreadRPCServer()");
    } catch (...) {
        vnThreadsRunning[THREAD_RPCSERVER]--;
        PrintException(NULL, "ThreadRPCServer()");
    }

    delete pMiningKey; pMiningKey = NULL;

    printf("ThreadRPCServer exited\n");
}

static Object JSONRPCExecOne(const Value& request)
{
    Object rpc_result;
    Object req = request.get_obj();
    Value id = Value::null;

    try {
        id = find_value(req, "id");

        // Parse method
        Value valMethod = find_value(req, "method");
        if (valMethod.type() == null_type)
            throw JSONRPCError(-32600, "Missing method");
        if (valMethod.type() != str_type)
            throw JSONRPCError(-32600, "Method must be a string");
        string strMethod = valMethod.get_str();
        if (strMethod != "getwork" && strMethod != "getblocktemplate")
            printf("ThreadRPCServer method=%s\n", strMethod.c_str());

        // Parse params
        Value valParams = find_value(req, "params");
        Array params;
        if (valParams.type() == array_type)
            params = valParams.get_array();
        else if (valParams.type() == null_type)
            params = Array();
        else
            throw JSONRPCError(-32600, "Params must be an array");

        Value result = tableRPC.execute(strMethod, params);
        rpc_result = JSONRPCReplyObj(result, Value::null, id);
    }
    catch (Object& objError)
    {
        rpc_result = JSONRPCReplyObj(Value::null, objError, id);
    }
    catch (std::exception& e)
    {
        rpc_result = JSONRPCReplyObj(Value::null, JSONRPCError(-32700, e.what()), id);
    }

    return rpc_result;
}

static string JSONRPCExecBatch(const Array& vReq)
{
    Array ret;
    for (unsigned int reqIdx = 0; reqIdx < vReq.size(); reqIdx++)
        ret.push_back(JSONRPCExecOne(vReq[reqIdx]));

    return write_string(Value(ret), false) + "\n";
}

void ThreadRPCServer2(void* parg)
{
    printf("ThreadRPCServer started\n");

    strRPCUserColonPass = mapArgs["-rpcuser"] + ":" + mapArgs["-rpcpassword"];
    if ((mapArgs["-rpcpassword"] == "") ||
        (mapArgs["-rpcuser"] == mapArgs["-rpcpassword"]))
    {
        unsigned char rand_pwd[32];
        RAND_bytes(rand_pwd, 32);
        string strWhatAmI = "To use paycoin(paycoind)";
        if (mapArgs.count("-server"))
            strWhatAmI = strprintf(_("To use the %s option"), "\"-server\"");
        else if (mapArgs.count("-daemon"))
            strWhatAmI = strprintf(_("To use the %s option"), "\"-daemon\"");
        ThreadSafeMessageBox(strprintf(
            _("%s, you must set a rpcpassword in the configuration file:\n %s\n"
              "It is recommended you use the following random password:\n"
              "rpcuser=paycoinrpc\n"
              "rpcpassword=%s\n"
              "(you do not need to remember this password)\n"
              "The username and password MUST NOT be the same.\n"
              "If the file does not exist, create it with owner-readable-only file permissions.\n"),
                strWhatAmI.c_str(),
                GetConfigFile().string().c_str(),
                EncodeBase58(&rand_pwd[0],&rand_pwd[0]+32).c_str()),
            _("Error"), wxOK | wxMODAL);
        StartShutdown();
        return;
    }

    bool fUseSSL = GetBoolArg("-rpcssl");
    asio::ip::address bindAddress = mapArgs.count("-rpcallowip") ? asio::ip::address_v4::any() : asio::ip::address_v4::loopback();

    asio::io_service io_service;
    ip::tcp::endpoint endpoint(bindAddress, GetArg("-rpcport", fTestNet? TESTNET_RPC_PORT : RPC_PORT));
    ip::tcp::acceptor acceptor(io_service);
    try
    {
        acceptor.open(endpoint.protocol());
        acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
        acceptor.bind(endpoint);
        acceptor.listen(socket_base::max_connections);
    }
    catch(boost::system::system_error &e)
    {
        ThreadSafeMessageBox(strprintf(_("An error occurred while setting up the RPC port %i for listening: %s"), endpoint.port(), e.what()),
                             _("Error"), wxOK | wxMODAL);
        StartShutdown();
        return;
    }

    ssl::context context(io_service, ssl::context::sslv23);
    if (fUseSSL)
    {
        context.set_options(ssl::context::no_sslv2);

        filesystem::path pathCertFile(GetArg("-rpcsslcertificatechainfile", "server.cert"));
        if (!pathCertFile.is_complete()) pathCertFile = filesystem::path(GetDataDir()) / pathCertFile;
        if (filesystem::exists(pathCertFile)) context.use_certificate_chain_file(pathCertFile.string());
        else printf("ThreadRPCServer ERROR: missing server certificate file %s\n", pathCertFile.string().c_str());

        filesystem::path pathPKFile(GetArg("-rpcsslprivatekeyfile", "server.pem"));
        if (!pathPKFile.is_complete()) pathPKFile = filesystem::path(GetDataDir()) / pathPKFile;
        if (filesystem::exists(pathPKFile)) context.use_private_key_file(pathPKFile.string(), ssl::context::pem);
        else printf("ThreadRPCServer ERROR: missing server private key file %s\n", pathPKFile.string().c_str());

        string strCiphers = GetArg("-rpcsslciphers", "TLSv1+HIGH:!SSLv2:!aNULL:!eNULL:!AH:!3DES:@STRENGTH");
        SSL_CTX_set_cipher_list(context.impl(), strCiphers.c_str());
    }

    for (;;)
    {
        // Accept connection
        SSLStream sslStream(io_service, context);
        SSLIOStreamDevice d(sslStream, fUseSSL);
        iostreams::stream<SSLIOStreamDevice> stream(d);

        ip::tcp::endpoint peer;
        vnThreadsRunning[THREAD_RPCSERVER]--;
        acceptor.accept(sslStream.lowest_layer(), peer);
        vnThreadsRunning[4]++;
        if (fShutdown)
            return;

        // Restrict callers by IP
        if (!ClientAllowed(peer.address().to_string()))
        {
            // Only send a 403 if we're not using SSL to prevent a DoS during the SSL handshake.
            if (!fUseSSL)
                stream << HTTPReply(403, "") << std::flush;
            continue;
        }

        map<string, string> mapHeaders;
        string strRequest;

        boost::thread api_caller(ReadHTTP, boost::ref(stream), boost::ref(mapHeaders), boost::ref(strRequest));
        if (!api_caller.timed_join(boost::posix_time::seconds(GetArg("-rpctimeout", 30))))
        {   // Timed out:
            acceptor.cancel();
            printf("ThreadRPCServer ReadHTTP timeout\n");
            continue;
        }

        // Check authorization
        if (mapHeaders.count("authorization") == 0)
        {
            stream << HTTPReply(401, "") << std::flush;
            continue;
        }
        if (!HTTPAuthorized(mapHeaders))
        {
            printf("ThreadRPCServer incorrect password attempt from %s\n",peer.address().to_string().c_str());
            /* Deter brute-forcing short passwords.
               If this results in a DOS the user really
               shouldn't have their RPC port exposed.*/
            if (mapArgs["-rpcpassword"].size() < 20)
                Sleep(250);

            stream << HTTPReply(401, "") << std::flush;
            continue;
        }

        Value id = Value::null;
        try
        {
            // Parse request
            Value valRequest;
            if (!read_string(strRequest, valRequest))
                throw JSONRPCError(-32700, "Parse error");

            string strReply;
            if (valRequest.type() == obj_type) {
              // singleton request
              Object result;
              result = JSONRPCExecOne(valRequest);
              strReply = write_string(Value(result), false) + "\n";
            } else if (valRequest.type() == array_type) {
              // array of requests
              strReply = JSONRPCExecBatch(valRequest.get_array());
            } else
              throw JSONRPCError(-32600, "Top-level object parse error");

            // Send reply
            stream << HTTPReply(200, strReply) << std::flush;
        }
        catch (Object& objError)
        {
            ErrorReply(stream, objError, id);
        }
        catch (std::exception& e)
        {
            ErrorReply(stream, JSONRPCError(-32700, e.what()), id);
        }
    }
}

json_spirit::Value CRPCTable::execute(const std::string &strMethod, const json_spirit::Array &params) const
{
    // Find method
    const CRPCCommand *pcmd = tableRPC[strMethod];
    if (!pcmd)
        throw JSONRPCError(-32601, "Method not found");

    // Observe safe mode
    string strWarning = GetWarnings("rpc");
    if (strWarning != "" && !GetBoolArg("-disablesafemode") &&
        !pcmd->okSafeMode)
        throw JSONRPCError(-2, string("Safe mode: ") + strWarning);

    try
    {
        // Execute
        Value result;
        {
            LOCK2(cs_main, pwalletMain->cs_wallet);
            result = pcmd->actor(params, false);
        }
        return result;
    }
    catch (std::exception& e)
    {
        throw JSONRPCError(-1, e.what());
    }
}


Object CallRPC(const string& strMethod, const Array& params)
{
    if (mapArgs["-rpcuser"] == "" && mapArgs["-rpcpassword"] == "")
        throw runtime_error(strprintf(
            _("You must set rpcpassword=<password> in the configuration file:\n%s\n"
              "If the file does not exist, create it with owner-readable-only file permissions."),
                GetConfigFile().string().c_str()));

    // Connect to localhost
    bool fUseSSL = GetBoolArg("-rpcssl");
    asio::io_service io_service;
    ssl::context context(io_service, ssl::context::sslv23);
    context.set_options(ssl::context::no_sslv2);
    SSLStream sslStream(io_service, context);
    SSLIOStreamDevice d(sslStream, fUseSSL);
    iostreams::stream<SSLIOStreamDevice> stream(d);
    if (!d.connect(GetArg("-rpcconnect", "127.0.0.1"), GetArg("-rpcport", CBigNum(fTestNet? TESTNET_RPC_PORT : RPC_PORT).ToString().c_str())))
        throw runtime_error("couldn't connect to server");

    // HTTP basic authentication
    string strUserPass64 = EncodeBase64(mapArgs["-rpcuser"] + ":" + mapArgs["-rpcpassword"]);
    map<string, string> mapRequestHeaders;
    mapRequestHeaders["Authorization"] = string("Basic ") + strUserPass64;

    // Send request
    string strRequest = JSONRPCRequest(strMethod, params, 1);
    string strPost = HTTPPost(strRequest, mapRequestHeaders);
    stream << strPost << std::flush;

    // Receive reply
    map<string, string> mapHeaders;
    string strReply;
    int nStatus = ReadHTTP(stream, mapHeaders, strReply);
    if (nStatus == 401)
        throw runtime_error("incorrect rpcuser or rpcpassword (authorization failed)");
    else if (nStatus >= 400 && nStatus != 400 && nStatus != 404 && nStatus != 500)
        throw runtime_error(strprintf("server returned HTTP error %d", nStatus));
    else if (strReply.empty())
        throw runtime_error("no response from server");

    // Parse reply
    Value valReply;
    if (!read_string(strReply, valReply))
        throw runtime_error("couldn't parse reply from server");
    const Object& reply = valReply.get_obj();
    if (reply.empty())
        throw runtime_error("expected reply to have result, error and id properties");

    return reply;
}

template<typename T> void ConvertTo(Value& value)
{
    if (value.type() == str_type)
    {
        // reinterpret string as unquoted json value
        Value value2;
        if (!read_string(value.get_str(), value2))
            throw runtime_error("type mismatch");
        value = value2.get_value<T>();
    }
    else
    {
        value = value.get_value<T>();
    }
}

// Convert strings to command-specific RPC representation
Array RPCConvertValues(const std::string &strMethod, const std::vector<std::string> &strParams)
{
    Array params;
    BOOST_FOREACH(const std::string &param, strParams)
        params.push_back(param);

    int n = params.size();

    //
    // Special case non-string parameter types
    //
    if (strMethod == "setgenerate"            && n > 0) ConvertTo<bool>(params[0]);
    if (strMethod == "setgenerate"            && n > 1) ConvertTo<boost::int64_t>(params[1]);
    if (strMethod == "sendtoaddress"          && n > 1) ConvertTo<double>(params[1]);
    if (strMethod == "settxfee"               && n > 0) ConvertTo<double>(params[0]);
    if (strMethod == "getreceivedbyaddress"   && n > 1) ConvertTo<boost::int64_t>(params[1]);
    if (strMethod == "getreceivedbyaccount"   && n > 1) ConvertTo<boost::int64_t>(params[1]);
    if (strMethod == "listreceivedbyaddress"  && n > 0) ConvertTo<boost::int64_t>(params[0]);
    if (strMethod == "listreceivedbyaddress"  && n > 1) ConvertTo<bool>(params[1]);
    if (strMethod == "listreceivedbyaccount"  && n > 0) ConvertTo<boost::int64_t>(params[0]);
    if (strMethod == "listreceivedbyaccount"  && n > 1) ConvertTo<bool>(params[1]);
    if (strMethod == "listaddressbook"        && n > 0) ConvertTo<bool>(params[0]);
    if (strMethod == "getbalance"             && n > 1) ConvertTo<boost::int64_t>(params[1]);
    if (strMethod == "getblockhash"           && n > 0) ConvertTo<boost::int64_t>(params[0]);
    if (strMethod == "getblock"               && n > 1) ConvertTo<bool>(params[1]);
    if (strMethod == "getblock"               && n > 2) ConvertTo<bool>(params[2]);
    if (strMethod == "move"                   && n > 2) ConvertTo<double>(params[2]);
    if (strMethod == "move"                   && n > 3) ConvertTo<boost::int64_t>(params[3]);
    if (strMethod == "sendfrom"               && n > 2) ConvertTo<double>(params[2]);
    if (strMethod == "sendfrom"               && n > 3) ConvertTo<boost::int64_t>(params[3]);
    if (strMethod == "listtransactions"       && n > 1) ConvertTo<boost::int64_t>(params[1]);
    if (strMethod == "listtransactions"       && n > 2) ConvertTo<boost::int64_t>(params[2]);
    if (strMethod == "listaddressgroupings"       && n > 2) ConvertTo<boost::int64_t>(params[0]);
    if (strMethod == "listaccounts"           && n > 0) ConvertTo<boost::int64_t>(params[0]);
    if (strMethod == "walletpassphrase"       && n > 1) ConvertTo<boost::int64_t>(params[1]);
    if (strMethod == "walletpassphrase"       && n > 2) ConvertTo<bool>(params[2]);
    if (strMethod == "getblocktemplate"       && n > 0) ConvertTo<Object>(params[0]);
    if (strMethod == "listsinceblock"         && n > 1) ConvertTo<boost::int64_t>(params[1]);
    if (strMethod == "sendalert"              && n > 2) ConvertTo<boost::int64_t>(params[2]);
    if (strMethod == "sendalert"              && n > 3) ConvertTo<boost::int64_t>(params[3]);
    if (strMethod == "sendalert"              && n > 4) ConvertTo<boost::int64_t>(params[4]);
    if (strMethod == "sendalert"              && n > 5) ConvertTo<boost::int64_t>(params[5]);
    if (strMethod == "sendalert"              && n > 6) ConvertTo<boost::int64_t>(params[6]);
    if (strMethod == "sendmany"               && n > 1)
    {
        string s = params[1].get_str();
        Value v;
        if (!read_string(s, v) || v.type() != obj_type)
            throw runtime_error("type mismatch");
        params[1] = v.get_obj();
    }
    if (strMethod == "sendmany"                && n > 2) ConvertTo<boost::int64_t>(params[2]);
    if (strMethod == "reservebalance"          && n > 0) ConvertTo<bool>(params[0]);
    if (strMethod == "reservebalance"          && n > 1) ConvertTo<double>(params[1]);
    if (strMethod == "createmultisig"          && n > 0) ConvertTo<boost::int64_t>(params[0]);
    if (strMethod == "createmultisig"          && n > 1)
    {
        string s = params[1].get_str();
        Value v;
        if (!read_string(s, v) || v.type() != array_type)
            throw runtime_error("type mismatch "+s);
        params[1] = v.get_array();
    }
    if (strMethod == "addmultisigaddress"      && n > 0) ConvertTo<boost::int64_t>(params[0]);
    if (strMethod == "addmultisigaddress"      && n > 1)
    {
        string s = params[1].get_str();
        Value v;
        if (!read_string(s, v) || v.type() != array_type)
            throw runtime_error("type mismatch "+s);
        params[1] = v.get_array();
    }
    if (strMethod == "listunspent"            && n > 0) ConvertTo<boost::int64_t>(params[0]);
    if (strMethod == "listunspent"            && n > 1) ConvertTo<boost::int64_t>(params[1]);
    if (strMethod == "listunspent"            && n > 2) ConvertTo<Array>(params[2]);
    if (strMethod == "getrawtransaction"      && n > 1) ConvertTo<boost::int64_t>(params[1]);
    if (strMethod == "createrawtransaction"   && n > 0) ConvertTo<Array>(params[0]);
    if (strMethod == "createrawtransaction"   && n > 1) ConvertTo<Object>(params[1]);
    if (strMethod == "signrawtransaction"     && n > 1) ConvertTo<Array>(params[1]);
    if (strMethod == "signrawtransaction"     && n > 2) ConvertTo<Array>(params[2]);
    if (strMethod == "sendrawtransaction"     && n > 1) ConvertTo<boost::int64_t>(params[1]);
    if (strMethod == "gettxout"               && n > 1) ConvertTo<int64_t>(params[1]);
    if (strMethod == "gettxout"               && n > 2) ConvertTo<bool>(params[2]);
    if (strMethod == "listminting"            && n > 0) ConvertTo<boost::int64_t>(params[0]);
    if (strMethod == "listminting"            && n > 1) ConvertTo<boost::int64_t>(params[1]);
    return params;
}

int CommandLineRPC(int argc, char *argv[])
{
    string strPrint;
    int nRet = 0;
    try
    {
        // Skip switches
        while (argc > 1 && IsSwitchChar(argv[1][0]))
        {
            argc--;
            argv++;
        }

        // Method
        if (argc < 2)
            throw runtime_error("too few parameters");
        string strMethod = argv[1];

        // Parameters default to strings
        std::vector<std::string> strParams(&argv[2], &argv[argc]);
        Array params = RPCConvertValues(strMethod, strParams);

        // Execute
        Object reply = CallRPC(strMethod, params);

        // Parse reply
        const Value& result = find_value(reply, "result");
        const Value& error  = find_value(reply, "error");

        if (error.type() != null_type)
        {
            // Error
            strPrint = "error: " + write_string(error, false);
            int code = find_value(error.get_obj(), "code").get_int();
            nRet = abs(code);
        }
        else
        {
            // Result
            if (result.type() == null_type)
                strPrint = "";
            else if (result.type() == str_type)
                strPrint = result.get_str();
            else
                strPrint = write_string(result, true);
        }
    }
    catch (std::exception& e)
    {
        strPrint = string("error: ") + e.what();
        nRet = 87;
    }
    catch (...)
    {
        PrintException(NULL, "CommandLineRPC()");
    }

    if (strPrint != "")
    {
        fprintf((nRet == 0 ? stdout : stderr), "%s\n", strPrint.c_str());
    }
    return nRet;
}

#ifdef TEST
int main(int argc, char *argv[])
{
#ifdef _MSC_VER
    // Turn off Microsoft heap dump noise
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, CreateFile("NUL", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0));
#endif
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    try
    {
        if (argc >= 2 && string(argv[1]) == "-server")
        {
            printf("server ready\n");
            ThreadRPCServer(NULL);
        }
        else
        {
            return CommandLineRPC(argc, argv);
        }
    }
    catch (std::exception& e) {
        PrintException(&e, "main()");
    } catch (...) {
        PrintException(NULL, "main()");
    }
    return 0;
}
#endif

const CRPCTable tableRPC;
