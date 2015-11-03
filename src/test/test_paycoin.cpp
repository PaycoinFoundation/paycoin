#define BOOST_TEST_MODULE Paycoin Test Suite
#include <boost/test/unit_test.hpp>

#include "main.h"
#include "scrapesdb.h"
#include "wallet.h"

int MIN_PROTO_VERSION = 70002;

CWallet* pwalletMain;
CScrapesDB* scrapesDB;

extern bool fPrintToConsole;
struct TestingSetup {
    TestingSetup() {
        fPrintToConsole = true; // don't want to write to debug.log file
        pwalletMain = new CWallet();
        bitdb.MakeMock();
        LoadBlockIndex(true);
        bool fFirstRun;
        pwalletMain = new CWallet("wallet.dat");
        pwalletMain->LoadWallet(fFirstRun);
        RegisterWallet(pwalletMain);
        scrapesDB = new CScrapesDB("cw");
    }
    ~TestingSetup()
    {
        delete pwalletMain;
        pwalletMain = NULL;
        bitdb.Flush(true);
    }
};

BOOST_GLOBAL_FIXTURE(TestingSetup);

void Shutdown(void* parg)
{
  exit(0);
}

void StartShutdown()
{
  exit(0);
}
