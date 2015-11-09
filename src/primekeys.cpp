#include "primenodes.h"

// This is in util.h but we really don't need all of util.h for this file.
typedef long long  int64;

void CPrimeNodeDB::WritePrimeNodeDB() {
    LOCK(cs);

    WritePrimeNodeDBVersion(4);

    if (fTestNet) {
        WritePrimeNodeKey(
            "04d445518d115243639d0dfd057a99da588e8334039ce674f177943d4c660957c810f924a5371a352b1e827121846500a588a4dc47dc6d5d9e5317dfa48c562aa7",
            END_PRIME_PHASE_ONE + 1209600, // 2 weeks // valid starting
            -1 // no shutdown time yet specified.
        );
        WritePrimeNodeKey(
            "0443e5bf72234d77a591ca2132c5995cccdba377a7022eb014d25e27ebe6ffaf85cd3a214588612186ee1771cfb905d1ec2137193bc01563dbc36d1e28f013e00d",
            END_PRIME_PHASE_ONE + 1296000, // 2 weeks, 2 days
            -1
        );
        return;
    }

    WritePrimeNodeKey(
        "04388d05d6cdbf75a37540e9b94c1c0b4e9b41a109c1466a33b3cf3cbca9e244f7761686502a0a593831fac02753ea5c2c8fc14ed59b9060da2088d2cb674e041d",
        END_PRIME_PHASE_ONE + 604800, // 1 week
        -1
    );

    WritePrimeNodeKey(
        "04190509dad08314b99d137ff42faf23c4c58cc20a86aab3e77ca2bfd2aadb48a3af57ea7c7970521214ebc07dd307a60c3721443025619d7e4b81b52fe7c56c29",
        END_PRIME_PHASE_ONE + 604800, // 1 week
        -1
    );

    WritePrimeNodeKey(
        "0425219d18bd44310138e0a44899a2eed33ba69948fb4af704dcc0b14026628e40a06c15cf8d9579782dbb0cb5e83ef9400b7e9ed25dab3cbd1cc62b147024be53",
        END_PRIME_PHASE_ONE + 1209600, // 2 weeks
        -1
    );

    WritePrimeNodeKey(
        "04a08d126504c0a4b49b1e3300bbfa3eb47da7a888728cc43a20ba06def3b27baf5d9aa653c0a79b3d49ad36f7cd4d66cf35491e3cb5bd6c5e635071dd22aa5647",
        END_PRIME_PHASE_ONE + 1209600, // 2 weeks
        -1
    );

    WritePrimeNodeKey(
        "0441bbafe1ba1960f63f901e11eadc7d3aa0d2a1fe9dcce1e64bde728fdcefc02dda6ca6418a097a7b0bf3b934f5d5cb36949adcc63f8ce5466a03e513376b3d3f",
        END_PRIME_PHASE_ONE + 1814400, // 3 weeks
        -1
    );

    WritePrimeNodeKey(
        "048459e154f476cf70eb08af52f6639d80c04524a3337be1d26f17c2f43618a9d4cd7bed8924cf72690c80cb43b25bcd91959b6effe1945b9c7391a566fa68a4fd",
        END_PRIME_PHASE_ONE + 1814400, // 3 weeks
        -1
    );

    WritePrimeNodeKey(
        "04cfd34375765cb33f5418c3b8976012cc569a646455dd5281b16339c6c94cddee8136f7f65d0fff072f177b9cdc5ffcf7b3f377c5892b176137e89007347baa9d",
        END_PRIME_PHASE_ONE + 2419200, // 4 weeks
        -1
    );

    WritePrimeNodeKey(
        "0475365af0c88811f597843187d5cfe0942c3ae6f3686c01ee10d016492799b9fd9f13c51c360e97fe0885978218351d891c7ce17897b9424a4097e8b590421583",
        END_PRIME_PHASE_ONE + 2419200, // 4 weeks
        -1
    );

    WritePrimeNodeKey(
        "04fc023669c5b3475e4e83b8ad26bb00f47020572468a01050fa6992cbeadf27dc1822c8927f8fbf9e0575aa2fb1e73690520ed00e886d1884671179c2e428a2e9",
        END_PRIME_PHASE_ONE + 3024000, // 5 weeks
        -1
    );

    WritePrimeNodeKey(
        "047cfe7bfc6289d77d819ef0020736e6c84c898be4be711bc6def7a1fcc166756e06e8a1441ca137e699dc06ad751a3a0617e67cdcaeff3b9fdd13292d7871621e",
        END_PRIME_PHASE_ONE + 3024000, // 5 weeks
        -1
    );

    WritePrimeNodeKey(
        "04225437f2cc7c19783f3745162dbcb3984e3e56e1e3e3ef3928beeed6156cd3c130762f40d82e4c9a2d806bc81433ce051a737ba20b8e2263e52a26575cd6de19",
        END_PRIME_PHASE_ONE + 3628800, // 6 weeks
        -1
    );

    WritePrimeNodeKey(
        "04dcf657b827f15ab55f23a10838829824efea6b497d4d9f9aba00e5ed705df27b4d5daf49f222c151ec57970471ff7c83e8288316349e6ebf1c4ae4fe392f5ce1",
        END_PRIME_PHASE_ONE + 3628800, // 6 weeks
        -1
    );

    WritePrimeNodeKey(
        "04d7547cc1cd5d661deb48af5de42800ed74ce4dc7a42ef93e7332b9a9c5ea0000d9894eeade45fd94d5fca77f88fc2576c65b3d5049717c6c11c4f0311aedb36a",
        END_PRIME_PHASE_ONE + 4233600, // 7 weeks
        -1
    );

    WritePrimeNodeKey(
        "04a14cf7474a03873650d0eac2262a83c64117f72ef8dd02029f4e9927050826ae2ff8af31a14a9f54e8cfdee45713a4bca9d1c94d99d6410f4da8ad2d6e7eebfc",
        END_PRIME_PHASE_ONE + 4233600, // 7 weeks
        -1
    );

    WritePrimeNodeKey(
        "048f1a4774909f8e7f55503b07e88c94f8de85877a9e5f925f4d3b411e60aa87284b8c78ae2bdbbc30673b43a7d5d47e5f4f297af11c01716afaded30795d5f64f",
        END_PRIME_PHASE_ONE + 4838400, // 8 weeks
        -1
    );

    WritePrimeNodeKey(
        "0403397802445e7c94e881bda2d8f7dc37d1f526d470b098edf8d1e42b6b64c6eb0675e8343d9aaeeea0e274dd113ce24345c3459160e6cc578046081c44ac65b6",
        END_PRIME_PHASE_ONE + 4838400, // 8 weeks
        -1
    );

    WritePrimeNodeKey(
        "045dcf53bc0b748e0a45530d26629766f9cb606f486a427619ddd6a848707dbbdfb28bf18e8bab4face51586d8153c5cf486e5807d898a4f61f74c1338bc55b8c0",
        END_PRIME_PHASE_ONE + 5443200, // 9 weeks
        -1
    );

    WritePrimeNodeKey(
        "040b8e367a05fa5f23b529621d328ecfd2b5c4c00d2c0b1e6264d2101ed97d3871a4615c81fb616114a625fd5ac76bb0abc0b9026f4f6e2579fd3cf45c8ec6f521",
        END_PRIME_PHASE_ONE + 5443200, // 9 weeks
        -1
    );

    WritePrimeNodeKey(
        "04c5ca2074fc1f0aa52ba7757e80fe0f02a9764696b9fb2737d8b8a1ece4dc27b9f4defb4bbfed6677c710a96ba12daef880d1d424b9a078eca957eab082bf135c",
        END_PRIME_PHASE_ONE + 6048000, // 10 weeks
        -1
    );

    WritePrimeNodeKey(
        "045c40b1ffb498a971f0214cb7525827ee5df13d58e522f4b7983cd3bb337dac57438639382a0a0068aa6fe15488cd3dd686ff2455f6ac7af22a6bd2b58bd41102",
        END_PRIME_PHASE_ONE + 6048000, // 10 weeks
        -1
    );

    WritePrimeNodeKey(
        "045e814c7fcaa9aa1220dfb2031153d2dbdee279411dd26ab45d9631bf10668c2c14a139857fcebd579dd529bef4a243dbebbc19db3efe1a43b7369f078b359c31",
        END_PRIME_PHASE_ONE + 6652800, // 11 weeks
        -1
    );

    WritePrimeNodeKey(
        "047545bc278722e77bcedd44a7b3abfb61d7b94bc719a61c030b8e0877bcc874c160d67e42100ef31db317d50b0fdef1b0e92b0d53e0bf064097433da7360a267d",
        END_PRIME_PHASE_ONE + 6652800, // 11 weeks
        -1
    );

    WritePrimeNodeKey(
        "04d636b44b621798e033b1480ed6d503ebd1a114454c8ee8d4458af2df6622939849e92173e11fdf5681209aa937a4e7b685c3f256d770625c028444429efb4dba",
        END_PRIME_PHASE_ONE + 7257600, // 12 weeks
        -1
    );

    WritePrimeNodeKey(
        "0418b5d12a90455616ab7fc48f904815e012db106ceceaf808457398464449680a42cc18a4a4aab504889a8769677c62e2b93062afbfbfeb93b38831777cc6561a",
        END_PRIME_PHASE_ONE + 7257600, // 12 weeks
        -1
    );

    WritePrimeNodeKey(
        "040fa2ea0b42b17aab20cfd971e74c0ae3dc03cda6148fa1618c03d2d6b017e86906dd1bfab673d35f9e9b8c77929bba965a1745c3ba6eda54863ec96a57ca0322",
        END_PRIME_PHASE_ONE + 7862400, // 13 weeks
        -1
    );

    WritePrimeNodeKey(
        "0454643cca0dbcd58a3054eccda22ee87cde8de3fc76dfa00504c800147602df07f1c2b51fa1acd7989774dbc42a40d8f4002a8dda63fd70b58f6b40afc421a5cd",
        END_PRIME_PHASE_ONE + 7862400, // 13 weeks
        -1
    );

    WritePrimeNodeKey(
        "0401f4f467e4bf7becb5a6a7fc92104badd9bd60727b7ea23fa651ec38d72692eea2abbe56122dea584c76277f6a54f09186af41a236fc2cc40b8622cf80d9e2f8",
        END_PRIME_PHASE_ONE + 8467200, // 14 weeks
        -1
    );

    WritePrimeNodeKey(
        "04bc6f36a02c5aece8bf67b09f8bffd4d61ea0214e289afcfebf44e531086304a9cc1601368e261db0da40a0199ad90334e81a802dcfd6a47647b948239db391f7",
        END_PRIME_PHASE_ONE + 8467200, // 14 weeks
        -1
    );

    WritePrimeNodeKey(
        "04f639a33908c6d8d2980d90906caa04a595d8e8b5c183b925b90f6dbfbab33f3906da2bca7baa75d7c3903eb1c683d3afeacdeefa8ed034120050adbb51a3f22f",
        END_PRIME_PHASE_ONE + 9072000, // 15 weeks
        1445380000 // Invalidated shortly after only stake for this key
    );

    WritePrimeNodeKey(
        "04e9aa4df6296ffd5041efaa9ea66928b7bd061ea29266c32282fe8f321ad083fc137c14f9684bfddbec4f4b0488a739eebe9b9542645f4acef6a00ccac761b8b6",
        END_PRIME_PHASE_ONE + 9072000, // 15 weeks
        -1
    );

    WritePrimeNodeKey(
        "04b510c56c90c756d664c78daac875ad68aad470c08071c1c8d00878793e40b1dab19897da829f66bd637f0bf0ac1cc298503305c9aa10b4b1bbf5c1f3c9ceeb00",
        END_PRIME_PHASE_ONE + 9676800, // 16 weeks
        -1
    );

    WritePrimeNodeKey(
        "04658020acbe6383d4d0e3f2111afa5d956d4c2777cf0b5b016275a7349c4aea36a738f8535d40226cef494c9e90f398bd7613cc9e99c83059790f89ae8d661028",
        END_PRIME_PHASE_ONE + 10281600, // 17 weeks
        -1
    );

    WritePrimeNodeKey(
        "04de4a176eb26027f1c07a95a6d456d3c006bd8f66e72217e0edd6bb1d90587503e279c1a73118ed0431eb124bb558ca856af32493e830d836951195592811716f",
        END_PRIME_PHASE_ONE + 10281600, // 17 weeks
        -1
    );

    WritePrimeNodeKey(
        "0472b325244857201d36435a820cf152b267f361672e91f7f67d43c83b893ac6d453268ad9e1dc35100661435dbc1fe565c07b8179bf0c08a3d761fb053b9e60d8",
        END_PRIME_PHASE_ONE + 10886400, // 18 weeks
        -1
    );

    WritePrimeNodeKey(
        "043f2cc09b94c1b419658b08517fe0e2403e36b33e64529f6b71378333be15de5072318abb7b31f320a220a8b50ffe881bda547d65b985d3b03742c4124483a307",
        END_PRIME_PHASE_ONE + 10886400, // 18 weeks
        -1
    );

    WritePrimeNodeKey(
        "049e62eab973a734f116f1e94c17ceef520aabb6fb2bf9103c9dcc9873f67e34a597846da165852b85f77fbba1bb40c7c656c03cf0478d4a73722e15775771e83c",
        END_PRIME_PHASE_ONE + 11491200, // 19 weeks
        -1
    );

    WritePrimeNodeKey(
        "04d106f80dda9e7b591f4bea3682bdea462c7855d22fbeaabff1d9ed93fb896c9eaf9d8b75f7bebfb7c061ddc60737ee59d663b80ff9535bebb840887bf2570aa6",
        END_PRIME_PHASE_ONE + 11491200, // 19 weeks
        -1
    );

    WritePrimeNodeKey(
        "04bf2ba1fc4f1309c89858459a925a8b6c806729c849cc585178df4cbea59531a569dad5255cfae6000588c8db53718d1a4e64c0f98bf1b79f9028326a6836b946",
        END_PRIME_PHASE_ONE + 12096000, // 20 weeks
        -1
    );

    WritePrimeNodeKey(
        "04293db53e95098615d00389cae5c6119933f5dd83d857a4001b68d7755d367aa6fb133b3f046f6163e87a947627b18cb82649b949a2dd745bd489d298a5d73815",
        END_PRIME_PHASE_ONE + 12096000, // 20 weeks
        -1
    );

    WritePrimeNodeKey(
        "04f42d1829f568b97a5ef73cfae5e8d7d3e93587a10fd7931d62d0d781a9858b8a9abf94f7cc689f2dfa5b3f3f21cb70bf3bcac1881d9c18670c5a2af0ae82742a",
        END_PRIME_PHASE_ONE + 12700800, // 21 weeks
        -1
    );

    WritePrimeNodeKey(
        "0496f840e96ae0725b45f48cbc1eec5ad5df786b126f605b0847cc2e768f198b41a0a80b1a1c328f577e53c2bab4fd7a53aba22d9279296cf74913d57225ac8853",
        END_PRIME_PHASE_ONE + 12700800, // 21 weeks
        -1
    );

    WritePrimeNodeKey(
        "0403511e93de04e636133f102b4952e817ff1212c2032853464ae646d2da12824414230f30df923bcb3c6e09d3a38cd4c99b03f12422dccc8acf4d9a2b62367a6e",
        END_PRIME_PHASE_ONE + 13305600, // 22 weeks
        -1
    );

    WritePrimeNodeKey(
        "042393fcf0641af94d4df5bca39a489440a7c39f7bfdc5216f637bfa5ee99be7e61de2451f84cb7f1df8591a2d39135bfcebed1a182f941d6288bb0cafd52b147b",
        END_PRIME_PHASE_ONE + 13305600, // 22 weeks
        -1
    );

    WritePrimeNodeKey(
        "04a370a9c58434886b71fbee6de556e93c82e0768dca07be85b4536aeff690d63e8478a83606ef9513387b6ad68bfcd87ff62c0616b84d87edab923dfbbabac7f0",
        END_PRIME_PHASE_ONE + 13910400, // 23 weeks
        -1
    );

    WritePrimeNodeKey(
        "0490abde95a40963e819e454f1099800e09670691aa389eb345901f230df7d508a458c348275f998e7e6521a8d0ceeede7364d1c758d75ece6c68ba2ea153bdc55",
        END_PRIME_PHASE_ONE + 13910400, // 23 weeks
        -1
    );

    WritePrimeNodeKey(
        "04d90d8a5b0b4e3d56c6f1ef59bcd70ad676a3d86c295526c5088b663d35920412e402c8a1bdeb9b5b8c51aaf867fb71c0e8eeb9a2fb4c3af3ac4ef854b3b6401f",
        END_PRIME_PHASE_ONE + 14515200, // 24 weeks
        -1
    );

    WritePrimeNodeKey(
        "04fd4f559346393b0c5530869dcb1a05db35ae26998d116ecbcf106d5b6b022960344134087bbcadc1bb6d004487e3a1b77a5ea84e0e751f53444e540c1a38ec68",
        END_PRIME_PHASE_ONE + 14515200, // 24 weeks
        -1
    );

    WritePrimeNodeKey(
        "043c31391627cfac357cd01e30a2f74b8eb97871d28d040cdc2dc9577cc21965f973c47400eb198ab22ee1d5a3c733eb541502af8f82e7fe752e833036459d803f",
        END_PRIME_PHASE_ONE + 15120000, // 25 weeks
        -1
    );

    WritePrimeNodeKey(
        "04df482827573b607fe7279687bb287ccb48f87d24752c69d68e2c130d2d2c8993056e05fb86e61d54747b043c3f6f22b31b891664a90e4c071c794c93455b1cbe",
        END_PRIME_PHASE_ONE + 15120000, // 25 weeks
        -1
    );

    // New keys to replace the invalidated ones from week 15 and 16...
    WritePrimeNodeKey(
        "049f525f2ab7d8491873b7c63f41a60e2d2762966815d7a7995976f695df0ff3a8d70812f5191c381eb8d6bfc171937abc729f2d940673660ecfe6b8e2c82d4d08",
        END_PRIME_PHASE_ONE + 15120000, // 25 weeks
        -1
    );

    WritePrimeNodeKey(
        "049bee18cacc1d51282633a0d269f53bfc4366342c3043e229f3c5534b9184bce83440e4d3164ceb158515c6af8867091e0b1045f53c5b3756fc4413265266e759",
        END_PRIME_PHASE_ONE + 15120000, // 25 weeks
        -1
    );
}
