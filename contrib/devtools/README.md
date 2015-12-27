Contents
========
This directory contains tools for developers working on this repository.

fix-copyright-headers.py
========================

Every year newly updated files need to have its copyright headers updated to reflect the current year.
If you run this script from src/ it will automatically update the year on the copyright header for all
.cpp and .h files if these have a git commit from the current year.

For example a file changed in 2015 (with 2015 being the current year):
```// Copyright (c) 2013-2014 The Paycoin developers```

would be changed to:
```// Copyright (c) 2013-2015 The Paycoin developers```

optimize-pngs.py
================

A script to optimize png files in the paycoin
repository (requires pngcrush).

update-translations.py
=======================

Run this script from the root of the repository to update all translations from transifex.
It will do the following automatically:

- fetch all translations
- post-process them into valid and committable format
- add missing translations to the build system (TODO)

See doc/translation-process.md for more information.
