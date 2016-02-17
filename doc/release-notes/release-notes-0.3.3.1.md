Paycoin version 0.3.3.1 is now available from:

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

Added support for Paycoin URIs in QT wallet.
Fixed crash on send/stake plus general code updates.

0.3.3.1 Change log
===================

Detailed release notes follow.

GUI:
- `2d6dfb9` merge toggleHidden() code into showNormalIfMinimized() to extend the …
- `8a1a967` change initial Balance on overviewpage from "123.456 XPY" to "0 XPY" …
- `722c5dc` Change strings to Paycoin (uppercase) and other miscellaneous fixes
- `18993f7` Correct translatable string from Bitcoin to Paycoin
- `a0cb315` Remove duplicate spaces from a string
- `648fc59` Add an option to open the paycoin.conf in the default editor
- `80dbe2e` Add a notice when selecting edit config in QT
- `02d42ae` Fix Opening on OSX
- `4898c94` Paycoin-Qt (Windows only): extend Resource File
- `0b67ded` Add missing Q_OBJECT in bitcoin.cpp
- `45717b7` Qt: add copyrightLabel to aboutdialog.ui
- `e13d341` Translation strings update
- `20bc095` Move GetStartOnSystemStartup and SetStartOnSystemStartup to GUI code
- `eed5028` move class HelpMessageBox to guiutil.cpp/.h / add button to show Bitc…
- `f2f538e` Periodic translation update
- `9e094f0` Optimise PNG files
- `7fc12cb` Cross-platform "Open debug logfile"
- `4ca32c0` Periodic translations update
- `295751b` Correct a string accidentally referencing Bitcoin
- `4f29cec` Translation updates / string updates
- `2bfee2a` Fix some translation plurals
- `0142107` Change Window title to "Paycoin - Wallet" / misc related renames
- `f51e337` Make sort and filters for transactions and labels case-insensitive
- `0efc89b` Qt: Periodic translation update
- `abaa02c` Revert "Remove spent transactions from the minting table model."
- `f687b68` Add support for opening paycoin: URIs directly.
- `478af1c` Update the copyright strings visible in the Qt to 2016

Build system:
- `3d0e35d` Check if FD_SETSIZE is already defined before trying to define it
- `bcd09f8` Mute this obnoxious unused warning that occurs on linux
- `120ec8e` Fix noinline definition so that it works for more compilers.
- `c5c281a` Rename project to paycoin-qt

Primes / Microprimes:
- `438a2ab` Move primenode dbtype defines in CPrimeNodeDB
- `2c0cd96` Fix the values of the last keys that are checked in primenodes.cpp
- `f7f87dd` Fix microprime help entry (requires an address argument)

Net handling:
- `3f1e85f` Use "IPv6" and "IPv4" in strings as these are the official spellings …
- `2c75804` Use getnameinfo() to get canonical IPv6 addresses
- `2b9374e` Only check for port# after : in ConnectSocketByName
- `7583226` Keep local service information per address
- `e930f30` Take -port into account when resolving -bind's
- `abddf76` Break up CAddrMan's IMPLEMENT_SERIALIZE
- `09d6486` Fix-up GetMyExternalIP
- `fce8b28` Do not listen on blocked networks

Miscellaneous:
- `30b4663` Corrected grammar. As per Principle Of Least Surprise.
- `b77f1f1` Update the note about translations in README.md
- `0b47971` Move help messages out of AppInit2
- `f855eef` Introduce -debugnet option, thereby quieting some redundant debug mes…
- `515fcd6` Document -debugnet option in command line help
- `dbd79b4` Include human readble format for nRequestTime.
- `cc192f7` Make CNetAddr::GetHash() return an unsigned val.
- `0672c5c` Don't overflow signed ints in CBigNum::setint64().
- `2850e9b` Add test case for CBigNum::setint64().
- `c018c69` Fix signed subtraction overflow in CBigNum::setint64().
- `e3abf16` Use C++-style numeric limits instead of C-style.
- `61c56ae` Don't overflow integer on 32-bit machines.
- `1c2c54a` Move NOINLINE definition to test where it's used.
- `9a02361` Should only be mapped when the getdata is done.
- `e3aa65e` JSON-RPC: remove 'getblocknumber' deprecated RPC
- `b936745` Shared code for wallet lock help and check
- `fc873bb` add client startup time as an entry to debug.log (note: logged time i…
- `77ed41f` remove dead "using namespace boost::asio;" from rpcdump.cpp
- `c1fbca9` Reorder AppInit2
- `55e7a09` Fix init issues with the qt app when running on the testnet since 284
- `ebc82dd` fix a memory leak in key.cpp
- `e18933c` Bugfix: getwork: NULL pindexPrev across CreateNewBlock, in case it fails
- `bcd9eeb` add 2 comments to transactionview.cpp to ensure no one moves setPlace…
- `7745644` Split hash functionaliity out of util.h to it's own file.
- `21635f5` Move wallet functions from bitcoinrpc.cpp to rpcwallet.cpp
- `48b4a0b` Move some functions out of bitcoinrpc.cpp to rpcnet.cpp
- `6495c87` Move some blockchain specific stuff out of bitcoinrpc.cpp into rpcblo…
- `1b5b7f6` Fix OSX Compilation Issue
- `c2c014e` Refactor: add IsChainFile helper. LoadBlockIndex() code movement.
- `4bb83f1` Small update to contrib/devtools/README.md
- `537679c` Split synchronization mechanisms from util.{h,cpp}
- `74ba1a0` Use boost::thread locking instead of interprocess
- `815fe7f` Fix DEBUG_LOCKCONTENTION
- `507e90b` exclude CreatePidFile() function on WIN32 as it is unused
- `7528409` Quieten 'getdata' P2P message output
- `d78bbc2` Use linker-arguments only when linking
- `814ffb9` fix a comment to correctly use -upgradewallet
- `74d6c05` Remove comma from setscrapeaddress description
- `769efcd` Better validity checks for scrape addresses
- `8e222bb` Remove unneeded extern from scrapesdb.cpp
- `2427e82` Allow binding to the any address, and report failure
- `ca2ae7a` Rename rpcuser from bitcoinrpc --> paycoinrpc in message dialog
- `d2fa289` Some X11 references snuck back into the source
- `afe7c02` util.h/.ccp: modifiy some comments / rename MyGetSpecialFolderPath() …
- `3efe964` Cleanup leftover docs from the Peerunity fork
- `83e0154` Update forum link to correspond with ownership/URL change

Credits
=======

Thanks to everyone who contributed to this release:

- Joshua Baldwin
- Nathan Bass
- Mitchell Cash
- Ryan Mottley
- R E Broadley (indirectly, authored code committed by other contributers)
- Matt Corallo (indirectly, authored code committed by other contributers)
- Ricardo M. Correia (indirectly, authored code committed by other contributers)
- Luke Dashjr (indirectly, authored code committed by other contributers)
- Jeff Garzig (indirectly, authored code committed by other contributers)
- Philip Kaufmann (indirectly, authored code committed by other contributers)
- Wladimir J. van der Laan (indirectly, authored code committed by other contributers)
- Giel van Schijndel (indirectly, authored code committed by other contributers)
- Pieter Wuille (indirectly, authored code committed by other contributers)
- fsb4000 (indirectly, authored code committed by other contributers)

The following were instrumental in planning and release preparation:

- Matthew Eden
- Adam Matlack
- Richard Nelson
- Jason Sponaugle
