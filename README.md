[![pipeline status](https://gitlab.yapbreak.fr/libraries/libyaplog/badges/master/pipeline.svg)](https://gitlab.yapbreak.fr/libraries/libyaplog/commits/master)
[![coverage report](https://gitlab.yapbreak.fr/libraries/libyaplog/badges/master/coverage.svg)](https://gitlab.yapbreak.fr/libraries/libyaplog/commits/master)

# Purpose

This directory contains the source code of Yaplog library.

The YapLog library is a free software. See COPYING file for copying permission.

It provides a basic logger functionnality for C++ application.
See files in samples folder for example on how to use it.

# Installation

To compile and install the library, simply run the following commands:

```bash
./autogen.sh
./configure
make
make check # (optional)
make doc # (generate documentation)
sudo make install
```

