#!/bin/bash

# Set the compile flags
# Always include debug symbols (-g) when using valgrind.
# Sometimes you might want to turn on optimizations (-O2 or -O3), in
# particular for the competition.
FLAGS="-g -Wall"
OPTFLAGS="-O3"

BUILD="build"

# List all the c files here
OBJECTS="$BUILD/main.o $BUILD/ecse425proj.o $BUILD/ecse425projOPT.o"

# create directory "build" if it doesn't exist
[ -d build ] || mkdir build

# compile! (this will generate an executable named "ecse425proj" in
# the directory "build/")

gcc $FLAGS -c main.c -o $BUILD/main.o
gcc $FLAGS $OPTFLAGS -c ecse425proj.c -o $BUILD/ecse425proj.o
gcc $FLAGS $OPTFLAGS -c ecse425projOPT.c -o $BUILD/ecse425projOPT.o
gcc $FLAGS $OBJECTS -o $BUILD/ecse425proj
