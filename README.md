Paycoin Core integration/staging tree
=====================================

[![Build Status](https://travis-ci.org/PaycoinFoundation/paycoin.svg?branch=master)](https://travis-ci.org/PaycoinFoundation/paycoin)

https://www.paycoin.com

What is Paycoin?
----------------

Paycoin is an experimental new digital currency that enables instant payments to
anyone, anywhere in the world. Paycoin uses a proof-of-stake method in order for
the Paycoin blockchain network to achieve distributed consensus. Paycoin Core is
the name of open source software which enables the use of this currency.

For more information, as well as an immediately useable, binary version of the
Paycoin Core software, see https://www.paycoin.com/#wallet.

License
-------

Paycoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see http://opensource.org/licenses/MIT.

Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the Paycoin
development team members simply pulls it.

If it is a *more complicated or potentially controversial* change, then the patch
submitter will be asked to start a discussion (if they haven't already) on the
[TalkXPY forum](https://www.talkxpy.com/category/8/paycoin-coincode)

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see [doc/coding.md](doc/coding.md)) or are
controversial.

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/PaycoinFoundation/paycoin/tags) are created
regularly to indicate new official, stable release versions of Paycoin.

Translations
------------

Changes to translations as well as new translations can be submitted to
[Paycoin Core's Transifex page](https://www.transifex.com/projects/p/paycoin/).

Translations are periodically pulled from Transifex and merged into the git repository. See the
[translation process](doc/translation_process.md) for details on how this works.

**Important**: We do not accept translation changes as GitHub pull requests because the next
pull from Transifex would automatically overwrite them again.
