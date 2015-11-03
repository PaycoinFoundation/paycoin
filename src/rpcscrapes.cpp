// Copyright (c) 2015 The Paycoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "init.h"
#include "bitcoinrpc.h"
#include "wallet.h"

using namespace json_spirit;
using namespace std;

extern Object JSONRPCError(int code, const string& message);

Value setscrapeaddress(const Array& params, bool fHelp)
{
    if (fHelp || params.size() != 2) {
        string ret = "setscrapeaddress <staking address>, <address to stake to>\nSet an auto scrape address to send stake rewards to from a given address.";
        if (pwalletMain->IsCrypted())
            ret += "requires wallet passphrase to be set with walletpassphrase first";

        throw runtime_error(ret);
    }

    if (pwalletMain->IsLocked())
        throw JSONRPCError(-13, "Error: Please enter the wallet passphrase with walletpassphrase first.");

    string strAddress = params[0].get_str();
    CBitcoinAddress address(strAddress);
    string strScrapeAddress = params[1].get_str();
    CBitcoinAddress scrapeAddress(strScrapeAddress);

    if (!address.IsValid())
        throw JSONRPCError(-5, "Invalid Paycoin address.");

    if (address.Get() == scrapeAddress.Get())
        throw JSONRPCError(-1, "Cannot set scrape address to the same as staking address.");

    if (!IsMine(*pwalletMain, address.Get()))
        throw JSONRPCError(-1, "Staking address must be in wallet.");

    if (!scrapeAddress.IsValid())
        throw JSONRPCError(-5, "Invalid scrape address.");

    string oldScrapeAddress;
    bool warn = false;
    if (pwalletMain->ReadScrapeAddress(strAddress, oldScrapeAddress)) {
        if (strScrapeAddress == oldScrapeAddress)
            throw runtime_error(strprintf("Scrape address is already set to %s", oldScrapeAddress.c_str()));

        warn = true;
    }

    if (pwalletMain->WriteScrapeAddress(strAddress, strScrapeAddress)) {
        if (warn)
            return strprintf("Warning overwriting %s with %s", oldScrapeAddress.c_str(), strScrapeAddress.c_str());

        Object obj;
        obj.push_back(Pair(strAddress, strScrapeAddress));
        return obj;
    }

    // This should never happen.
    throw JSONRPCError(-1, "setscrapeaddress: unknown error");
}

Value getscrapeaddress(const Array& params, bool fHelp)
{
    if (fHelp || params.size() != 1)
        throw runtime_error(
            "getscrapeaddress <staking address>\n"
            "Get the auto scrape address for a given address."
        );

    string strAddress = params[0].get_str();
    CBitcoinAddress address(strAddress);

    if (!address.IsValid())
        throw JSONRPCError(-5, "Invalid Paycoin address.");

    if (!IsMine(*pwalletMain, address.Get()))
        throw JSONRPCError(-1, "Staking address must be in wallet.");

    string strScrapeAddress;
    if (!pwalletMain->ReadScrapeAddress(strAddress, strScrapeAddress)) {
        string ret = "No scrape address set for address ";
        ret += strAddress;
        throw JSONRPCError(-1, ret);
    }

    Object obj;
    obj.push_back(Pair(strAddress, strScrapeAddress));
    return obj;
}

Value listscrapeaddresses(const Array& params, bool fHelp)
{
    if (fHelp || params.size() != 0)
        throw runtime_error(
            "listscrapeaddresses\n"
            "List all the defined scrape addresses."
        );

    Object obj;
    LOCK(pwalletMain->cs_wallet);
    CWalletDB(pwalletMain->strWalletFile).DumpScrapeAddresses(obj);

    return obj;
}

Value deletescrapeaddress(const Array& params, bool fHelp)
{
    if (fHelp || params.size() != 1) {
        string ret = "deletescrapeaddress <staking address>\nDelete the auto scrape address for a given address.";
        if (pwalletMain->IsCrypted())
            ret += "requires wallet passphrase to be set with walletpassphrase first";

        throw runtime_error(ret);
    }

    if (pwalletMain->IsLocked())
        throw JSONRPCError(-13, "Error: Please enter the wallet passphrase with walletpassphrase first.");

    string strAddress = params[0].get_str();
    CBitcoinAddress address(strAddress);

    if (!address.IsValid())
        throw JSONRPCError(-5, "Invalid Paycoin address.");

    if (!IsMine(*pwalletMain, address.Get()))
        throw JSONRPCError(-1, "Staking address must be in wallet.");

    if (!pwalletMain->HasScrapeAddress(strAddress)) {
        string ret = "No scrape address set for address ";
        ret += strAddress;
        throw JSONRPCError(-1, ret);
    }

    return pwalletMain->EraseScrapeAddress(strAddress);
}
