#!/bin/bash

set -eux

CFLAGS=
read CFLAGS <CFLAGS || true

redo-ifchange $2.c #{CFLAGS:+CFLAGS}
clang -I. -MD -MF $2.deps -c -o $3 $2.c $CFLAGS

read DEPS <$2.deps
redo-ifchange ${DEPS#*:}
