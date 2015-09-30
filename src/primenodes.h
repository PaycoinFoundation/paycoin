// Copyright (c) 2015 The Paycoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef PRIMENODES_H
#define PRIMENODES_H

#include "db.h"
#include "script.h"

bool initPrimeNodes(std::string &/*ret*/);
void WritePrimeNodeDB();
void WriteMicroPrimeDB();
void WriteTestMicroPrimeDB();

/* This is used to unseralize the a database entry retaining all of the the
 * primenode information */
class CPrimeNodeDBEntry
{
public:
    std::string key;
    int primeNodeRate;
    unsigned int valid_starting;
    unsigned int valid_until;

    CPrimeNodeDBEntry()
    {
        SetNull();
    }

    void SetNull()
    {
        key.clear();
        primeNodeRate = 0;
        valid_starting = 0;
        valid_until = 0;
    }

    IMPLEMENT_SERIALIZE
    (
        READWRITE(primeNodeRate);
        READWRITE(valid_starting);
        READWRITE(valid_until);
    )
};

class CPrimeNodeDB : public CDB
{
public:
    CPrimeNodeDB(const char* pszMode="r+") : CDB("primenodes.dat", pszMode) { }
private:
    CPrimeNodeDB(const CPrimeNodeDB&);
    void operator=(const CPrimeNodeDB);
public:
    bool WritePrimeNodeKey(const std::string /*key*/, int /*primeNodeRate*/, unsigned int /*valid_starting*/, unsigned int /*valid_until*/);
    bool WriteMicroPrimeAddr(const std::string /*address*/, int64 /*group*/, int /*primeNodeRate*/);
    bool IsPrimeNodeKey(CScript /*scriptPubKeyType*/, unsigned int /*nTime*/, CPrimeNodeDBEntry &/*entry*/);
    bool IsMicroPrime(CScript /*scriptPubKeyAddress*/, int &/*primeNodeRate*/, int64 &/*group*/);
    bool CheckPrimeNodeKey(const std::string /*key*/);
    bool CheckMicroPrime(const std::string /*address*/);
    bool CheckMicroPrime(CScript /*scriptPubKeyAddress*/);
};

extern CPrimeNodeDB* primeNodeDB;

#endif // PRIMENODES_H
