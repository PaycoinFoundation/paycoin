// Copyright (c) 2015 The Paycoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "main.h"
#include "primekeys.h"
#include "script.h"

#include <ctime>

std::vector<std::string> pubKeyList350;
std::vector<std::string> pubKeyList100;
std::vector<std::string> pubKeyList20;
std::vector<std::string> pubKeyList10;
std::vector<std::string> pubKeyListP2;
bool pubKeyListsInitialized = false;
bool p2pubKeyListsInitialized = false;

void getPrimePubKeyList(unsigned char primeType, std::vector<std::string> &pubKeyList, int &primeNodeRate) {
    if (!pubKeyListsInitialized) initPrimePubKeyLists();
    /* Reload the Phase 2 keys everytime they're needed until after the
     * end of the Phase 2 distribution.  We pad this with an extra 10
     * minutes to insure the correct list is loaded for machines that
     * may be processing a transaction a few minutes behind the others. */
    if (!p2pubKeyListsInitialized
        || (time(NULL) < (END_PRIME_PHASE_ONE + ((60 * 60 * 24 * 7 * 25) + (60 * 10)))))
            initPrimeP2PubKeyLists();

    switch (primeType) {
    case OP_PRIMENODE350:
        primeNodeRate = 350;
        pubKeyList = pubKeyList350;
        break;

    case OP_PRIMENODE100:
        primeNodeRate = 100;
        pubKeyList = pubKeyList100;
        break;

    case OP_PRIMENODE20:
        primeNodeRate = 20;
        pubKeyList = pubKeyList20;
        break;

    case OP_PRIMENODE10:
        primeNodeRate = 10;
        pubKeyList = pubKeyList10;
        break;

    case OP_PRIMENODEP2:
        primeNodeRate = 25;
        pubKeyList = pubKeyListP2;
        break;
    }
}

