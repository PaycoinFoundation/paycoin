Paycoin version 0.3.1.0 is now available from:

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
Downgrading to a version prior to 0.3.1.0 will break compatibility with phase 2
primenodes and will cause nodes to disconnect from the network.

Notable changes
===============

Resolved staking on primenodes.
-------------------------------
Added requirements so that phase 2 primenode stakes are accepted by the network.

Fixed testnet.
--------------
Enabled proof of work and changed basic testnet requirements so we can utilize it.

0.3.1.0 Change log
===================

Detailed release notes follow.

GUI:
- `056ef4a` Make user action more straightforward in address book
- `05fc92a` Rename qrcodedialog.ui window title to "QR Code Dialog" and change wi…
- `0b0a53f` Change size of transactiondialog, to allow display of Transaction ID …
- `ad73421` Add icon for debug window
- `15434f6` Add missing version.h and netbase.h to Qt project-file
- `67ba206` Remove virtual keyboard from askpassphrasedialog and small clean-up
- `56d2cb2` New splash screen
- `7957f35` Harmonise the use of ellipsis ("...") to be used in menus, but not on…
- `b05e919` Move many overviewpage settings from code to ui XML-file / set mouse …
- `11b4115` qt: use series of pngs for spinner
- `2fc432a` Small translation-file handling / loading changes and re-work comment…
- `e121452` Move label placeholdertext from sendcoinsentry.cpp to ui-file
- `b00fe70` Allow Qt to wrap long tooltips
- `2ab6f26` Cleanup of src/qt/forms/aboutdialog.ui
- `85fdf23` Remove string "TextLabel" from warningLabel as this is unneeded
- `5ab5f85` Enhance translation possibilities in TransactionDesc / misc other cha…
- `70ecfce` Add 2 labels to the overviewpage that display Wallet and Transaction …
- `bcb7fc7` start rows in askpassphrasedialog.ui at 0 (not 1)
- `e63293a` Remove autocorrection of 0/i in addresses in UI
- `d2cd0d8` Override progress bar on platforms with segmented progress bars
- `b6ee63a` Prevent tooltip filter from ever causing infinite loops
- `5c2a03a` Add code to open (display) debug.log on Windows with the associated a…
- `b921889` Add icon for "About Qt" in menu
- `6a3e798` Paycoin-Qt (Windows only): enable DEP for paycoin-qt.exe

Build system:
- `a723988` Silence useless warning in src/json/json_spirit_writer_template.h to …
- `e325578` Fixes regression introduced in 1788441 that broke compiling on OS X
- `6a7a833` Revert "Fixes regression introduced in 1788441 that broke compiling o…

Validation / Staking:
- `5303c37` Check for the P2 OP code when checking IsProofOfStake
- `9cc6ae9` Set primenode minimum to proper value
- `4fc4f24` Primes for the testnet
- `85df45b` Fix minimum for primenodes to allow syncing the old primestakes
- `3c93bf7` Remove duplicate GetHash() in ConnectBlock
- `a09cf82` Update checkpoints for release
- `2e2ac63` Update minimum protocol for phase 2 primenodes

Miscellaneous:
- `fb66d3f` remove pre-paycoin protocol versions
- `1788441` Split synchronization mechanisms from util.{h,cpp}
- `f55ddf3` Change basic requirements for testnet
- `167849e` Re-enable DNS seeds on the testnet and add one.
- `a76bba5` Small cleanup of .gitignore and add a Mac OS X specific ignore
- `ff34c52` Do not ban addresses on the testnet for misbehaving.
- `2cf744a` ensure that no double timestamps show up in the debug.log, by removin…
- `70a257b` Was showing a negative number. Changes to positive, since negative (T…
- `644465e` Remove dead code: CTxDB::EraseBlockIndex(), CBlockIndex::EraseBlockFr…
- `ad07a7e` CTxMemPool: eliminate redundant lock, GetHash() call
- `c935e4b` Fix signed/unsigned warnings in {script,serialize}.h
- `148d873` Revert "Split synchronization mechanisms from util.{h,cpp}"
- `8c8dbc7` make CheckDiskSpace() use a global static const uint64 for checking r…
- `ea2e789` Remove strncasecmp() + strnicmp() calls and replace that code via boo…
- `2de8296` Alert system DoS prevention
- `05a76ad` Revert "Revert "Rename CreateThread to NewThread""
- `6d0788e` implement CreateThread with boost::thread
- `0bf57ce` Remove contrib/bitrpc
- `b692772` Switch protocol on the correct date

Credits
=======

Thanks to everyone who contributed to this release:

- Mark Achee
- Gavin Anderson (indirectly, authored code committed by other contributers)
- Nathan Bass
- Mitchell Cash
- Mark Corallo (indirectly, authored code committed by other contributers)
- Philip Kaufmann (indirectly, authored code committed by other contributers)
- Wladimir J. van der Laan (indirectly, authored code committed by other contributers)

The following were instrumental in planning and release preparation:

- Jason Sponaugle
- Matthew Eden
