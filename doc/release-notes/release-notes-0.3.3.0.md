Paycoin version 0.3.3.0 is now available from:

  https://github.com/PaycoinFoundation/paycoin/releases

This is a mandatory update, including microprimes updates, replacement prime node
keys and multiple bug fixes.

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
Downgrading to a version prior to 0.3.3.0 will break network compatibility and
cause nodes to disconnect from the network.

Notable changes
===============

Microprime balance and rate modifications
-----------------------------------------
Reduces microprime rates from 25% to 10% over a 90 day period.
At 120 days reduce microprime rate to 40% of the primenode rate.

Changes the required balance on the microprime to match the microprime stake
group at the same time as the fork.

Resolves sync issues
--------------------
Fixes multiple issues with syncing related to both stalling and slow syncing.

0.3.3.0 Change log
===================

Detailed release notes follow.

GUI:
- `b32f59e` Organise optionsdialog (split off Window and Network page)
- `282d543` Make it possible to set user interface language from options dialog
- `eef65bb` Include Link To Wiki
- `dd7c1bd` add Debug window to tray-menu / switch sendCoinsAction and receiveCoi…
- `1091f2b` update some strings used as warning messages in sendcoinsdialog.cpp
- `c4ee968` When a transaction is clicked on overview page, focus it on history page
- `c287d43` Fix display of external scrape transactions in qt wallet.

Build system:
- `0fc0f88` guiutil.cpp/.h: fix a -Wreorder compiler warning and make constructor…
- `8e89a33` Replace instances of lld/llu with the PRI64d/PRI64u macro for MSVC++ …

Primes / Microprimes:
- `a2b8134` remove duplicate prime keys preventing sync
- `a0472b3` Flag primenode database to be updated
- `319d6f3` re-add prime key that was invalidated after one stake
- `23638b0` Fix microprime max balances
- `3f8aa5c` Add 2 keys at the end of the cycle to replace the duplicates.

Miscellaneous:
- `6b4f227` Fix regression in tests introduced in ab3a8eb
- `ec58e32` Add .travis.yml to run all linux gcc builds and tests
- `fadc564` disable sudo so builds run in container environments (non-legacy)
- `89e64a6` Travis build status image in README.md
- `3556b7f` Revert "Remove checkpoint-warning:"
- `a13e866` Swap out checkpoint key for one that we have a private key for.
- `97378b0` Checkpoint server on the testnet
- `d0639cc` CTxMemPool: consolidate two frequently-printed debug.log lines into one
- `28ebc48` CTxMemPool::accept(): do not log FetchInputs failure redundantly
- `8db9b9d` Fixed initial download stall
- `656d2a8` Don't stop users from using 0.0.0.0 as the a bind address
- `7baa80a` Fork for microprime balances and correct invalid primekeys

Credits
=======

Thanks to everyone who contributed to this release:

- Joshua Baldwin
- Nathan Bass
- Mitchell Cash
- Ryan Mottley
- Jeff Garzig (indirectly, authored code committed by other contributers)
- Philip Kaufmann (indirectly, authored code committed by other contributers)
- Wladimir J. van der Laan (indirectly, authored code committed by other contributers)

The following were instrumental in planning and release preparation:

- Matthew Eden
- Adam Matlack
- Jason Sponaugle
