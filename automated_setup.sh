#!/bin/bash

# initialize the submodules
git submodule init
git submodule update

#compile google test
cd googletest
mkdir build
cd build
cmake ..

make

sudo make install