Test 2/3 multisig address
==========================

Alice must send coins to Bob using a multisig address generated with 3 keys (Alice, Bob, Trent) and requiring signatures from 2 keys out of 3 to spend the coins.
Trent is a trusted third party.


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


**Trent:**

validateaddress "mm8Fwn92RU8zvJmH7TCpaYL3v4PTyjN4xd"

    {
      "isvalid" : true,
      "address" : "mm8Fwn92RU8zvJmH7TCpaYL3v4PTyjN4xd",
      "ismine" : true,
      "isscript" : false,
      "pubkey" : "033ba42c942ff7e7fcf42ff604d6ef6c51826f9eea3a04308379c2ade98fb9e703",
      "iscompressed" : true,
      "account" : "Trent"
    }


createmultisig 2 '["02c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b", "025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e", "033ba42c942ff7e7fcf42ff604d6ef6c51826f9eea3a04308379c2ade98fb9e703"]'

    {
      "address" : "2N582fRZZZm9hL4RH4sguG9SDDLZhu7eeng",
      "redeemScript" : "522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e21033ba42c942ff7e7fcf42ff604d6ef6c51826f9eea3a04308379c2ade98fb9e70353ae"
    }


Send coins to the multisig address
----------------------------------

Alice sends 360 PPC to the multisig address.


**Alice:**

sendtoaddress "2N582fRZZZm9hL4RH4sguG9SDDLZhu7eeng" 360

    0ef16552d0dadaa150da34cfbc5380e82d59b5f328f967fb72104c43a1b99f74


Create a transaction to spend the coins
---------------------------------------

Bob creates a transaction to spend the coins that Alice sent to the multisig address.
The transaction will have 360 PPC (Alice's coins) as input and 359.99 PPC as output (because of the mandatory 0.01 PPC transaction fee; the transaction won't be accepted by the network without it).


**Bob:**

getrawtransaction "0ef16552d0dadaa150da34cfbc5380e82d59b5f328f967fb72104c43a1b99f74" 1

    {
      "hex" : "01000000197f5a530105a302fe97c3ab33581486fdb39296e8728d2dac7b06324a62ab83515c30d9d8000000006b4830450221008054ee73403f401b2c10acdaed1e51e5345d35fb24574719d8a01203934c6e3202204d97e79ccdae05713b18d85e36896e3bd7a1a0636bd207a493779ca6a7c148c4012102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0bffffffff02f0591b2c000000001976a9149f99f0ec7288694065243d32bea766bf9a8d602188ac002a75150000000017a914824524d69e3c8f2ea66e39af89727bc0e8d3de4b8700000000",
      "txid" : "0ef16552d0dadaa150da34cfbc5380e82d59b5f328f967fb72104c43a1b99f74",
      "version" : 1,
      "locktime" : 0,
      "vin" : [
        {
          "txid" : "d8d9305c5183ab624a32067bac2d8d72e89692b3fd86145833abc397fe02a305",
          "vout" : 0,
          "scriptSig" : {
            "asm" : "30450221008054ee73403f401b2c10acdaed1e51e5345d35fb24574719d8a01203934c6e3202204d97e79ccdae05713b18d85e36896e3bd7a1a0636bd207a493779ca6a7c148c401 02c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b",
            "hex" : "4830450221008054ee73403f401b2c10acdaed1e51e5345d35fb24574719d8a01203934c6e3202204d97e79ccdae05713b18d85e36896e3bd7a1a0636bd207a493779ca6a7c148c4012102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b"
          },
          "sequence" : 4294967295
        }
      ],
      "vout" : [
        {
          "value" : 739.99000000,
          "n" : 0,
          "scriptPubKey" : {
            "asm" : "OP_DUP OP_HASH160 9f99f0ec7288694065243d32bea766bf9a8d6021 OP_EQUALVERIFY OP_CHECKSIG",
            "hex" : "76a9149f99f0ec7288694065243d32bea766bf9a8d602188ac",
            "reqSigs" : 1,
            "type" : "pubkeyhash",
            "addresses" : [
              "mv4r9a4FXuDgSA5GaFtLGC9W5Db3XJUrLD"
            ]
          }
        },
        {
          "value" : 360.00000000,
          "n" : 1,
          "scriptPubKey" : {
            "asm" : "OP_HASH160 824524d69e3c8f2ea66e39af89727bc0e8d3de4b OP_EQUAL",
            "hex" : "a914824524d69e3c8f2ea66e39af89727bc0e8d3de4b87",
            "reqSigs" : 1,
            "type" : "scripthash",
            "addresses" : [
              "2N582fRZZZm9hL4RH4sguG9SDDLZhu7eeng"
            ]
          }
        }
      ],
      "blockhash" : "05a7088c02f589ca91beb52ea9667955f7ee10a2433e56f2e11a058c2273bb70",
      "confirmations" : 2,
      "time" : 1398439709,
      "blocktime" : 1398439709
    }

createrawtransaction '[{"txid" : "0ef16552d0dadaa150da34cfbc5380e82d59b5f328f967fb72104c43a1b99f74", "vout" : 1, "scriptPubKey" : "a914824524d69e3c8f2ea66e39af89727bc0e8d3de4b87", "redeemScript" : "522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e21033ba42c942ff7e7fcf42ff604d6ef6c51826f9eea3a04308379c2ade98fb9e70353ae"}]' '{"mub5ke5cWP4nZW2VDgtAkFGA7UzSVhwese" : 359.99}'

    0100000062815a5301749fb9a1434c1072fb67f928f3b5592de88053bccf34da50a1dadad05265f10e0100000000ffffffff01f0027515000000001976a9149a59a69866c7668acdd2b36491cfc18229d2348988ac00000000


