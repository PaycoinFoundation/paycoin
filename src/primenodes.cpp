// Copyright (c) 2015 The Paycoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "base58.h"
#include "db.h"
#include "util.h"
#include "primenodes.h"

using namespace std;

extern void CloseDb(const string& strFile);

CPrimeNodeDB* primeNodeDB;

// Reset all primenode stakerates to 100% after the given date
static const unsigned int RESET_PRIMERATES = 1429531200; // Mon, 20 Apr 2015 12:00:00 GMT

bool NewScriptPrimeID(CScript &scriptPrimeID, vector<unsigned char> vchPrivKey, unsigned int nTime) {
    CKey key;
    key.SetPrivKey(CPrivKey(vchPrivKey.begin(), vchPrivKey.end()));
    CScript scriptTime;
    scriptTime << nTime;
    uint256 hashScriptTime = Hash(scriptTime.begin(), scriptTime.end());
    vector<unsigned char> vchSig;

    if (!key.Sign(hashScriptTime, vchSig)) // Should only ever occur on init.
        return error("NewScriptPrimeID() : unable to sign ID script, possible invalid key format.");

    scriptPrimeID << OP_PRIMENODEP2 << vchSig;
    return true;
}

bool initPrimeNodes(string &str) {
    // Create our database if it doesn't exist..
    primeNodeDB = new CPrimeNodeDB("cr");

    /* For whatever reason the database statistics don't return usable
     * information (same stats on all existing databases). Check for the
     * existance of the first and last keys in the list assuming all keys
     * in between are present, if either key is missing, attempt to inflate
     * the database. These checks can be done with a single if statement for
     * each node type but it causes a warning about missing parenthesis that if
     * added break the function. The dbtype checks should be doable with a
     * ternary but when using one the value of fulldb is always returned.
     *
     * So if you are done trying to 'optimize' this routine (and failed).
     * Please increment the following counter as a warning to the next guy.
     *
     * total_hours_wasted_here = 5
     */
     dbtype db = nodb;
     if (fTestNet) {
         if (!primeNodeDB->CheckPrimeNodeKey(string("04d445518d115243639d0dfd057a99da588e8334039ce674f177943d4c660957c810f924a5371a352b1e827121846500a588a4dc47dc6d5d9e5317dfa48c562aa7"))
             || !primeNodeDB->CheckPrimeNodeKey(string("0443e5bf72234d77a591ca2132c5995cccdba377a7022eb014d25e27ebe6ffaf85cd3a214588612186ee1771cfb905d1ec2137193bc01563dbc36d1e28f013e00d")))
             db = primedb;

         if (!primeNodeDB->CheckMicroPrime(string("muVEJW5YZpZc4QxUaDMJVxcy1vQcMrPhmQ"))
             || !primeNodeDB->CheckMicroPrime(string("mpCYzc3XqcLYGBHtJxAFQQ1nz7YZwecE3v")))
         {
             if (db == primedb) {
                 db = fulldb;
             } else {
                 db = microdb;
             }
         }
     } else {
         if (!primeNodeDB->CheckPrimeNodeKey(string("04388d05d6cdbf75a37540e9b94c1c0b4e9b41a109c1466a33b3cf3cbca9e244f7761686502a0a593831fac02753ea5c2c8fc14ed59b9060da2088d2cb674e041d"))
             || !primeNodeDB->CheckPrimeNodeKey(string("04df482827573b607fe7279687bb287ccb48f87d24752c69d68e2c130d2d2c8993056e05fb86e61d54747b043c3f6f22b31b891664a90e4c071c794c93455b1cbe")))
             db = primedb;
         if (!primeNodeDB->CheckMicroPrime(string("P9Yo3PtaxuzeBZAimsGzz6mdTmdDtU6vhf"))
             || !primeNodeDB->CheckMicroPrime(string("PMaTtaVc6iV6XCc92ZYwzNGXUxBryUAmDm")))
         {
             if (db == primedb) {
                 db = fulldb;
             } else {
                 db = microdb;
             }
         }
     }
     if (db != nodb)
         InflatePrimeNodeDB(db);

    // If there is a primenode key in the conf file, confirm it's valid.
    if (mapArgs.count("-primenodekey")) {
        printf("Primenode key found in configuration, verifying...\n");

        CScript scriptPrimeID;
        unsigned int nTime = GetTime();
        string strPrivKey = GetArg("-primenodekey", "");
        vector<unsigned char> vchPrivKey = ParseHex(strPrivKey);
        if (!NewScriptPrimeID(scriptPrimeID, vchPrivKey, nTime)) {
            str = "initPrimeNodes() : unable to sign ID script, possible invalid key format.";
            return false;
        }

        // We don't use this entry, we just want to know that the key is valid.
        CPrimeNodeDBEntry entry;
        if (!primeNodeDB->IsPrimeNodeKey(scriptPrimeID, nTime, entry)) {
            str = "initPrimeNode() : invalid primenode key";
            return false;
        }

        str = "Primenode key is correct for activating a prime controller";
    }
    return true;
}

