#include <boost/test/unit_test.hpp>

#include "base58.h"
#include "main.h"
#include "primenodes.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(primenode_tests)

BOOST_AUTO_TEST_CASE(primenode_validity)
{
    // Use the testnet keys so that we can perform signature tests.
    fTestNet = true;

    CScript scriptPubKeyTypeValid;
    CScript scriptPubKeyTypeInvalid;
    CScript scriptPubKeyAddress;
    CScript scriptMicroPrimeOP;
    string strMicroPrimeValid = "muVEJW5YZpZc4QxUaDMJVxcy1vQcMrPhmQ";
    string strMicroPrimeInvalid = "mnKXnp4kCNM79pjiPSEB7oD59jken6pWq5";

    unsigned int nTime = GetTime();
    scriptMicroPrimeOP << OP_MICROPRIME;

    // Generic testnet private key
    string strPrivKey = "308201130201010420de934fbd46ef6f57d68562a912829c0cd4d04378bd27d41be53da572aac44645a081a53081a2020101302c06072a8648ce3d0101022100fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f300604010004010704410479be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8022100fffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141020101a1440342000451d8cafe5ab366128835d1280d9f8b534d17320a22193179e0f99299c63a11796f24673e42752a71940355c8698b31cbc73b5bea025d6471996ed37da72961a9";
    vector<unsigned char> vchPrivKey = ParseHex(strPrivKey);
    // Valid format generates proper script type even if invalid key
    BOOST_CHECK(NewScriptPrimeID(scriptPubKeyTypeInvalid, vchPrivKey, nTime));

    // One of the 2 testnet primenode keys.
    strPrivKey = "3082011302010104202ac1e3a01bd7daa92eb945e7b524a4e6729587c15b20a01e54e3893a3a6188b5a081a53081a2020101302c06072a8648ce3d0101022100fffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f300604010004010704410479be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8022100fffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141020101a14403420004d445518d115243639d0dfd057a99da588e8334039ce674f177943d4c660957c810f924a5371a352b1e827121846500a588a4dc47dc6d5d9e5317dfa48c562aa7";
    vchPrivKey.clear();
    vchPrivKey = ParseHex(strPrivKey);
    BOOST_CHECK(NewScriptPrimeID(scriptPubKeyTypeValid, vchPrivKey, nTime));

    primeNodeDB = new CPrimeNodeDB("cr");
    CPrimeNodeDBEntry entry;

    // Empty database, returns false.
    BOOST_CHECK(!primeNodeDB->IsPrimeNodeKey(scriptPubKeyTypeValid, nTime, entry));
    BOOST_CHECK(!primeNodeDB->IsPrimeNodeKey(scriptPubKeyTypeInvalid, nTime, entry));
    BOOST_CHECK(!primeNodeDB->CheckMicroPrime(strMicroPrimeValid));
    BOOST_CHECK(!primeNodeDB->CheckMicroPrime(strMicroPrimeInvalid));

    // Inflate just the microprime database.
    InflatePrimeNodeDB(CPrimeNodeDB::microdb);
    // Database is only inflated with microprime keys, still return false.
    BOOST_CHECK(!primeNodeDB->IsPrimeNodeKey(scriptPubKeyTypeValid, nTime, entry));

    BOOST_CHECK(primeNodeDB->CheckMicroPrime(strMicroPrimeValid));
    BOOST_CHECK(!primeNodeDB->CheckMicroPrime(strMicroPrimeInvalid));

    // Inflate the primenode side of the database.
    InflatePrimeNodeDB(CPrimeNodeDB::primedb);
    BOOST_CHECK(primeNodeDB->IsPrimeNodeKey(scriptPubKeyTypeValid, nTime, entry));
    BOOST_CHECK(!primeNodeDB->IsPrimeNodeKey(scriptPubKeyTypeInvalid, nTime, entry));

    CBitcoinAddress addr(strMicroPrimeValid);
    scriptPubKeyAddress.SetDestination(addr.Get());

    CTransaction tx;
    BOOST_CHECK(tx.IsPrimeStake(scriptMicroPrimeOP, scriptPubKeyAddress, nTime, 5000 * COIN, 0, 0));
    // Value in exceeds max stakeable balance of address (microPrimeGroup)
    BOOST_CHECK(!tx.IsPrimeStake(scriptMicroPrimeOP, scriptPubKeyAddress, nTime, 5000 * COIN + 1, 0, 0));
    // Value in is too low for microprime after given date.
    BOOST_CHECK(!tx.IsPrimeStake(scriptMicroPrimeOP, scriptPubKeyAddress, MICROPRIMES_STAGGER_DOWN, 5000 * COIN - 1, 0, 0));
    // Excessive reward.
    BOOST_CHECK(!tx.IsPrimeStake(scriptMicroPrimeOP, scriptPubKeyAddress, nTime, 4000 * COIN, 6000 * COIN, 0));

    // Invalid microprime address.
    addr = CBitcoinAddress(strMicroPrimeInvalid);
    scriptPubKeyAddress.clear();
    scriptPubKeyAddress.SetDestination(addr.Get());
    BOOST_CHECK(!tx.IsPrimeStake(scriptMicroPrimeOP, scriptPubKeyAddress, nTime, 4000 * COIN, 0, 0));

    // Sign a script with an old primenode OP code.
    CKey key;
    key.SetPrivKey(CPrivKey(vchPrivKey.begin(), vchPrivKey.end()));
    CScript scriptTime;
    scriptTime << nTime;
    uint256 hashScriptTime = Hash(scriptTime.begin(), scriptTime.end());
    vector<unsigned char> vchSig;
    CScript scriptPubKeyTypeOld;
    key.Sign(hashScriptTime, vchSig);
    scriptPubKeyTypeOld << OP_PRIMENODE350 << vchSig;
    // Returns false when processing the OP code (without checking anything else)
    BOOST_CHECK(!tx.IsPrimeStake(scriptPubKeyTypeOld, scriptPubKeyAddress, nTime, 0, 0, 0));
    // Returns false at signature check
    BOOST_CHECK(!tx.IsPrimeStake(scriptPubKeyTypeInvalid, scriptPubKeyAddress, nTime, 0, 0, 0));

    /* Can't test database ranges because it's impossible to get a valid signature
     * from IsPrimeNodeKey with the nTime being so far off from something real. */

    // Returns false at MINIMUM_FOR_PRIMENODE check
    BOOST_CHECK(!tx.IsPrimeStake(scriptPubKeyTypeValid, scriptPubKeyAddress, nTime, 0, MINIMUM_FOR_PRIMENODE_PHASE2 - 1, 0));
    BOOST_CHECK(!tx.IsPrimeStake(scriptPubKeyTypeOld, scriptPubKeyAddress, END_PRIME_PHASE_ONE - 1000, 0, MINIMUM_FOR_PRIMENODE_PHASE1 - 1, 0));
    // Return false at coin age / reward check
    BOOST_CHECK(!tx.IsPrimeStake(scriptPubKeyTypeValid, scriptPubKeyAddress, nTime, 0, MINIMUM_FOR_PRIMENODE_PHASE2, 0));
    // Pass
    BOOST_CHECK(tx.IsPrimeStake(scriptPubKeyTypeValid, scriptPubKeyAddress, nTime, MINIMUM_FOR_PRIMENODE_PHASE2 - 10000, MINIMUM_FOR_PRIMENODE_PHASE2, 500));

    fTestNet = false;
}

BOOST_AUTO_TEST_SUITE_END()
