Paycoin version 0.3.0.0 is now available from:

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

Because release 0.3.0.0 implements a protocol update downgrading is not
possible without being disconnected from all updated peers (including the
primenodes).

Notable changes
===============

Normalized stake rates
---------------------

All primenodes will stake at 25% while non-primenodes will continue to stake 5% APR starting July 1st 2015.

Deprecated phase one primenode keys
-----------------------------------

All original primenode keys will be shutdown as of July 1st.

Implemented phase two primenode keys
------------------------------------

Second round of primenodes start coming online 1 week after July 1st and will continue with 2 keys a week until all 50 keys are active.

Added clearorphans command
--------------------------

A rpc command to remove orphaned transactions from the wallet.dat file has been added. Previously only qt wallets were able to remove orphaned transactions.

Added listaddressbook command
-----------------------------

A rpc command to list all the addresses in the wallet has been added. This lists new addresses that do not have a balance on them which otherwise cannot be listed without knowing the account to list addresses from.

0.3.0.0 Change log
===================

Detailed release notes follow.

RPC:
- `6b2ada1` Make rpcdump commands more informative with wallets unlocked for minting
- `680113e` Add clearorphans command to rpc/cli commands
- `203af29` Add new RPC command: `listaddressbook`

Build system:
- `8b75dcc` Fix makefile for OS X when compiling a static binary
- `4fb34b4` Update paths for gitian

GUI:
- `f3ce3c5` simplified qrcode icon that scales gracefully to 16x16

Validation / Staking:
- `aa8f924` refactor prime keys to separate file
- `7a5f54b` Disable compound staking on primenodes.
- `0557c49` Phase/Round 2 Primenodes
- `420b290` Reduce standard staking to 2% and clean-up logic in connect inputs.
- `944c589` Set end of Primenode Phase one for July 1st 12:00 GMT
- `88fd1f0` Change prime stake rate to 25% and normal stake back to 5%

Miscellaneous:
- `79d5644` Build tests:
- `6e8db96` Fix util_tests.cpp
- `bfe7f71` use Paycoin keys for tests
- `971cc03` use Paycoin transaction for tests
- `fb9f6ab` use new version for tests
- `e805876` Remove checknbits test
- `3eb37a5` remove loop define
- `c10e31d` Rename test_bitcoin.cpp to test_paycoin.cpp
- `c75e4ac` Update .gitignore
- `924345d` Remove the rest of the unneeded checknbits test.
- `7003332` Fix translation files
- `39cb9ca` Add new dnsseed nodes:
- `2169063` Add bash-completion script
- `6e3a90b` Cryptocurrency is one word
- `4939b36` Fix translation filenames
- `158e9f9` Update Doxygen logo
- `d62ec70` Lossless image optimisation
- `e41cfd2` Fix some cosmetic flaws in the codebase
- `236c9f2` Rename CreateThread to NewThread
- `c1ab418` Update checkpoints; 100000, 150000, 200000, 210000
- `8835d2b` Update release version and add release notes for 0.3.0.0
- `f6e1cd9` Revert "Rename CreateThread to NewThread"

Network:
- `08dee25` Try more than the first address for a DNS -addnode.
- `7fbf0bc` Use a copy in place of mapMultiArgs["-addnode"].
- `bee60bb` Remove dead IRC code.

Credits
=======

Thanks to everyone who contributed to this release:

- Evan Lucas
- Mark Achée
- Mitchell Cash
- Nathan Bass
- Wladimir J. van der Laan (indirectly, authored code committed by other contributers)

The following were instrumental in planning and release preparation:

- Hans Looman
- Jason Sponaugle
- Matthew Eden
