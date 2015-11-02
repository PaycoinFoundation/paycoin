// Copyright (c) 2015 The Paycoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef SCRAPESDB_H
#define SCRAPESDB_H

#include "db.h"
#include "json/json_spirit_value.h"

class CScrapesDB : public CDB
{
public:
    CScrapesDB(const char* pszMode="r+") : CDB("scrapes.dat", pszMode) { }
private:
    mutable CCriticalSection(cs);

    CScrapesDB(const CScrapesDB&);
    void operator=(const CScrapesDB);
public:
    bool WriteScrapeAddress(const std::string /*strAddress*/, const std::string /*strScrapeAddress*/);
    bool EraseScrapeAddress(const std::string /*strAddress*/);
    bool ReadScrapeAddress(const std::string /*strAddress*/, std::string &/*strScrapeAddress*/);
    bool DumpScrapeAddresses(json_spirit::Object &/*ScrapeAddresses*/);
    bool HasScrapeAddress(const std::string /*strAddress*/);
};

#endif // SCRAPESDB_H
