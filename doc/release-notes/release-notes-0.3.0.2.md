Paycoin version 0.3.0.2 is now available from:

  https://github.com/PaycoinFoundation/paycoin/releases

This is a mandatory update, including a modification to the primenode stake
rate and many bug fixes.

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

Non-primenodes can safely be downgraded to version 0.3.0.1 without issues.
Downgrading a primenode will cause it to fail to stake.

Notable changes
===============

Resolved staking on primenodes.
---------------------

Removed reserve on primenodes as this causes coins that are part of the same
transaction as the reserve to fail to stake.

0.3.0.2 Change log
===================

Detailed release notes follow.

GUI:
- `e857686` Minor Splashscreen Fix
- `f9b2fc4` XPY Icon Size Fix

Validation / Staking:
- `d4e1e00` Revert "Disable compound staking on primenodes."

Miscellaneous:
- `63445fd` Fix some misspellings

Credits
=======

Thanks to everyone who contributed to this release:

- Nathan Bass
- Mitchell Cash
- Victor Vargas

The following were instrumental in planning and release preparation:

- Jason Sponaugle
- Matthew Eden
