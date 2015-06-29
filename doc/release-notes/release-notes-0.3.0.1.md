Paycoin version 0.3.0.1 is now available from:

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

This release resolves an issue with staking in 0.3.0.0 so downgrading to it is
not recommended. Downgrading to a version older then 0.3.0.0 will cause a node
to not connect properly. Downgrading is from 0.3.0.1 is not recommended.

Notable changes
===============

Corrected an issue with staking
---------------------

Staking in version 0.3.0.1 was broken do to an issue with the GetProofOfStakeReward code, it has been corrected.

0.3.0.1 Change log
===================

Detailed release notes follow.

Validation / Staking:
- `358b20a` Make sure we pass nTime to GetProofOfStakeReward

Credits
=======

Thanks to everyone who contributed to this release:

- Evan Lucas

The following were instrumental in planning and release preparation:

- Nathan Bass
- Jason Sponaugle
- Matthew Eden
