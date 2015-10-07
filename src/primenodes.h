// Copyright (c) 2015 The Paycoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef PRIMENODES_H
#define PRIMENODES_H

#include "db.h"
#include "script.h"

// Used for stake confirmation
static const int64 MINIMUM_FOR_PRIMENODE_PHASE1 = 125000 * COIN;
static const int64 MINIMUM_FOR_PRIMENODE_PHASE2 = 160000 * COIN;
/* Used ONLY in wallet.cpp for stake generation checks (should always be set
 * to the CURRENT MINIMUM_FOR_PRIMENODE) */
static const int64 MINIMUM_FOR_PRIMENODE = MINIMUM_FOR_PRIMENODE_PHASE2;

static const unsigned int END_PRIME_PHASE_ONE = 1435752000; // Wed, 01 Jul 2015 12:00:00 GMT

static const int PRIME_NODE_RATE = 25;

bool initPrimeNodes(std::string &/*ret*/);

bool NewScriptPrimeID(CScript &/*scriptPrimeID*/, std::vector<unsigned char> /*vchPrivKey*/, unsigned int /*nTime*/);

/* This is used to unseralize a database entry retaining all of the
 * primenode information */
class CPrimeNodeDBEntry
{
public:
    std::string key;
    unsigned int valid_starting;
    unsigned int valid_until;

    CPrimeNodeDBEntry()
    {
        SetNull();
    }

    void SetNull()
    {
        key.clear();
        valid_starting = 0;
        valid_until = 0;
    }

    IMPLEMENT_SERIALIZE
    (
        READWRITE(valid_starting);
        READWRITE(valid_until);
    )
};

class CPrimeNodeDB : public CDB
{
public:
    enum dbtype {
        nodb,
        primedb,
        microdb,
        fulldb
    };

    CPrimeNodeDB(const char* pszMode="r+") : CDB("primenodes.dat", pszMode) { }
private:
    mutable CCriticalSection cs;

    CPrimeNodeDB(const CPrimeNodeDB&);
    void operator=(const CPrimeNodeDB);

    bool WritePrimeNodeKey(const std::string /*key*/, unsigned int /*valid_starting*/, unsigned int /*valid_until*/);
    bool WriteMicroPrimeAddr(const std::string /*address*/, int64 /*group*/);
    bool WritePrimeNodeDBVersion(int /*version*/);
public:
    void WritePrimeNodeDB();
    void WriteMicroPrimeDB();
    void WriteTestMicroPrimeDB();

    bool CheckPrimeNodeDBVersion(int &/*version*/);

    bool IsPrimeNodeKey(CScript /*scriptPubKeyType*/, unsigned int /*nTime*/, CPrimeNodeDBEntry &/*entry*/);
    bool IsMicroPrime(CScript /*scriptPubKeyAddress*/, int &/*primeNodeRate*/, int64 &/*group*/, unsigned int /*nTime*/);
    bool CheckPrimeNodeKey(const std::string /*key*/);
    bool CheckMicroPrime(const std::string /*address*/);
    bool CheckMicroPrime(CScript /*scriptPubKeyAddress*/);
};

void InflatePrimeNodeDB(CPrimeNodeDB::dbtype /*db*/);

extern CPrimeNodeDB* primeNodeDB;

#endif // PRIMENODES_H
