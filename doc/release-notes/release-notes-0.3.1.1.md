Paycoin version 0.3.1.1 is now available from:

  https://github.com/PaycoinFoundation/paycoin/releases

This is an optional update (for normal users), including scrape addresses and general code cleanup.

For users on the testnet this is a mandatory update as it includes micro-primes for beta testing.

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

Linux : `~/.paycoin/`

Windows : `%appdata%\Paycoin`

Mac : `~/Library/Application Support/Paycoin`

It is highly recommended that if you do not have a backup of your wallet.dat
to go ahead and make one before deleting the blockchain.

The listed directories are the defaults, if using the datadir flag make sure to
look in the assigned directory.

If after the blockchain is synced you find your balance is incorrect please run:

`repairwallet`

If using the daemon this can be done the same as any other command, for QT users
please proceed to help > debug window > console and enter the command from there
(you may press escape to close out of the console).

Downgrading warning
---------------------
Normal users are safe to downgrade to version 0.3.1.0.

This is a mandatory update for testnet users, downgrading to a version prior
will break compatibility with the network.

Notable changes
===============

- Scrape addresses (allow scraping the reward off of a stake to a separate address).
- Updated alert key (for use in future releases, do to ban potential from peers this won't be used immediately).
- Managing primenode keys via database instead of in memory vectors.
- Reduced number of primenode keys in code by removing legacy key requirements during sync.
- Checkpoints for the testnet.
- Micro-primes for the testnet.

0.3.1.1 Change log
===================

Detailed release notes follow.

GUI:
- `01aaa46` Partial scrape address control functionality for QT wallet.

Build system:
- `594962d` Minor update to makefiles.

Validation / Staking:
- `8c063c4` Add a testnet checkpoint at block 546
- `26962f9` Refactor primenode handling.
- `723ee98` Remove phase 1 prime keys.
- `5128bbb` Remove deprecated primenoderate option from CreateCoinStake.
- `4b5e86e` Refactor primekeys.cpp into primenodes.cpp/.h
- `08c45fb` Move primekeys out of primenodes.cpp to their own file.
- `fa4ef2e` Implement microprimes (testnet).

Network / Peer handling:
- `9726be4` Do not consider inbound peers for outbound network group exclusion.
- `307bc9d` Replace the alert key with something that we have a private key for...
- `cc463dc` P2P: Do not request blocks from peers with fewer blocks than us
- `453598d` CAddrDB: Replace BDB-managed addr.dat with internally managed peers.dat

Miscellaneous:
- `11ad091` Reopen debug.log on SIGHUP
- `c00ae1b` Fix Up to date QT-Status
- `d471352` fix DebugLog file opens twice after clicking "Open" in RPC Console In…
- `8234c7c` Write used OpenSSL library version to debug.log
- `84d0422` Improve readability of CAddrInfo::IsTerrible
- `478eb66` Update contrib/debian and remove system json_spirit patch.
- `2f31211` Allow select()ing up to 1024 file descriptors on Windows
- `4225938` Prevent prevent file descriptor leak in ShrinkDebugFile()
- `fabc23f` Reduce repeat call to GetHash during ProcessMessage "block"
- `a59f7b8` Update INSTALL
- `a775971` Implement scrape addresses
- `2c18b04` Fix segmentation fault on help prompt and add standard logging.
- `503d871` Bring README more inline with current events
- `ee26fb8` Make truncating the debug.log file an option.
- `2b4c771` add used datadir to debug.log


Credits
=======

Thanks to everyone who contributed to this release:

- Joshua Baldwin (indirectly, authored code committed by other contributers)
- Tariq Bashir (indirectly, authored code committed by other contributers)
- Nathan Bass
- Mitchell Cash
- Jeff Garzik (indirectly, authored code committed by other contributers)
- Michael Hendricks (indirectly, authored code committed by other contributers)
- Philip Kaufmann (indirectly, authored code committed by other contributers)
- Gregory Maxwell (indirectly, authored code committed by other contributers)
- Teran McKinney (indirectly, authored code committed by other contributers)
- Pieter Wuille (indirectly, authored code committed by other contributers)
- xanatos (indirectly, authored code committed by other contributers)

The following were instrumental in planning and release preparation:

- Jason Sponaugle
- Matthew Eden
