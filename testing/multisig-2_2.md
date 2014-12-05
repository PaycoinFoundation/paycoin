Test 2/2 multisig address
==========================

Alice wants to send coins to Bob using a multisig address generated with 2 keys and requiring signatures from these 2 keys to spend the coins.


Generate the multisig address
-----------------------------

The multisig address is generated with the complete public keys of the participants.


**Alice:**

validateaddress "mw2pj33HMhRfRkKtceHcyKpPiGYkPdD4SM"

    {
      "isvalid" : true,
      "address" : "mw2pj33HMhRfRkKtceHcyKpPiGYkPdD4SM",
      "ismine" : true,
      "isscript" : false,
      "pubkey" : "02c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b",
      "iscompressed" : true,
      "account" : "Alice"
    }


**Bob:**

validateaddress "mkLNecFNeiJgKjw6492nqDiQfKQs1JnLmE"

    {
      "isvalid" : true,
      "address" : "mkLNecFNeiJgKjw6492nqDiQfKQs1JnLmE",
      "ismine" : true,
      "pubkey" : "025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e",
      "iscompressed" : true,
      "account" : "Bob"
    }

createmultisig 2 '["02c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b", "025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e"]'

    {
      "address" : "2N8inbkwEUk17mcxtZwXvJZ41L9tLy36wcb",
      "redeemScript" : "522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e52ae"
    }


Send coins to the multisig address
----------------------------------

Alice sends 360 PPC to the multisig address.


**Alice:**

sendtoaddress "2N8inbkwEUk17mcxtZwXvJZ41L9tLy36wcb" 360

    ae43abc09837882ec50f2f899aab46bd880ccd88c3796255b275880c0a4535e0


Create a transaction to spend the coins
---------------------------------------

Bob creates a transaction to spend the coins that Alice sent to the multisig address.
The transaction will have 360 PPC (Alice's coins) as input and 359.99 PPC as output (because of the mandatory 0.01 PPC transaction fee; the transaction won't be accepted by the network without it).


**Bob:**

getrawtransaction "ae43abc09837882ec50f2f899aab46bd880ccd88c3796255b275880c0a4535e0" 1

    {
      "hex" : "01000000034455530167099ebc43ec43f8dedc338697c68af6fae60ff195adda352124cd97034a6b7a000000006b483045022040fe9fff5c86f2f76b7ab09b1f11b8aa3549603b4fc5cd81c503f1dabf397c97022100fb373a243bdedfe59887bd48bf664e94e5491ac564c15fcfb6a4e47494d2c9950121027fd3ce4054c80cdca9504b16c6e895a7f830e387c3eacc3001a977771e0c04b1ffffffff024075aa04000000001976a914a3a39a25ee165907da7fba509fe4bc7d3abfc54188ac002a75150000000017a914a9c0572da551ff1962f624e9845200641e7232978700000000",
      "txid" : "ae43abc09837882ec50f2f899aab46bd880ccd88c3796255b275880c0a4535e0",
      "version" : 1,
      "locktime" : 0,
      "vin" : [
        {
          "txid" : "7a6b4a0397cd242135daad95f10fe6faf68ac6978633dcdef843ec43bc9e0967",
          "vout" : 0,
          "scriptSig" : {
            "asm" : "3045022040fe9fff5c86f2f76b7ab09b1f11b8aa3549603b4fc5cd81c503f1dabf397c97022100fb373a243bdedfe59887bd48bf664e94e5491ac564c15fcfb6a4e47494d2c99501 027fd3ce4054c80cdca9504b16c6e895a7f830e387c3eacc3001a977771e0c04b1",
            "hex" : "483045022040fe9fff5c86f2f76b7ab09b1f11b8aa3549603b4fc5cd81c503f1dabf397c97022100fb373a243bdedfe59887bd48bf664e94e5491ac564c15fcfb6a4e47494d2c9950121027fd3ce4054c80cdca9504b16c6e895a7f830e387c3eacc3001a977771e0c04b1"
          },
          "sequence" : 4294967295
        }
      ],
      "vout" : [
        {
          "value" : 78.28000000,
          "n" : 0,
          "scriptPubKey" : {
            "asm" : "OP_DUP OP_HASH160 a3a39a25ee165907da7fba509fe4bc7d3abfc541 OP_EQUALVERIFY OP_CHECKSIG",
            "hex" : "76a914a3a39a25ee165907da7fba509fe4bc7d3abfc54188ac",
            "reqSigs" : 1,
            "type" : "pubkeyhash",
            "addresses" : [
              "mvSCRbfPmop2eh8eFRHxffLapKYXvSFaCR"
            ]
          }
        },
        {
          "value" : 360.00000000,
          "n" : 1,
          "scriptPubKey" : {
            "asm" : "OP_HASH160 a9c0572da551ff1962f624e9845200641e723297 OP_EQUAL",
            "hex" : "a914a9c0572da551ff1962f624e9845200641e72329787",
            "reqSigs" : 1,
            "type" : "scripthash",
            "addresses" : [
              "2N8inbkwEUk17mcxtZwXvJZ41L9tLy36wcb"
            ]
          }
        }
      ],
      "blockhash" : "000000049aa3b4de0b04b02222f24772f0297cc45dfcd84dd47f70276ea0e582",
      "confirmations" : 15,
      "time" : 1398097347,
      "blocktime" : 1398097347
    }

