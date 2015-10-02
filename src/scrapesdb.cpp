// Copyright (c) 2015 The Paycoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "init.h"
#include "bitcoinrpc.h"
#include "scrapesdb.h"

#define printf OutputDebugStringF

using namespace json_spirit;
using namespace std;

extern CScrapesDB* scrapesDB;

Value setscrapeaddress(const Array& params, bool fHelp)
{
    if (fHelp || params.size() != 2)
        throw runtime_error(
            "setscrapeaddress <staking address>, <address to stake to>\n"
            "Set an auto scrape address to send stake rewards to from a given address."
        );

    string strAddress = params[0].get_str();
    CBitcoinAddress address(strAddress);
    string strScrapeAddress = params[1].get_str();
    CBitcoinAddress scrapeAddress(strScrapeAddress);

    if (address.Get() == scrapeAddress.Get())
        throw runtime_error(
            "Cannot set scrape address to the same as staking address."
        );

    if (!IsMine(*pwalletMain, address.Get()))
        throw runtime_error(
            "Staking address must be in wallet."
        );

    if (!scrapeAddress.IsValid())
        throw runtime_error(
            "Invalid scrape address."
        );

    string oldScrapeAddress;
    bool warn = false;
    if (scrapesDB->ReadScrapeAddress(strAddress, oldScrapeAddress)) {
        if (strScrapeAddress == oldScrapeAddress)
            throw runtime_error(strprintf("Scrape address is already set to %s", oldScrapeAddress.c_str()));

        warn = true;
    }

    if (scrapesDB->WriteScrapeAddress(strAddress, strScrapeAddress)) {
        if (warn)
            return strprintf("Warning overwriting %s with %s", oldScrapeAddress.c_str(), strScrapeAddress.c_str());

        Object obj;
        obj.push_back(Pair(strAddress, strScrapeAddress));
        return obj;
    }

    // This should never happen.
    throw runtime_error(
        "setscrapeaddress: unknown error"
    );
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

    if (!IsMine(*pwalletMain, address.Get()))
        throw runtime_error(
            "Staking address must be in wallet."
        );

    string strScrapeAddress;
    if (!scrapesDB->ReadScrapeAddress(strAddress, strScrapeAddress)) {
        string ret = "No scrape address set for address ";
        ret += strAddress;
        throw runtime_error(ret);
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
    scrapesDB->DumpScrapeAddresses(obj);

    return obj;
}

Value deletescrapeaddress(const Array& params, bool fHelp)
{
    if (fHelp || params.size() != 1)
        throw runtime_error(
            "deletescrapeaddress <staking address>\n"
            "Delete the auto scrape address for a given address."
        );

    string strAddress = params[0].get_str();
    CBitcoinAddress address(strAddress);

    if (!IsMine(*pwalletMain, address.Get()))
        throw runtime_error(
            "Staking address must be in wallet."
        );

    if (!scrapesDB->HasScrapeAddress(strAddress)) {
        string ret = "No scrape address set for address ";
        ret += strAddress;
        throw runtime_error(ret);
    }

    return scrapesDB->EraseScrapeAddress(strAddress);
}

bool CScrapesDB::WriteScrapeAddress(const string strAddress, const string strScrapeAddress)
{
    LOCK(cs);
    return Write(make_pair(string("scrapeaddress"), strAddress), strScrapeAddress);
}

bool CScrapesDB::EraseScrapeAddress(const string strAddress)
{
    LOCK(cs);
    return Erase(make_pair(string("scrapeaddress"), strAddress));
}

bool CScrapesDB::ReadScrapeAddress(const string strAddress, string &strScrapeAddress)
{
    return Read(make_pair(string("scrapeaddress"), strAddress), strScrapeAddress);
}

bool CScrapesDB::HasScrapeAddress(const string strAddress)
{
    return Exists(make_pair(string("scrapeaddress"), strAddress));
}

bool CScrapesDB::DumpScrapeAddresses(Object &ScrapeAddresses) {
    Dbc* pcursor = GetCursor();
    if (!pcursor)
        throw runtime_error("DumpScrapeAddresses() : cannot create DB cursor");
    unsigned int fFlags = DB_SET_RANGE;

    for (;;)
    {
        CDataStream ssKey(SER_DISK, CLIENT_VERSION);
        if (fFlags == DB_SET_RANGE)
            ssKey << make_pair(std::string("scrapeaddress"), string(""));
        CDataStream ssValue(SER_DISK, CLIENT_VERSION);
        int ret = ReadAtCursor(pcursor, ssKey, ssValue, fFlags);
        fFlags = DB_NEXT;
        if (ret == DB_NOTFOUND)
            break;

        else if (ret != 0)
        {
            pcursor->close();
            throw runtime_error("DumpScrapeAddresses() : error scanning DB");
        }
        // Unserialize
        string strType, address, scrape_address;
        ssKey >> strType;
        if (strType != "scrapeaddress")
            break;
        ssKey >> address;
        ssValue >> scrape_address;
        ScrapeAddresses.push_back(Pair(address, scrape_address));
    }

    pcursor->close();
    return true;
}
