#!/bin/sh

set -e

mkdir advent/
ln -s guile/*.scm advent/
ln -s ../.libs/libadvent.so advent/libcore.so

# EOF #