createrawtransaction '[{"txid" : "ae43abc09837882ec50f2f899aab46bd880ccd88c3796255b275880c0a4535e0", "vout" : 1, "scriptPubKey" : "a914a9c0572da551ff1962f624e9845200641e72329787", "redeemScript" : "522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e52ae"}]' '{"mkLNecFNeiJgKjw6492nqDiQfKQs1JnLmE" : 359.99}'

    010000009f87555301e035450a0c8875b2556279c388cd0c88bd46ab9a892f0fc52e883798c0ab43ae0100000000ffffffff01f0027515000000001976a91434d86223cb5480e9086f1c934e8aa7f1798954ab88ac00000000


First signature of the transaction
----------------------------------

Bob signs the new transaction with the private key associated to the public key he used to create the multisig address and sends the result to Alice.


**Bob:**

dumpprivkey "mkLNecFNeiJgKjw6492nqDiQfKQs1JnLmE"

    cTxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo5

signrawtransaction "010000009f87555301e035450a0c8875b2556279c388cd0c88bd46ab9a892f0fc52e883798c0ab43ae0100000000ffffffff01f0027515000000001976a91434d86223cb5480e9086f1c934e8aa7f1798954ab88ac00000000" '[{"txid" : "ae43abc09837882ec50f2f899aab46bd880ccd88c3796255b275880c0a4535e0", "vout" : 1, "scriptPubKey" : "a914a9c0572da551ff1962f624e9845200641e72329787", "redeemScript" : "522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e52ae"}]' '["cTxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo5"]'

    {
      "hex" : "010000009f87555301e035450a0c8875b2556279c388cd0c88bd46ab9a892f0fc52e883798c0ab43ae010000009200483045022100bd4b352f7e290b3aa5f09da55ed2390bdb68dbfa6500711fe27cfb2a6afcf97602200ab4478c3104ca7ec7893e248bd83c8be382fc443836497989792c8775cfb5cd0147522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e52aeffffffff01f0027515000000001976a91434d86223cb5480e9086f1c934e8aa7f1798954ab88ac00000000",
      "complete" : false
    }


Second signature of the transaction
-----------------------------------

Alice signs the transaction with the private key associated to the public key she used to create the multisig address.


**Alice:**

dumpprivkey "mw2pj33HMhRfRkKtceHcyKpPiGYkPdD4SM"

    cPxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxFo

signrawtransaction "010000009f87555301e035450a0c8875b2556279c388cd0c88bd46ab9a892f0fc52e883798c0ab43ae010000009200483045022100bd4b352f7e290b3aa5f09da55ed2390bdb68dbfa6500711fe27cfb2a6afcf97602200ab4478c3104ca7ec7893e248bd83c8be382fc443836497989792c8775cfb5cd0147522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e52aeffffffff01f0027515000000001976a91434d86223cb5480e9086f1c934e8aa7f1798954ab88ac00000000" '[{"txid" : "ae43abc09837882ec50f2f899aab46bd880ccd88c3796255b275880c0a4535e0", "vout" : 1, "scriptPubKey" : "a914a9c0572da551ff1962f624e9845200641e72329787", "redeemScript" : "522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e52ae"}]' '["cPxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxFo"]'

    {
      "hex" : "010000009f87555301e035450a0c8875b2556279c388cd0c88bd46ab9a892f0fc52e883798c0ab43ae01000000db004830450220377f445291ebbc7e462f2c7dc7c56e063174e46fad472e95483c4a54e708127c022100cdd2d108d0a7a696fb5055c7ec7bc6ea78f9f3394a8d981b521702d19a19c90d01483045022100bd4b352f7e290b3aa5f09da55ed2390bdb68dbfa6500711fe27cfb2a6afcf97602200ab4478c3104ca7ec7893e248bd83c8be382fc443836497989792c8775cfb5cd0147522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e52aeffffffff01f0027515000000001976a91434d86223cb5480e9086f1c934e8aa7f1798954ab88ac00000000",
      "complete" : true
    }


Send the signed transaction to the network
------------------------------------------

Both participants have signed the transaction (indicating that they agree with it).
Either Alice sends the fully signed transaction to the network, or she send the result of her signature of the transaction to Bob and he send it to the network.

sendrawtransaction "010000009f87555301e035450a0c8875b2556279c388cd0c88bd46ab9a892f0fc52e883798c0ab43ae01000000db004830450220377f445291ebbc7e462f2c7dc7c56e063174e46fad472e95483c4a54e708127c022100cdd2d108d0a7a696fb5055c7ec7bc6ea78f9f3394a8d981b521702d19a19c90d01483045022100bd4b352f7e290b3aa5f09da55ed2390bdb68dbfa6500711fe27cfb2a6afcf97602200ab4478c3104ca7ec7893e248bd83c8be382fc443836497989792c8775cfb5cd0147522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e52aeffffffff01f0027515000000001976a91434d86223cb5480e9086f1c934e8aa7f1798954ab88ac00000000"

    6e24726d133aeacbb8b3c1c6b6e60ae50cb306ed98737dd85a0b8dbfa11dcfd5
