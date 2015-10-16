#include <boost/test/unit_test.hpp>

#include "init.h"
#include "util.h"
#include "walletdb.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(accounting_tests)

static void GetResults(CWalletDB& walletdb, std::map<int64, CAccountingEntry>& results)
{
    std::list<CAccountingEntry> aes;

    results.clear();
    BOOST_CHECK(walletdb.ReorderTransactions(pwalletMain) == DB_LOAD_OK);
    walletdb.ListAccountCreditDebit("", aes);
    BOOST_FOREACH(CAccountingEntry& ae, aes)
    {
        results[ae.nOrderPos] = ae;
    }
}

BOOST_AUTO_TEST_CASE(acc_basics)
{
    CWalletDB walletdb(pwalletMain->strWalletFile);
    vector<CWalletTx*> vpwtx;
    CWalletTx wtx;
    CAccountingEntry ae;
    list<CAccountingEntry> aes;
    map<int64, CAccountingEntry> results;

    int64 nTimeStart = 1333333333;
    int64 nTime = nTimeStart;

    ae.strAccount = "";
    ae.nCreditDebit = 1;
    ae.nTime = nTime;
    ae.strOtherAccount = "b";
    ae.strComment = "";

    BOOST_CHECK_EQUAL(walletdb.GetAccountCreditDebit(""), (int64)0);
    BOOST_CHECK(walletdb.GetAccountCreditDebit("") != (int64)1);

    walletdb.ListAccountCreditDebit("", aes);

    BOOST_CHECK_EQUAL(aes.size(), 0);
    BOOST_CHECK(aes.size() != 1);

    walletdb.WriteAccountingEntry(ae);

    BOOST_CHECK(walletdb.GetAccountCreditDebit("") != (int64)0);
    BOOST_CHECK_EQUAL(walletdb.GetAccountCreditDebit(""), (int64)1);

    GetResults(walletdb, results);
    BOOST_CHECK_EQUAL(1, results.size());
    // nOrderPos always starts with 1 so checking 0 returns a null value
    BOOST_CHECK_EQUAL(results[1].nTime, 1333333333);
    BOOST_CHECK(results[1].strComment.empty());
    BOOST_CHECK_EQUAL(results[1].strOtherAccount, "b");

    wtx.mapValue["comment"] = "z";
    pwalletMain->AddToWallet(wtx);
    vpwtx.push_back(&pwalletMain->mapWallet[wtx.GetHash()]);
    vpwtx[0]->nTimeReceived = (unsigned int)1333333335;
    vpwtx[0]->nOrderPos = -1;

    ae.nTime = 1333333336;
    ae.strOtherAccount = "c";
    ae.nOrderPos = -1;
    walletdb.WriteAccountingEntry(ae);

    BOOST_CHECK_EQUAL(walletdb.GetAccountCreditDebit(""), (int64)2);
    BOOST_CHECK(walletdb.GetAccountCreditDebit("") != (int64)9);

    GetResults(walletdb, results);
    BOOST_CHECK(pwalletMain->nOrderPosNext == 4);
    BOOST_CHECK_EQUAL(2, results.size());
    BOOST_CHECK_EQUAL(results[1].nTime, 1333333333);
    BOOST_CHECK(results[1].strComment.empty());
    BOOST_CHECK_EQUAL(2, vpwtx[0]->nOrderPos);
    BOOST_CHECK_EQUAL(results[3].nTime, 1333333336);
    BOOST_CHECK(results[3].strOtherAccount == "c");

    aes.clear();
    walletdb.ListAccountCreditDebit("", aes);
    BOOST_CHECK_EQUAL(aes.size(), 2);

    ae.nTime = 1333333330;
    ae.strOtherAccount = "d";
    ae.nOrderPos = pwalletMain->nOrderPosNext++;
    walletdb.WriteAccountingEntry(ae);

    GetResults(walletdb, results);
    BOOST_CHECK_EQUAL(results.size(), 3);
    BOOST_CHECK_EQUAL(pwalletMain->nOrderPosNext, 5);
    BOOST_CHECK_EQUAL(results[1].nTime, 1333333333);
    BOOST_CHECK_EQUAL(2 , vpwtx[0]->nOrderPos);
    BOOST_CHECK_EQUAL(results[3].nTime, 1333333336);
    BOOST_CHECK_EQUAL(results[4].nTime , 1333333330);
    BOOST_CHECK(results[4].strComment.empty());

    wtx.mapValue["comment"] = "y";
    --wtx.nLockTime;  // Just to change the hash :)
    pwalletMain->AddToWallet(wtx);
    vpwtx.push_back(&pwalletMain->mapWallet[wtx.GetHash()]);
    vpwtx[1]->nTimeReceived = (unsigned int)1333333336;

    wtx.mapValue["comment"] = "x";
    --wtx.nLockTime;  // Just to change the hash :)
    pwalletMain->AddToWallet(wtx);
    vpwtx.push_back(&pwalletMain->mapWallet[wtx.GetHash()]);
    vpwtx[2]->nTimeReceived = (unsigned int)1333333329;
    vpwtx[2]->nOrderPos = -1;

    GetResults(walletdb, results);

    BOOST_CHECK_EQUAL(results.size(), 3);
    BOOST_CHECK_EQUAL(pwalletMain->nOrderPosNext, 7);
    BOOST_CHECK_EQUAL(0, vpwtx[2]->nOrderPos);
    BOOST_CHECK_EQUAL(results[2].nTime, 1333333333);
    BOOST_CHECK_EQUAL(3, vpwtx[0]->nOrderPos);
    BOOST_CHECK_EQUAL(results[4].nTime, 1333333336);
    BOOST_CHECK_EQUAL(results[5].nTime, 1333333330);
    BOOST_CHECK(results[4].strComment.empty());
    BOOST_CHECK_EQUAL(6, vpwtx[1]->nOrderPos);

    ae.nTime = 1333333334;
    ae.strOtherAccount = "e";
    ae.nOrderPos = -1;
    walletdb.WriteAccountingEntry(ae);

    GetResults(walletdb, results);

    BOOST_CHECK_EQUAL(results.size(), 4);
    BOOST_CHECK_EQUAL(pwalletMain->nOrderPosNext, 8);
    BOOST_CHECK_EQUAL(0, vpwtx[2]->nOrderPos);
    BOOST_CHECK_EQUAL(results[2].nTime, 1333333333);
    BOOST_CHECK_EQUAL(3, vpwtx[0]->nOrderPos);
    BOOST_CHECK_EQUAL(results[4].nTime, 1333333336);
    BOOST_CHECK(results[4].strComment.empty());
    BOOST_CHECK_EQUAL(results[5].nTime, 1333333330);
    BOOST_CHECK(results[5].strComment.empty());
    BOOST_CHECK_EQUAL(results[6].nTime, 1333333334);
    BOOST_CHECK_EQUAL(7, vpwtx[1]->nOrderPos);
}

BOOST_AUTO_TEST_SUITE_END()