// Prototype
bool IsPrimeNodeKey(CScript /*scriptPubKeyType*/, unsigned int /*nTime*/, CPrimeNodeDBEntry &/*entry*/);

// Check if a stake is either a prime or microprime stake.
bool CTransaction::IsPrimeStake(CScript scriptPubKeyType, CScript scriptPubKeyAddress, unsigned int nTime, int64 nValueIn, int64 nValueOut, uint64 nCoinAge) {
    int primeNodeRate = 0;
    int64 nStakeReward = nValueOut - nValueIn;

    // Process microprime transactions first as these are easier to confirm.
    if (scriptPubKeyType[0] == OP_MICROPRIME) {
        int64 group;
        /* Destination address is stored in the CScript for vout[1] of the input
         * so extract it against our database.
         *
         * IsMicroPrime returns the DB return value which will always return
         * true for a read even if nothing has been read, check that the address
         * exists before trying to read the related entries. */
        if (!primeNodeDB->CheckMicroPrime(scriptPubKeyAddress))
            return DoS(100, error("IsPrimeStake() : invalid microprime address, HAXORS!!!"));

        primeNodeDB->IsMicroPrime(scriptPubKeyAddress, primeNodeRate, group);
        /* Confirm the nValueIn is not greater than the balance allowed per
         * microPrimeGroup. This should not occur and will only happen if
         * someone attempts to hack the stake rate. */
        if (nValueIn > group * COIN)
            return DoS(100, error("IsPrimeStake() : nValueIn %lld exceeds max balance for microprime group %lld", nValueIn, group));

        if (nStakeReward > GetProofOfStakeReward(nCoinAge, nTime, primeNodeRate) - GetMinFee() + MIN_TX_FEE)
            return DoS(100, error("IsPrimeStake() : %s stake reward exceeded", GetHash().ToString().substr(0,10).c_str()));

        // No need to validate primes at this point, just return true.
        return true;
    }

    /* Block new stakes from legacy phase 1 primenodes
     *.
     * Starting with microprimes primenodes will be stored in a database
     * along with primeNodeRate, valid_starting and valid_until tracking
     * variables to reduce the number of OP codes that are needed.
     */
    if (nTime >= END_PRIME_PHASE_ONE && scriptPubKeyType[0] != OP_PRIMENODEP2)
        return DoS(100, error("IsPrimeStake() : prime node staking has ended for the given keypair"));

    // Set legacy primeNodeRates.
    switch (scriptPubKeyType[0]) {
        case OP_PRIMENODE350:
            primeNodeRate = 350;
            break;
        case OP_PRIMENODE100:
            primeNodeRate = 100;
            break;
        case OP_PRIMENODE20:
            primeNodeRate = 20;
            break;
        case OP_PRIMENODE10:
            primeNodeRate = 10;
            break;
    }

    /* Check the script signature to confirm it came from a valid prime node key
     * Don't check legacy phase 1 primenode key sigs, these are old blocks which
     * are known good. Future stakes are already invalidated by the above.
     * Old blocks are valid so long as they pass standard chain integrity checks
     */
    if (scriptPubKeyType[0] == OP_PRIMENODEP2) {
        CPrimeNodeDBEntry entry;
        if (!primeNodeDB->IsPrimeNodeKey(scriptPubKeyType, nTime, entry))
            return DoS(10, error("IsPrimeStake() : verify signature failed"));

        // Confirm the transaction time is within the valid time of the key used.
        if (nTime < entry.valid_starting)
            return DoS(100, error("IsPrimeStake() : prime node staking has not started for the given keypair"));
        /* -1 means that a stop time hasn't been defined, this is something that
         * may be set temperately when it's known that a release will be done
         * that ensures people update before the real valid_until time occurs
         * and the real end date is unknown at the time of updating the keys. */
        if (entry.valid_until != -1 && nTime >= entry.valid_until)
            return DoS(100, error("IsPrimeStake() : prime node staking has ended for the given keypair"));

        primeNodeRate = entry.primeNodeRate;
    }

    // Confirm the stake passes the minimum for a primenode
    if (nTime >= END_PRIME_PHASE_ONE && nValueOut < MINIMUM_FOR_PRIMENODE_PHASE2)
        return DoS(100, error("IsPrimeStake() : credit doesn't meet requirement for primenode = %lld while you only have %lld", MINIMUM_FOR_PRIMENODE_PHASE2, nValueOut));
    if (nValueOut < MINIMUM_FOR_PRIMENODE_PHASE1)
        return DoS(100, error("IsPrimeStake() : credit doesn't meet requirement for primenode = %lld while you only have %lld", MINIMUM_FOR_PRIMENODE_PHASE1, nValueOut));

    /* Reset the primeNodeRate to 100 on the Legacy Phase 1 primenodes after the
     * specified time. Stakes existing prior to that or created after the end of
     * prime phase 1 use the normal primeNodeRate specified. */
    if (nTime >= RESET_PRIMERATES && nTime < END_PRIME_PHASE_ONE) {
        if (nStakeReward > GetProofOfStakeReward(nCoinAge, nTime, 100) - GetMinFee() + MIN_TX_FEE)
            return DoS(100, error("IsPrimeStake() : %s stake reward exceeded", GetHash().ToString().substr(0,10).c_str()));
    } else {
        if (nStakeReward > GetProofOfStakeReward(nCoinAge, nTime, primeNodeRate) - GetMinFee() + MIN_TX_FEE)
            return DoS(100, error("IsPrimeStake() : %s stake reward exceeded", GetHash().ToString().substr(0,10).c_str()));
    }

    return true;
}

