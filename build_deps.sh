#!/bin/bash

wd=$PWD
cd "$(dirname "$0")"
aps="$(dirname $(readlink -e $0))/"

git submodule init
git submodule update


# build glfw both shared and static
cd glfw
mkdir -p shared
cd shared 
cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX:PATH=$aps ..
make -j 4
make install 

