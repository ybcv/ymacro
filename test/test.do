DEPS="test.c"

redo-ifchange $DEPS
redo-ifchange ../y.h
clang -g -o $2 $DEPS
