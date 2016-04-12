// Copyright (c) 2015 The Paycoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef SCRAPESDB_H
#define SCRAPESDB_H

#include "db.h"

class CScrapesDB : public CDB
{
public:
    CScrapesDB(std::string strFilename, const char* pszMode="r+") : CDB(strFilename.c_str(), pszMode) { }
private:

    CScrapesDB(const CScrapesDB&);
    void operator=(const CScrapesDB);
public:
    bool ImportScrapeAddressesToWallet();
};

#endif // SCRAPESDB_H
