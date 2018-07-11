#!/bin/sh

git shortlog -sne > AUTHORS
./version.sh || exit 127
aclocal || exit 126
autoreconf --install --force --symlink || exit 125

echo "Now run ./configure && make && sudo make install"