First signature of the transaction
----------------------------------

Bob signs the new transaction with the private key associated to the public key he used to create the multisig address and sends the result to Alice.


**Bob:**

dumpprivkey "mkLNecFNeiJgKjw6492nqDiQfKQs1JnLmE"

    cTxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo5

signrawtransaction "0100000062815a5301749fb9a1434c1072fb67f928f3b5592de88053bccf34da50a1dadad05265f10e0100000000ffffffff01f0027515000000001976a9149a59a69866c7668acdd2b36491cfc18229d2348988ac00000000" '[{"txid" : "0ef16552d0dadaa150da34cfbc5380e82d59b5f328f967fb72104c43a1b99f74", "vout" : 1, "scriptPubKey" : "a914824524d69e3c8f2ea66e39af89727bc0e8d3de4b87", "redeemScript" : "522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e21033ba42c942ff7e7fcf42ff604d6ef6c51826f9eea3a04308379c2ade98fb9e70353ae"}]' '["cTxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo5"]'

    {
      "hex" : "0100000062815a5301749fb9a1434c1072fb67f928f3b5592de88053bccf34da50a1dadad05265f10e01000000b40047304402201dfd957507d6b48b777a6f5c31d85fb8d00513b79c55dbd902c7f6dee90bc4cc0220773f05b481a9dbbc3153cb832acd994caef0d569de49d3b4a125b5f1e637836c014c69522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e21033ba42c942ff7e7fcf42ff604d6ef6c51826f9eea3a04308379c2ade98fb9e70353aeffffffff01f0027515000000001976a9149a59a69866c7668acdd2b36491cfc18229d2348988ac00000000",
      "complete" : false
    }


Second signature of the transaction
-----------------------------------

Let's imagine that Alice refuses to sign the transaction.
Bob sends the transaction with one signature to Trent and asks him to validate it. Let's imagine that Trent decides that the transaction is legitimate.
Trent signs the transaction with the private key associated to the public key he used to create the multisig address.


**Trent:**

dumpprivkey "mm8Fwn92RU8zvJmH7TCpaYL3v4PTyjN4xd"

    cPxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxis

signrawtransaction "0100000062815a5301749fb9a1434c1072fb67f928f3b5592de88053bccf34da50a1dadad05265f10e01000000b40047304402201dfd957507d6b48b777a6f5c31d85fb8d00513b79c55dbd902c7f6dee90bc4cc0220773f05b481a9dbbc3153cb832acd994caef0d569de49d3b4a125b5f1e637836c014c69522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e21033ba42c942ff7e7fcf42ff604d6ef6c51826f9eea3a04308379c2ade98fb9e70353aeffffffff01f0027515000000001976a9149a59a69866c7668acdd2b36491cfc18229d2348988ac00000000" '[{"txid" : "0ef16552d0dadaa150da34cfbc5380e82d59b5f328f967fb72104c43a1b99f74", "vout" : 1, "scriptPubKey" : "a914824524d69e3c8f2ea66e39af89727bc0e8d3de4b87", "redeemScript" : "522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e21033ba42c942ff7e7fcf42ff604d6ef6c51826f9eea3a04308379c2ade98fb9e70353ae"}]' '["cPxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxis"]'

    {
      "hex" : "0100000062815a5301749fb9a1434c1072fb67f928f3b5592de88053bccf34da50a1dadad05265f10e01000000fdfd000047304402201dfd957507d6b48b777a6f5c31d85fb8d00513b79c55dbd902c7f6dee90bc4cc0220773f05b481a9dbbc3153cb832acd994caef0d569de49d3b4a125b5f1e637836c014830450220576a38baba9c821a5dbfce6be50825322995041a052f8a76016928ee2741b542022100e95dcefd049628e8c422ee584eb1c3feab3d00f7111a29a16f40353ff7de9648014c69522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e21033ba42c942ff7e7fcf42ff604d6ef6c51826f9eea3a04308379c2ade98fb9e70353aeffffffff01f0027515000000001976a9149a59a69866c7668acdd2b36491cfc18229d2348988ac00000000",
      "complete" : true
    }


Send the signed transaction to the network
------------------------------------------

The transaction has the two required signatures, anyone can send it to the network.


sendrawtransaction "0100000062815a5301749fb9a1434c1072fb67f928f3b5592de88053bccf34da50a1dadad05265f10e01000000fdfd000047304402201dfd957507d6b48b777a6f5c31d85fb8d00513b79c55dbd902c7f6dee90bc4cc0220773f05b481a9dbbc3153cb832acd994caef0d569de49d3b4a125b5f1e637836c014830450220576a38baba9c821a5dbfce6be50825322995041a052f8a76016928ee2741b542022100e95dcefd049628e8c422ee584eb1c3feab3d00f7111a29a16f40353ff7de9648014c69522102c16ff447129fae7374d97212cf9fcd88a744da87ff2985869065cd6d17ee5c0b21025cc4b319284aabcdaef6e9a18af0bb73ac5d4b9f2556a214f30686b0173b316e21033ba42c942ff7e7fcf42ff604d6ef6c51826f9eea3a04308379c2ade98fb9e70353aeffffffff01f0027515000000001976a9149a59a69866c7668acdd2b36491cfc18229d2348988ac00000000"

    fea9875ccac102897ff128c868027a05e3d2f9057569529c8e5e94f8d641bc47
