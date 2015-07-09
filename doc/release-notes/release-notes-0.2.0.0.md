Paycoin version 0.2.0.0 is now available from:

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

In some cases users may be required to delete and resync their blockchain do to
a race/version issue with Berkeley DB. To delete the blockchain look in the
Paycoin data directory (listed below) and delete everything except the
wallet.dat and paycoin.conf

Linux : ~/.paycoin/

Windows : %appdata%\Roaming\Paycoin

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

Because release 0.2.0.0 implements a protocol update downgrading is not
possible without being disconnected from all updated peers (including the
primenodes).

Notable changes
===============

Primenode stake rates
---------------------

All primenodes will stake at 100% starting April 20th 2015.

Synchronization fixed
---------------------

Synchronization has been patched and should no longer stall every 500 blocks
after block 8045. The patch will fetch new blocks after a given amount of time
if new blocks have not been pulled in.

Remove checkpoint warning
-------------------------

The warning regarding broadcast checkpoints has been removed. The broadcast
checkpoints themselves are non-functional, the future of which has yet to be
determined. Hardened checkpoints are still encoded into the wallet for chain
integrity.

Added listaddressgroupings
--------------------------

The listaddressgroupings function from Bitcoin Core has been merged. It is
recommended that daemon users use this for accounting instead of the
listaccounts function.

Updated qt resources
--------------------

Icons and other image files updated to replace incorrect paybase branding.

Documentation
-------------

Readmes and other documentation updated with correct copyright information and
upstream references.

Many of these were based off of peercoin and/or had out of date links.

0.2.0.0 Change log
===================

Detailed release notes follow.

RPC:
- `008f818` Update bitcoinrpc.h (added listaddressgroupings function)
- `f7af96c` Factoring: listaddressgroupings
- `e6c3af5` Factoring: listaddressgroupings
- `837776d` Factoring: listaddressgroupings

Build system:
- `26a308a` File needs to be regenerated every time to get proper version
- `f1ac7dc` use new qt binary name in gitian builds
- `278b4cc` point gitian build at foundation repo

Wallet:
- `4161ea2` Add debug information when collecting coins for staking

GUI:
- `af5ea85` Update sv translations per github issue 20
- `3cd3324` Update resources
- `daf00b4` Fix the resources that were missed earlier

Validation / Staking:
- `dee9f83` Add Max Time Since Best Block
- `2abed74` Change all stakerates to 100% after Mon, 06 Apr 2015 12:00:00 GMT
- `66d4c5f` check rate change for new stakes
- `68a993c` Update current and minimum protocol
- `34b46fa` Use same timestamp/variable for primenode rates and protocol version
- `d37299e` drop peers after rate change time
- `5154231` fix minimum version global
- `e09a4ec` Update timestamp for stake-rates based on announcement

Miscellaneous:
- `49f4652` Bugfix -port was not used properly
- `80cb5ce` More ignores
- `459fc54` Copyright fix.
- `7d8b271` Copyright fix.
- `6c0d6ab` Corrected version
- `daf29bd` Get correct version from git
- `925d391` Added debian package building files
- `b242711` Updated checkpoints
- `767da4c` Update acknolwedgements in README_windows.txt
- `4b1206b` Fix version string to list properly
- `88fbd4b` Remove checkpoint-warning
- `5d42eb1` Bring changelog and debian package version inline with current
- `148b3d4` Update Links
- `8541f0d` Update README.md
- `9901576` Update doc/README
- `638f0a0` Update README.md
- `c0faa76` Update README.md
- `177ecca` Checkpoints for every 2500 or so blocks from 50000 to 95000
- `62a3da1` Update GitHub URLs to point to PaycoinFoundation/paycoin
- `1ac376d` Update version numbers to 0.1.2.26
- `b8837fe` Fix spelling mistakes
- `6b20f1d` Remove printf lines containing PRId64 as this breaks gitian builds
- `19ca0ef` Point GitHub URL to PaycoinFoundation
- `9a47b43` Update HTTP to HTTPS
- `12ae607` Fix references to the MIT licence
- `a0a6b5f` Replace reference to license.txt with COPYING
- `492869c` Fix translation file names

Credits
=======

Thanks to everyone who contributed to this release:

- Craig
- Crestington
- Evan Lucas
- Hans Looman
- Jason Sponaugle
- Mark Achée
- Marlon Hanks
- Mitchell Cash
- Nathan Bass
- Paycoin Developer Team
- Treefunder Incorporated
- Victor J Vargas II
- wdl1908