void initPrimePubKeyLists() {
    pubKeyListsInitialized = true;

    pubKeyList350.push_back("0427096f2e3123970010d97a1f0e210499435482927b12b1d6a209f0c383e03b444a244e372cad494c144b47ac3686fc4feea2aec2df3ba77f41cc27dbf8f3c4ff");
    pubKeyList350.push_back("04d96b945eca3ea23e1dfd414d2a4772c66e6c7297d0d4f88b7a3b7c285931c36f16ef26299704d49bda770621d9145d96365e02380b4329aceafe7b81012bef48");
    pubKeyList350.push_back("040057901e3de5e6429912047c2b5175dde2586b981397a0e434d43accf2e49c108fb3361b3957fcbbfa39930d50aeff56c690e91ffb2d953eefa46aa50fcb6917");
    pubKeyList350.push_back("0486022d6dd5c8d17c411cf28add879e5c738b64090e83a43cca1699ececdb8f3524379aa71bb76a2af2d7e8294c9d7b8179d98215afe589c921e4507f63c5c802");
    pubKeyList350.push_back("0436639ad108f7630881fb3af5f540ded3bb4653dab695f1716e71ea5838bcee7c238fa624bc2f1bfe0990cea4c3ee3e9f949bbc61e347b5887815eb51468b5c88");
    pubKeyList350.push_back("04d04183c8caad2f41edffbabd5b6a266e886457ef0621283b3418979d841bc2425e6b273ce0ea2b461b9797a7d3edd74a4407af9995a9702018cf69df8eee6aba");
    pubKeyList350.push_back("04a8b4a8c55361f37cad732da49b2bccadb9be522dd84f9c2329a7dbfaac8c5dd093b803d791719c413196694c97fcb360b7935034dcc4b1b3c2e45a39e67b8dd6");
    pubKeyList350.push_back("04b7930cd8bda83097841cfa0a2b5317ecc029a512bbf056a130421ee500773f16850f74e2cbffa4e8aa2a0b0a25009ea619e49839e8608db4469de285d6ee781d");
    pubKeyList350.push_back("04d0e3e0e688659d07d4510e25a9884c12931e581b8a2bcdd8ad6c4362ae219b08089761e88e17109aa6618dfca152f854e880ca66414d7f8e5d1d95e70dc95dee");
    pubKeyList350.push_back("04025f944a31226086da4f0f49188bfe12d29a304986d909b00560a5f8c84c09ab0f6d0e16926d42a07eaa522dad74404ef25ca863fbd78d45ecdb6da282caf9da");
    pubKeyList350.push_back("04983ebed643535907ebbea93387ca38c262778d21dab385f0d0c5dc49b66ebe54c27d9e318ea2798800a067dc3ad8e414684d477e7633f261b08522a0f81b3c5e");
    pubKeyList350.push_back("04512b7f555a89e73cd1f9d5138d8e46b81c49a184e0cb7b538167e046dea93689101f076c59874c085642b33b2ad58ff1dee34ffa1d03880c0272686291bd64b5");
    pubKeyList350.push_back("045f46a60dd9c3c3e68a127aee68a4ad59d303f9cfe91e2015156fe25a42687855a6de4ccb53756f06e7c3cf66e295fd84d8c3c0fd73c7cee44966aaae3d033652");
    pubKeyList350.push_back("049a0e427b86663cc928d6475d0e591fd6dbaf686e2b6a140e79e646fbaa0c88481984f61de390c9fc73c9f58d2c26bd8bdadbdd400a8cc96b4d7a6f52fbe1209d");
    pubKeyList350.push_back("040da5d570e39531f25ae747a1698d67470c0d7fb4941f104d081235f7425cefb95b5eca24daf80a732cb267bd13d47b62ce4102394c180b2a792216f4a087d320");
    pubKeyList350.push_back("04672dbddcb26bc82028652a5ff042f98c5c5f58f7330d49ad4a22268f9a93e2cca8ce2ed7a93012b83903f4ddcef5f1a0ea5fb90df3ae38528489d9b69cd0dd39");
    pubKeyList350.push_back("04fb8a251640f766ec63aee35f74f49e46b5ae7f61f7bcabe6103d13ab56086c884c525b96e10741704a3c44982aa9c6577184f0259a36f18e4ca8325ff2cd8330");
    pubKeyList350.push_back("04f9644ebc672e382eb45a82e221f2ab9d5124fea1de7de2d417c863ddd760c5c778f8fe39e09e7937ac99172a3a9d0b013020c1256b935da171b66864a1e16b9c");
    pubKeyList350.push_back("048a58fe8de7c123f6f816667fb1bfe6d99b9f0ac415bde1fdf4e9725fc80d2699c30b362faf992cd00edb586df9f459081c3f586becbabdd33bdd8becf31f85c2");
    pubKeyList350.push_back("0475a43388b6023722d93c03128541b3877153736a9ac7f48bf1d1a37e46aa1381a450aa0a6c40e2f4e317a4212c37c18bd1cf99ea3f70ecec83c30f4ceca65201");
    pubKeyList350.push_back("04bf85a4920b6fb89868fac40c4917af40546867221f2da2de84b9a9f26c569cee689c2eafe0c911c31ac88d9005badb8f32fb0650ffe2e272194ef5df162b35ac");
    pubKeyList350.push_back("04e75eda3a94f74d684a7239b8c6cc056e75fba2690888855f81810c439270265f4c3c46c3aedfaff81da2dfb236e091cc36b5759e6a0513898ad443cf91ff6631");
    pubKeyList350.push_back("04c62eb46a011e45f0069d8881894ac22889988b384ba7234c5caeed42d4f11d16e2ba0b55198cec0a0a710714d0602e1ccaada5284ae07fa0ae43b0cb1e7d59b1");
    pubKeyList350.push_back("043d60413953d4a9e144d86390c8ddb51b674df65ce1a05a26e400b3bc27cbc55c6c6b05d5030e60dfe59101dc9614e4298c33716be751feb0d494a788e00ad627");
    pubKeyList350.push_back("041c10a07fa1799e8d43d4a0b74b89614722fabcfd90dac380d170ebfddd0b5f0462e67c0704172cbe925c77c1890af68000d44fed56d628cceea6101fcaf74d38");
    pubKeyList350.push_back("04640a129ecf82ed28875881c28f59bf46b82aba8e8be77ad39bb1dd0ffd7944f49da4dc3de9cac50d88763167583b030d7df0e234e8a6e9de725aa337fcb1f0ed");
    pubKeyList350.push_back("04e5cba6da1d31076d42db494613e6c8587ba4252693c8d8dbcdae033479e8cab10921c147b91127ef4b36d0209a8de917f3c51fd231b07acdcce47d0ac3a14de8");
    pubKeyList350.push_back("0479502526431508d1edcb054bfb49dfed971e144ff1d3d89384f1af8c95a2ee3d6f296cade67c2dfb8c43b324ed6cc079395a5ec4118f0b8c5737fe8988d4ecfc");
    pubKeyList350.push_back("04048059da03e2ecca976fb0c8e8ea408ea3a8e2b45c55c9ee095011077ded701f9b8639b265e1dc1eb0ac08f990f67b99da03f4bb5c68bef182488d49f5e27762");
    pubKeyList350.push_back("04f3b1f9c8b07034eb3f7f609d150561ee4ae05a1051816060974221f5c36a1e3db4b79b46146da9bae303648dbf94bf740ad41d6e3297eeae6829bd2d9f3e3a5e");
    pubKeyList350.push_back("048f400e748d54d8fdf148a270adcb7aa4b73c9d49f3c8bbdf57df6a8a349c54abaae8e223bab43cb1770e8a80c00cb11904e301f32ea0aeec5d59ce8a9b9dc5c1");
    pubKeyList350.push_back("04cf206b074a8da673f6b06cdbd28b82253ef4b4aeb6689745bf9e42a5d9007269b18a3ba5becfabb3a2d5f7b4e84ad9f6d6283856fc315ddf4fd8e5797a4d8be7");
    pubKeyList350.push_back("04ae324ce3d313a42a76ec17f09625185c53bfa99c5f06920105291bea676220203d3f1b7c0de605c2bbcaa760a632f5b9a55dd86d8f36b6b985932d61a9a88946");
    pubKeyList350.push_back("040ba9aeeff11561fa33827d17957fc40ed5b1b8d260140535e0350ba431609abf3a31166a9e014d26553520f59de730dbcf5944fb433d1abfadb3f4f30668ab48");
    pubKeyList350.push_back("0416683a0796c3dfda8065c6011a61747488345bf0a0f559836104b4e9074e6c40b206797850603862baac60ba61bea930db1f2b4362c117d54472dc2a8b93bbd4");

    pubKeyList100.push_back("046ebc739ff7d6a0dbb3ae9bb9260a17b9d2fc40ca77d9c018784834ef863414c17b4fd3a580d9721ec0ee12c823f1eb48821b8135cd32aee26ba3be9cb22f7a31");
    pubKeyList100.push_back("04ffcd9e3acffbd40d6472f354e76f03a5c806623a5fbe341796b92e71ad59f5c4a4ad5f04c4fe7d6e50f6546d361a06020f8670eae020e8a7a1d036155e75d10a");
    pubKeyList100.push_back("04a61c5b67927c4a0389baa1089a87a93d60fbf15cc345823097245d0c331525d273a03544720f3a4e8f9afb443793f3ea595d5f0af7e17d764385750a9eb54d19");
    pubKeyList100.push_back("04f9f78f1dcdb6f76ba0a962aba3058a605691e2ecd63e16b5e0e39d19c5821f8eda421d06b4bf1159bcee989f01b273a4337ba0bc9fc749ef35c32e6e4a7bc1e9");
    pubKeyList100.push_back("0444b7d2aa1b9c74710325735df89692d1fa686a3a67d95462cbf4cb0d8f47eb9ac18da92bcce99b58e1be020c36736d9a1f85fa191c2ddcc779c53c4ede7c73b9");
    pubKeyList100.push_back("0426bbbd25a4dc0a295b64d4f1d3787d39cba04534109cd145c5229a8cc3285d097462131dd6fa1968eb510d53fee8a012250390ef6149c2003784f5585fef97a2");
    pubKeyList100.push_back("04ab438d669c7ed7db2e0eef61bd7ae4937ac32347d39adfb204f4d6e4e2a5adfa4548f69dc4cdc2ff3da0506e9382f69175138163328d445f110081dfa5d5d416");
    pubKeyList100.push_back("04406932519cd5e47333a049922eb8bcddc6b722c31440f36ca2851e119314b375914b08c635837e47c7cbf6ace95acbadee62acb054551bc4255c81d03c485e95");
    pubKeyList100.push_back("0454d677fbe06d5f56920db9bd124015edfd1fb32786c88a1a15cf0a84204d4386bd48fb31239eb3e594b13ca952b3c5f25aca9f3f702ad5b0120160dc355a6fbd");
    pubKeyList100.push_back("0452f030183dffd2b53d639b16488bd451ba2dc9d1791464300f28abf5414036530735b6a8de119443e3875f2e67514b6b2678ed3966629d354e6aabdb8251ed19");

    pubKeyList20.push_back("04ce27308191e2e0274459bb191ba2cb93ef4dc8a838e8e8310083fcf7e2be9c7c20b3b15e2dc2a1482275ee55138c2350771231b00d7740e1e495269987faa24b");
    pubKeyList20.push_back("04311cc5333eeadbb3b18f6c70832df159796b1872bfa66bf214030ced65f8a33c4c6b4da48ffebb111a09129b337c9ed5129256995a4fa315fab3b81666cf2bad");

    pubKeyList10.push_back("0428588850c9361e7f5848807ef40ac839d5cd664db6183cbc53f63b0e8682a5b4b6caa6782db2b314e3cab43503f05df280b9e98e82b2235a00e4dd24997b49a0");
    pubKeyList10.push_back("04bf2832da17137215912a1173b3ad2675e1b03c4df22bb93f2f2fdb92bdd0097e0a267d8813799fe335d1b80ff23fa48809dea4517211b48eacadc85147d5c643");
    pubKeyList10.push_back("04c8ad33bb094d7bee52ec9d08e4eea8ef33d49c1d871e6a4ee56f2fd6f44bb87a28a903bf1306cd855c4fa19baa42d604e2f6aa571b4a6a603ab7769162e7fcb8");
}