/* Check the script signature to confirm it came from a valid prime node key
 * nTime is the time of the transaction/stake.
 * entry is the resulting database entry if the script signature is valid. */
bool CPrimeNodeDB::IsPrimeNodeKey(CScript scriptPubKeyType, unsigned int nTime, CPrimeNodeDBEntry &entry) {
    vector<CPrimeNodeDBEntry> primeNodeDBEntries;
    Dbc* pcursor = GetCursor();
    if (!pcursor)
        throw runtime_error("IsPrimeNodeKey() : cannot create DB cursor");
    unsigned int fFlags = DB_SET_RANGE;

    for (;;)
    {
        CDataStream ssKey(SER_DISK, CLIENT_VERSION);
        if (fFlags == DB_SET_RANGE)
            ssKey << make_pair(string("primenode"), string(""));
        CDataStream ssValue(SER_DISK, CLIENT_VERSION);
        int ret = ReadAtCursor(pcursor, ssKey, ssValue, fFlags);
        fFlags = DB_NEXT;
        if (ret == DB_NOTFOUND)
            break;

        else if (ret != 0)
        {
            pcursor->close();
            throw runtime_error("IsPrimeNodeKey() : error scanning DB");
        }

        // Unserialize
        string strType;
        ssKey >> strType;
        if (strType != "primenode")
            break;
        CPrimeNodeDBEntry dbentry;
        ssKey >> dbentry.key;
        ssValue >> dbentry;
        primeNodeDBEntries.push_back(dbentry);
    }

    pcursor->close();

    BOOST_FOREACH(CPrimeNodeDBEntry dbentry, primeNodeDBEntries) {
        vector<unsigned char> vchPubKey = ParseHex(dbentry.key);
        CKey key;
        key.SetPubKey(vchPubKey);
        CScript scriptTime;
        scriptTime << nTime;
        uint256 hashScriptTime = Hash(scriptTime.begin(), scriptTime.end());

        vector<unsigned char> vchSig;
        vchSig.insert(vchSig.end(), scriptPubKeyType.begin() + 2, scriptPubKeyType.end());

        if(key.Verify(hashScriptTime, vchSig)) {
            entry = dbentry;
            return true;
        }
    }
    return false;
}

// Inflate the primenode table in the primeNodeDB
void InflatePrimeNodeDB(dbtype db) {
    printf("InflatePrimeNodeDB() : Primenode database is inconsistent, inflating database.\n");
    // Db is open in read-only mode, close and reopen it with write privs.
    primeNodeDB->Close();
    bitdb.CloseDb("primenodes.dat");
    delete primeNodeDB;
    primeNodeDB = new CPrimeNodeDB("w+");

    if (db == primedb || db == fulldb)
        primeNodeDB->WritePrimeNodeDB();

    if (db == microdb || db == fulldb)
        fTestNet ? primeNodeDB->WriteTestMicroPrimeDB() : primeNodeDB->WriteMicroPrimeDB();

    /* Close Db and reopen it w/ read-only privs because we won't need to write
     * to it again. */
    primeNodeDB->Close();
    bitdb.CloseDb("primenodes.dat");
    delete primeNodeDB;
    primeNodeDB = new CPrimeNodeDB("r");
}

bool CPrimeNodeDB::WritePrimeNodeKey(const string key, int primeNodeRate, unsigned int valid_starting, unsigned int valid_until)
{
    return Write(make_pair(string("primenode"), key), boost::make_tuple(primeNodeRate, valid_starting, valid_until));
}

bool CPrimeNodeDB::WriteMicroPrimeAddr(const string address, int64 group, int primeNodeRate)
{
    return Write(make_pair(string("microprime"), address), make_pair(primeNodeRate, group));
}

bool CPrimeNodeDB::CheckPrimeNodeKey(const string key)
{
    return Exists(make_pair(string("primenode"), key));
}

bool CPrimeNodeDB::IsMicroPrime(CScript scriptPubKeyAddress, int &primeNodeRate, int64 &group)
{
    CTxDestination address;
    ExtractDestination(scriptPubKeyAddress, address);
    CBitcoinAddress addr(address);

    pair<int, int64> p;
    Read(make_pair(string("microprime"), addr.ToString()), p);
    primeNodeRate = p.first;
    group = p.second;
    return true;
}

bool CPrimeNodeDB::CheckMicroPrime(const string address)
{
    return Exists(make_pair(string("microprime"), address));
}

bool CPrimeNodeDB::CheckMicroPrime(CScript scriptPubKeyAddress)
{
    CTxDestination address;
    ExtractDestination(scriptPubKeyAddress, address);
    CBitcoinAddress addr(address);

    return CheckMicroPrime(addr.ToString());
}
