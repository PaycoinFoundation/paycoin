#include <boost/test/unit_test.hpp>

#include "main.h"
#include "wallet.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(transaction_tests)

BOOST_AUTO_TEST_CASE(basic_transaction_tests)
{
    // Random real transaction (3a22a7c759e489356604a07295658d9e289896b68e56f22c26a85b69985e616b)
    unsigned char ch[] = {0x01, 0x00, 0x00, 0x00, 0xe5, 0xf5, 0x98, 0x54, 0x01, 0x3e, 0x8e, 0x12, 0xf0, 0xb0, 0x7f, 0xdd, 0x35, 0x06, 0x5e, 0x3e, 0x3d, 0xee, 0xaa, 0xb2, 0xcc, 0x3d, 0xeb, 0xc1, 0x89, 0xd6, 0xbf, 0xd8, 0x0b, 0xe6, 0x17, 0xf7, 0xc9, 0x12, 0x90, 0x92, 0xce, 0x01, 0x00, 0x00, 0x00, 0x4a, 0x49, 0x30, 0x46, 0x02, 0x21, 0x00, 0xed, 0xeb, 0x0b, 0xa6, 0x47, 0x72, 0x1a, 0x7c, 0x7a, 0x0c, 0xa4, 0xb6, 0x39, 0x84, 0xff, 0xdb, 0x75, 0x4b, 0xaa, 0xa7, 0x6b, 0x52, 0x5b, 0x3a, 0xf8, 0xee, 0xc5, 0x7b, 0x40, 0x67, 0x58, 0x48, 0x02, 0x21, 0x00, 0x82, 0xc8, 0xbe, 0x1e, 0x44, 0x43, 0x22, 0xa4, 0xde, 0xad, 0x90, 0xb9, 0xcd, 0xba, 0x54, 0xcd, 0xaf, 0x73, 0xbe, 0x38, 0xd5, 0x69, 0xd5, 0x70, 0x12, 0xc7, 0xb6, 0xec, 0x8e, 0xb5, 0xcc, 0x88, 0x01, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0xa9, 0x6f, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x23, 0x21, 0x03, 0x64, 0x76, 0xec, 0xbe, 0x03, 0x7c, 0xa1, 0xf8, 0x41, 0x1f, 0xdf, 0x04, 0x25, 0x9c, 0x07, 0xe9, 0x95, 0xd0, 0x50, 0x51, 0xd3, 0x45, 0x65, 0x21, 0x45, 0x58, 0xf2, 0xc6, 0xa0, 0x0e, 0x7c, 0x95, 0xac, 0x70, 0xca, 0x6f, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x23, 0x21, 0x03, 0x64, 0x76, 0xec, 0xbe, 0x03, 0x7c, 0xa1, 0xf8, 0x41, 0x1f, 0xdf, 0x04, 0x25, 0x9c, 0x07, 0xe9, 0x95, 0xd0, 0x50, 0x51, 0xd3, 0x45, 0x65, 0x21, 0x45, 0x58, 0xf2, 0xc6, 0xa0, 0x0e, 0x7c, 0x95, 0xac, 0x00, 0x00, 0x00, 0x00, 0x00};
    vector<unsigned char> vch(ch, ch + sizeof(ch) -1);
    CDataStream stream(vch, SER_DISK, CLIENT_VERSION);
    CTransaction tx;
    stream >> tx;
    BOOST_CHECK_MESSAGE(tx.CheckTransaction(), "Simple deserialized transaction should be valid.");

    // Check that duplicate txins fail
    tx.vin.push_back(tx.vin[0]);
    BOOST_CHECK_MESSAGE(!tx.CheckTransaction(), "Transaction with duplicate txins should be invalid.");
}

