Paycoin version 0.3.2.0 is now available from:

  https://github.com/PaycoinFoundation/paycoin/releases

This is a mandatory update, including microprimes and many bug fixes.

Please report bugs using the issue tracker at github:

  https://github.com/PaycoinFoundation/paycoin/issues

Upgrading and downgrading
=========================

How to Upgrade
--------------

If you are running an older version, shut it down. Wait until it has completely
shut down (this could take a few minutes), then run the installer (on Windows)
or just copy over /Applications/Paycoin-Qt (on Mac) or paycoind/paycoin-qt (on Linux).

If you encounter any issues starting the new wallet it is recommended that you delete and resync the blockchain. To delete the blockchain look in the
Paycoin data directory (listed below) and delete everything except the wallet.dat and paycoin.conf

Linux : ~/.paycoin/

Windows : %appdata%\Paycoin

Mac : ~/Library/Application Support/Paycoin

It is highly recommended that if you do not have a backup of your wallet.dat
to go ahead and make one before deleting the blockchain.

The listed directories are the defaults, if using the datadir flag make sure to
look in the assigned directory.

If after the blockchain is synced you find your balance is incorrect please run:

repairwallet

If using the daemon this can be done the same as any other command, for QT users
please proceed to help > debug window > console and enter the command from there
(you may press escape to close out of the console).

Downgrading warning
---------------------
Downgrading to a version prior to 0.3.2.0 will break network compatibility and
cause nodes to disconnect from the network.

Notable changes
===============

Microprimes
-----------
Prime-like staking for select addresses (former ZC prime staker owners).

Network burn addresses
----------------------
Addresses for both the mainnet and testnet that when coins are sent to are
removed from both the UTXO and the money supply.

mainnet: PLgqKBNdyGJ4rC21efAQhDUsrZZRU4qcQo
testnet: msccTG4mjNF8eTps29pFrEiw6ozFM5dwJ8

0.3.2.0 Change log
===================

Detailed release notes follow.

GUI:
- `7100b42` fix crash: CoinControl "space" bug
- `49bd520` Add function to open a transaction via ledger from transactions table
- `0200529` Remove spent transactions from the minting table model.
- `54b5442` move most explicit getters in optionsmodel to header
- `9848e53` Qt: small header changes / fixes
- `7f2b1d7` Enhance Qt5 compatibility

Primes / Microprimes:
- `2a356db` Check the primenode key on app start and throw an error if invalid.
- `7b7bc97` Move primenode id script generation out of wallet.cpp into primenodes…
- `3fdda39` Fix a bug where microPrimeGroup isn't initialized on Primenodes
- `5743900` Primenode and microprime stake confirmation tests.
- `ab3a8eb` Cleanup primenode header declarations
- `8067188` Don't split the stake on microprimes.
- `771984e` RPC command to look up microprime data in wallet.
- `bcc529d` Microprimes for the main net
- `7c0eb7c` safety

Database handling:
- `a064a7b` Encapsulate BDB environment inside new CDBEnv class
- `65efeb0` Update detachdb comment in help
- `5e29c48` Create CDBEnv::TxnBegin(), and use it in CDB::TxnBegin()
- `4e7883c` Remove unused nested BDB transaction support
- `64367be` CDB::CDB: properly initialize activeTxn to NULL
- `55014b6` Further CDBEnv encapsulation work.
- `fb8ea7e` Remove CTxDB::ReadOwnerTxes.
- `f130bf1` Removed duplicated lock
- `d28a6ef` Run BDB disk-less for test_paycoin
- `3610d69` Simplify CDBEnv::Open() / fix small glitches
- `5e9c8d8` Use a CriticalSection when writing to the primenode database
- `b23a182` Lock writes to scrapes database with CriticalSection.

Miscellaneous:
- `7d29ab4` Show when node is misbehaving, not just at the point that it gets ban…
- `9a4ab80` = instead of == in multisig_tests.cpp
- `aa568b6` Fix regression in tests introduced in a775971
- `abc58b4` add default value in -timout description
- `f515a5e` RPC: Forbid RPC username == RPC password
- `ccdd452` Network burn addresses for mainnet and testnet
- `2d8d8a4` remove "checkorder" and "reply" P2P commands
- `5f2d90a` Reorganize(): remove spurious TxnAbort()
- `e97ca96` clear path cache after getting a proper config file
- `3c6ee34` Improve error reporting at startup
- `fcb476b` Correct some small anomalies in COPYING
- `7134feb` Very basic accounting tests for general sanity checking
- `c09cc69` Use BOOST_CHECK_EQUAL where viable
- `1794ce5` Fix spacing on shrinkdebugfile help message
- `15a1c9c` Add the testnet genesis block to the testnet checkpoints
- `4c03219` Kill warning from unavoidable signed/unsigned comparison in bitcoinrp…
- `eec4c58` Upgrade OpenSSL to 1.0.1h
- `7fd751a` Add a Paycoin files explanation document
- `b41d0e4` Add compatibility for miniupnpc api 14
- `f63ee42` Stop processing messages on full send buffer and dont disconnect
- `8cadd8c` Add a '-stake' flag to disable the staking thread
- `b5f4b94` Remove invalid/unused pchMessageStart declaration
- `54eef85` Remove unused bool from GetMessageStart
- `f875138` Update protocol for fork
- `91ff2e0` Stupid pro file

Credits
=======

Thanks to everyone who contributed to this release:

- Joshua Baldwin
- Nathan Bass
- Mitchell Cash
- R E Broadley (indirectly, authored code committed by other contributers)
- Mark Corallo (indirectly, authored code committed by other contributers)
- fsb4000 (indirectly, authored code committed by other contributers)
- Jeff Garzig (indirectly, authored code committed by other contributers)
- Philip Kaufmann (indirectly, authored code committed by other contributers)
- Gregory Maxwell (indirectly, authored code committed by other contributers)
- Wladimir J. van der Laan (indirectly, authored code committed by other contributers)
- Pieter Wuille (indirectly, authored code committed by other contributers)
- xanatos (indirectly, authored code committed by other contributers)

The following were instrumental in planning and release preparation:

- Matthew Eden
- Adam Matlack
- Jason Sponaugle