void initPrimeP2PubKeyLists() {
    /* Get the time at the beginning of the method instead of fetching
     * it repeatedly. */
    const int now = time(NULL);

    /* Because this list is reloaded each time it's needed for the
     * interim of the Phase 2 key distribution we need to clear the
     * vector array before adding to it so we don't wind up adding
     * the same keys each time it's called. */
    if(p2pubKeyListsInitialized)
        pubKeyListP2.erase(pubKeyListP2.begin(), pubKeyListP2.end());

    p2pubKeyListsInitialized = true;

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7)) {
        pubKeyListP2.push_back("04388d05d6cdbf75a37540e9b94c1c0b4e9b41a109c1466a33b3cf3cbca9e244f7761686502a0a593831fac02753ea5c2c8fc14ed59b9060da2088d2cb674e041d");
        pubKeyListP2.push_back("04190509dad08314b99d137ff42faf23c4c58cc20a86aab3e77ca2bfd2aadb48a3af57ea7c7970521214ebc07dd307a60c3721443025619d7e4b81b52fe7c56c29");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 2)) {
        pubKeyListP2.push_back("0425219d18bd44310138e0a44899a2eed33ba69948fb4af704dcc0b14026628e40a06c15cf8d9579782dbb0cb5e83ef9400b7e9ed25dab3cbd1cc62b147024be53");
        pubKeyListP2.push_back("04a08d126504c0a4b49b1e3300bbfa3eb47da7a888728cc43a20ba06def3b27baf5d9aa653c0a79b3d49ad36f7cd4d66cf35491e3cb5bd6c5e635071dd22aa5647");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 3)) {
        pubKeyListP2.push_back("0441bbafe1ba1960f63f901e11eadc7d3aa0d2a1fe9dcce1e64bde728fdcefc02dda6ca6418a097a7b0bf3b934f5d5cb36949adcc63f8ce5466a03e513376b3d3f");
        pubKeyListP2.push_back("048459e154f476cf70eb08af52f6639d80c04524a3337be1d26f17c2f43618a9d4cd7bed8924cf72690c80cb43b25bcd91959b6effe1945b9c7391a566fa68a4fd");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 4)) {
        pubKeyListP2.push_back("04cfd34375765cb33f5418c3b8976012cc569a646455dd5281b16339c6c94cddee8136f7f65d0fff072f177b9cdc5ffcf7b3f377c5892b176137e89007347baa9d");
        pubKeyListP2.push_back("0475365af0c88811f597843187d5cfe0942c3ae6f3686c01ee10d016492799b9fd9f13c51c360e97fe0885978218351d891c7ce17897b9424a4097e8b590421583");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 5)) {
        pubKeyListP2.push_back("04fc023669c5b3475e4e83b8ad26bb00f47020572468a01050fa6992cbeadf27dc1822c8927f8fbf9e0575aa2fb1e73690520ed00e886d1884671179c2e428a2e9");
        pubKeyListP2.push_back("047cfe7bfc6289d77d819ef0020736e6c84c898be4be711bc6def7a1fcc166756e06e8a1441ca137e699dc06ad751a3a0617e67cdcaeff3b9fdd13292d7871621e");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 6)) {
        pubKeyListP2.push_back("04225437f2cc7c19783f3745162dbcb3984e3e56e1e3e3ef3928beeed6156cd3c130762f40d82e4c9a2d806bc81433ce051a737ba20b8e2263e52a26575cd6de19");
        pubKeyListP2.push_back("04dcf657b827f15ab55f23a10838829824efea6b497d4d9f9aba00e5ed705df27b4d5daf49f222c151ec57970471ff7c83e8288316349e6ebf1c4ae4fe392f5ce1");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 7)) {
        pubKeyListP2.push_back("04d7547cc1cd5d661deb48af5de42800ed74ce4dc7a42ef93e7332b9a9c5ea0000d9894eeade45fd94d5fca77f88fc2576c65b3d5049717c6c11c4f0311aedb36a");
        pubKeyListP2.push_back("04a14cf7474a03873650d0eac2262a83c64117f72ef8dd02029f4e9927050826ae2ff8af31a14a9f54e8cfdee45713a4bca9d1c94d99d6410f4da8ad2d6e7eebfc");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 8)) {
        pubKeyListP2.push_back("048f1a4774909f8e7f55503b07e88c94f8de85877a9e5f925f4d3b411e60aa87284b8c78ae2bdbbc30673b43a7d5d47e5f4f297af11c01716afaded30795d5f64f");
        pubKeyListP2.push_back("0403397802445e7c94e881bda2d8f7dc37d1f526d470b098edf8d1e42b6b64c6eb0675e8343d9aaeeea0e274dd113ce24345c3459160e6cc578046081c44ac65b6");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 9)) {
        pubKeyListP2.push_back("045dcf53bc0b748e0a45530d26629766f9cb606f486a427619ddd6a848707dbbdfb28bf18e8bab4face51586d8153c5cf486e5807d898a4f61f74c1338bc55b8c0");
        pubKeyListP2.push_back("040b8e367a05fa5f23b529621d328ecfd2b5c4c00d2c0b1e6264d2101ed97d3871a4615c81fb616114a625fd5ac76bb0abc0b9026f4f6e2579fd3cf45c8ec6f521");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 10)) {
        pubKeyListP2.push_back("04c5ca2074fc1f0aa52ba7757e80fe0f02a9764696b9fb2737d8b8a1ece4dc27b9f4defb4bbfed6677c710a96ba12daef880d1d424b9a078eca957eab082bf135c");
        pubKeyListP2.push_back("045c40b1ffb498a971f0214cb7525827ee5df13d58e522f4b7983cd3bb337dac57438639382a0a0068aa6fe15488cd3dd686ff2455f6ac7af22a6bd2b58bd41102");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 11)) {
        pubKeyListP2.push_back("045e814c7fcaa9aa1220dfb2031153d2dbdee279411dd26ab45d9631bf10668c2c14a139857fcebd579dd529bef4a243dbebbc19db3efe1a43b7369f078b359c31");
        pubKeyListP2.push_back("047545bc278722e77bcedd44a7b3abfb61d7b94bc719a61c030b8e0877bcc874c160d67e42100ef31db317d50b0fdef1b0e92b0d53e0bf064097433da7360a267d");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 12)) {
        pubKeyListP2.push_back("04d636b44b621798e033b1480ed6d503ebd1a114454c8ee8d4458af2df6622939849e92173e11fdf5681209aa937a4e7b685c3f256d770625c028444429efb4dba");
        pubKeyListP2.push_back("0418b5d12a90455616ab7fc48f904815e012db106ceceaf808457398464449680a42cc18a4a4aab504889a8769677c62e2b93062afbfbfeb93b38831777cc6561a");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 13)) {
        pubKeyListP2.push_back("040fa2ea0b42b17aab20cfd971e74c0ae3dc03cda6148fa1618c03d2d6b017e86906dd1bfab673d35f9e9b8c77929bba965a1745c3ba6eda54863ec96a57ca0322");
        pubKeyListP2.push_back("0454643cca0dbcd58a3054eccda22ee87cde8de3fc76dfa00504c800147602df07f1c2b51fa1acd7989774dbc42a40d8f4002a8dda63fd70b58f6b40afc421a5cd");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 14)) {
        pubKeyListP2.push_back("0401f4f467e4bf7becb5a6a7fc92104badd9bd60727b7ea23fa651ec38d72692eea2abbe56122dea584c76277f6a54f09186af41a236fc2cc40b8622cf80d9e2f8");
        pubKeyListP2.push_back("04bc6f36a02c5aece8bf67b09f8bffd4d61ea0214e289afcfebf44e531086304a9cc1601368e261db0da40a0199ad90334e81a802dcfd6a47647b948239db391f7");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 15)) {
        pubKeyListP2.push_back("04f639a33908c6d8d2980d90906caa04a595d8e8b5c183b925b90f6dbfbab33f3906da2bca7baa75d7c3903eb1c683d3afeacdeefa8ed034120050adbb51a3f22f");
        pubKeyListP2.push_back("04e9aa4df6296ffd5041efaa9ea66928b7bd061ea29266c32282fe8f321ad083fc137c14f9684bfddbec4f4b0488a739eebe9b9542645f4acef6a00ccac761b8b6");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 16)) {
        pubKeyListP2.push_back("043fc35929b59de26a727a15e41a46eff8bd2f5fadb4d0984d6479bad6f32fc770510f79ec054b07d03386a0b1be41fbb93e49b8684f8f8d753dcba425aac65f37");
        pubKeyListP2.push_back("04b510c56c90c756d664c78daac875ad68aad470c08071c1c8d00878793e40b1dab19897da829f66bd637f0bf0ac1cc298503305c9aa10b4b1bbf5c1f3c9ceeb00");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 17)) {
        pubKeyListP2.push_back("04658020acbe6383d4d0e3f2111afa5d956d4c2777cf0b5b016275a7349c4aea36a738f8535d40226cef494c9e90f398bd7613cc9e99c83059790f89ae8d661028");
        pubKeyListP2.push_back("04de4a176eb26027f1c07a95a6d456d3c006bd8f66e72217e0edd6bb1d90587503e279c1a73118ed0431eb124bb558ca856af32493e830d836951195592811716f");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 18)) {
        pubKeyListP2.push_back("0472b325244857201d36435a820cf152b267f361672e91f7f67d43c83b893ac6d453268ad9e1dc35100661435dbc1fe565c07b8179bf0c08a3d761fb053b9e60d8");
        pubKeyListP2.push_back("043f2cc09b94c1b419658b08517fe0e2403e36b33e64529f6b71378333be15de5072318abb7b31f320a220a8b50ffe881bda547d65b985d3b03742c4124483a307");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 19)) {
        pubKeyListP2.push_back("049e62eab973a734f116f1e94c17ceef520aabb6fb2bf9103c9dcc9873f67e34a597846da165852b85f77fbba1bb40c7c656c03cf0478d4a73722e15775771e83c");
        pubKeyListP2.push_back("04d106f80dda9e7b591f4bea3682bdea462c7855d22fbeaabff1d9ed93fb896c9eaf9d8b75f7bebfb7c061ddc60737ee59d663b80ff9535bebb840887bf2570aa6");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 20)) {
        pubKeyListP2.push_back("04bf2ba1fc4f1309c89858459a925a8b6c806729c849cc585178df4cbea59531a569dad5255cfae6000588c8db53718d1a4e64c0f98bf1b79f9028326a6836b946");
        pubKeyListP2.push_back("04293db53e95098615d00389cae5c6119933f5dd83d857a4001b68d7755d367aa6fb133b3f046f6163e87a947627b18cb82649b949a2dd745bd489d298a5d73815");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 21)) {
        pubKeyListP2.push_back("04f42d1829f568b97a5ef73cfae5e8d7d3e93587a10fd7931d62d0d781a9858b8a9abf94f7cc689f2dfa5b3f3f21cb70bf3bcac1881d9c18670c5a2af0ae82742a");
        pubKeyListP2.push_back("0496f840e96ae0725b45f48cbc1eec5ad5df786b126f605b0847cc2e768f198b41a0a80b1a1c328f577e53c2bab4fd7a53aba22d9279296cf74913d57225ac8853");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 22)) {
        pubKeyListP2.push_back("0403511e93de04e636133f102b4952e817ff1212c2032853464ae646d2da12824414230f30df923bcb3c6e09d3a38cd4c99b03f12422dccc8acf4d9a2b62367a6e");
        pubKeyListP2.push_back("042393fcf0641af94d4df5bca39a489440a7c39f7bfdc5216f637bfa5ee99be7e61de2451f84cb7f1df8591a2d39135bfcebed1a182f941d6288bb0cafd52b147b");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 23)) {
        pubKeyListP2.push_back("04a370a9c58434886b71fbee6de556e93c82e0768dca07be85b4536aeff690d63e8478a83606ef9513387b6ad68bfcd87ff62c0616b84d87edab923dfbbabac7f0");
        pubKeyListP2.push_back("0490abde95a40963e819e454f1099800e09670691aa389eb345901f230df7d508a458c348275f998e7e6521a8d0ceeede7364d1c758d75ece6c68ba2ea153bdc55");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 24)) {
        pubKeyListP2.push_back("04d90d8a5b0b4e3d56c6f1ef59bcd70ad676a3d86c295526c5088b663d35920412e402c8a1bdeb9b5b8c51aaf867fb71c0e8eeb9a2fb4c3af3ac4ef854b3b6401f");
        pubKeyListP2.push_back("04fd4f559346393b0c5530869dcb1a05db35ae26998d116ecbcf106d5b6b022960344134087bbcadc1bb6d004487e3a1b77a5ea84e0e751f53444e540c1a38ec68");
    }

    if (now >= END_PRIME_PHASE_ONE + (60 * 60 * 24 * 7 * 25)) {
        pubKeyListP2.push_back("043c31391627cfac357cd01e30a2f74b8eb97871d28d040cdc2dc9577cc21965f973c47400eb198ab22ee1d5a3c733eb541502af8f82e7fe752e833036459d803f");
        pubKeyListP2.push_back("04df482827573b607fe7279687bb287ccb48f87d24752c69d68e2c130d2d2c8993056e05fb86e61d54747b043c3f6f22b31b891664a90e4c071c794c93455b1cbe");
    }
}