//
// Helper: create two dummy transactions, each with
// two outputs.  The first has 11 and 50 CENT outputs
// paid to a TX_PUBKEY, the second 21 and 22 CENT outputs
// paid to a TX_PUBKEYHASH.
//
static std::vector<CTransaction>
SetupDummyInputs(CBasicKeyStore& keystoreRet, MapPrevTx& inputsRet)
{
    std::vector<CTransaction> dummyTransactions;
    dummyTransactions.resize(2);

    // Add some keys to the keystore:
    CKey key[4];
    for (int i = 0; i < 4; i++)
    {
        key[i].MakeNewKey(i % 2);
        keystoreRet.AddKey(key[i]);
    }

    // Create some dummy input transactions
    dummyTransactions[0].vout.resize(2);
    dummyTransactions[0].vout[0].nValue = 11*CENT;
    dummyTransactions[0].vout[0].scriptPubKey << key[0].GetPubKey() << OP_CHECKSIG;
    dummyTransactions[0].vout[1].nValue = 50*CENT;
    dummyTransactions[0].vout[1].scriptPubKey << key[1].GetPubKey() << OP_CHECKSIG;
    inputsRet[dummyTransactions[0].GetHash()] = make_pair(CTxIndex(), dummyTransactions[0]);

    dummyTransactions[1].vout.resize(2);
    dummyTransactions[1].vout[0].nValue = 21*CENT;
    dummyTransactions[1].vout[0].scriptPubKey.SetDestination(key[2].GetPubKey().GetID());
    dummyTransactions[1].vout[1].nValue = 22*CENT;
    dummyTransactions[1].vout[1].scriptPubKey.SetDestination(key[3].GetPubKey().GetID());
    inputsRet[dummyTransactions[1].GetHash()] = make_pair(CTxIndex(), dummyTransactions[1]);

    return dummyTransactions;
}

BOOST_AUTO_TEST_CASE(test_Get)
{
    CBasicKeyStore keystore;
    MapPrevTx dummyInputs;
    std::vector<CTransaction> dummyTransactions = SetupDummyInputs(keystore, dummyInputs);

    CTransaction t1;
    t1.vin.resize(3);
    t1.vin[0].prevout.hash = dummyTransactions[0].GetHash();
    t1.vin[0].prevout.n = 1;
    t1.vin[0].scriptSig << std::vector<unsigned char>(65, 0);
    t1.vin[1].prevout.hash = dummyTransactions[1].GetHash();
    t1.vin[1].prevout.n = 0;
    t1.vin[1].scriptSig << std::vector<unsigned char>(65, 0) << std::vector<unsigned char>(33, 4);
    t1.vin[2].prevout.hash = dummyTransactions[1].GetHash();
    t1.vin[2].prevout.n = 1;
    t1.vin[2].scriptSig << std::vector<unsigned char>(65, 0) << std::vector<unsigned char>(33, 4);
    t1.vout.resize(2);
    t1.vout[0].nValue = 90*CENT;
    t1.vout[0].scriptPubKey << OP_1;

    BOOST_CHECK(t1.AreInputsStandard(dummyInputs));
    BOOST_CHECK_EQUAL(t1.GetValueIn(dummyInputs), (50+21+22)*CENT);

    // Adding extra junk to the scriptSig should make it non-standard:
    t1.vin[0].scriptSig << OP_11;
    BOOST_CHECK(!t1.AreInputsStandard(dummyInputs));

    // ... as should not having enough:
    t1.vin[0].scriptSig = CScript();
    BOOST_CHECK(!t1.AreInputsStandard(dummyInputs));
}

BOOST_AUTO_TEST_CASE(test_GetThrow)
{
    CBasicKeyStore keystore;
    MapPrevTx dummyInputs;
    std::vector<CTransaction> dummyTransactions = SetupDummyInputs(keystore, dummyInputs);

    MapPrevTx missingInputs;

    CTransaction t1;
    t1.vin.resize(3);
    t1.vin[0].prevout.hash = dummyTransactions[0].GetHash();
    t1.vin[0].prevout.n = 0;
    t1.vin[1].prevout.hash = dummyTransactions[1].GetHash();;
    t1.vin[1].prevout.n = 0;
    t1.vin[2].prevout.hash = dummyTransactions[1].GetHash();;
    t1.vin[2].prevout.n = 1;
    t1.vout.resize(2);
    t1.vout[0].nValue = 90*CENT;
    t1.vout[0].scriptPubKey << OP_1;

    BOOST_CHECK_THROW(t1.AreInputsStandard(missingInputs), runtime_error);
    BOOST_CHECK_THROW(t1.GetValueIn(missingInputs), runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()
