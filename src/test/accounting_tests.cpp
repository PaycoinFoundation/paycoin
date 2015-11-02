#include <boost/test/unit_test.hpp>

#include "init.h"
#include "util.h"
#include "walletdb.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(accounting_tests)

BOOST_AUTO_TEST_CASE(acc_basics)
{
    CWalletDB walletdb(pwalletMain->strWalletFile);
    vector<CWalletTx*> vpwtx;
    CWalletTx wtx;
    CAccountingEntry ae;
    list<CAccountingEntry> aes;

    int64 nTimeStart = 1443808862;
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

    nTime = nTime + (24 * 60 * 60);
    ae.nTime = nTime;
    walletdb.WriteAccountingEntry(ae);

    BOOST_CHECK_EQUAL(walletdb.GetAccountCreditDebit(""), (int64)2);
    BOOST_CHECK(walletdb.GetAccountCreditDebit("") != (int64)9);

    aes.clear();
    walletdb.ListAccountCreditDebit("", aes);
    BOOST_CHECK_EQUAL(aes.size(), 2);

    nTime = nTime + (24 * 60 * 60);
    for (int i = 0; i < 8; i++) {
        nTime = nTime + (24 * 60 * 60 * i);
        ae.nTime = nTime;
        walletdb.WriteAccountingEntry(ae);
    }

    BOOST_CHECK_EQUAL(walletdb.GetAccountCreditDebit(""), (int64)10);

    aes.clear();
    walletdb.ListAccountCreditDebit("", aes);
    BOOST_CHECK_EQUAL(aes.size(), 10);

    ae.nCreditDebit = 10;
    walletdb.WriteAccountingEntry(ae);

    BOOST_CHECK_EQUAL(walletdb.GetAccountCreditDebit(""), (int64)20);

    aes.clear();
    walletdb.ListAccountCreditDebit("", aes);
    BOOST_CHECK_EQUAL(aes.size(), 11);

    map<int, CAccountingEntry> entries;
    int i = 0;
    BOOST_FOREACH(CAccountingEntry &ae, aes) {
        entries[i] = ae;
        i++;
    }

    BOOST_CHECK_EQUAL(entries[0].nTime, 1443808862);
    BOOST_CHECK_EQUAL(entries[4].nTime, 1444240862);
    BOOST_CHECK_EQUAL(entries[10].nTime, 1446400862);
}

BOOST_AUTO_TEST_SUITE_END()
