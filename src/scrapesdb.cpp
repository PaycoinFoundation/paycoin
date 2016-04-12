// Copyright (c) 2015 The Paycoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "init.h"
#include "scrapesdb.h"

using namespace std;

bool CScrapesDB::ImportScrapeAddressesToWallet() {
    Dbc* pcursor = GetCursor();
    if (!pcursor)
        return error("ImportScrapeAddressesToWallet() : scrapes.dat appears is corrupt\n");

    unsigned int fFlags = DB_SET_RANGE;

    for (;;)
    {
        CDataStream ssKey(SER_DISK, CLIENT_VERSION);
        if (fFlags == DB_SET_RANGE)
            ssKey << make_pair(std::string("scrapeaddress"), string(""));

        CDataStream ssValue(SER_DISK, CLIENT_VERSION);
        int ret = ReadAtCursor(pcursor, ssKey, ssValue, fFlags);
        fFlags = DB_NEXT;
        if(ret == DB_NOTFOUND)
            break;

        else if (ret != 0)
        {
            pcursor->close();
            return error("ImportScrapeAddressesToWallet() : error scanning scrapes.dat\n");
        }

        // Unserialize
        string strType, address, scrape_address;
        ssKey >> strType;
        if (strType != "scrapeaddress")
            break;
        ssKey >> address;
        ssValue >> scrape_address;

        pwalletMain->WriteScrapeAddress(address, scrape_address);
    }

    pcursor->close();
    return true;
}
