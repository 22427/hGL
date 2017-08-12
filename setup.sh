#!/bin/bash
git submodule init
git submodule update

wd=$PWD
cd "$(dirname "$0")"

git submodule init
git submodule update


# build glfw both shared and static
cd dep/glfw
mkdir -p shared
cd shared 
cmake -DBUILD_SHARED_LIBS=ON ..
make -j 4
cd ..

mkdir -p static
cd static
cmake -DBUILD_SHARED_LIBS=OFF ..
make -j 4
cd ..

cd ..

# copying includes
mkdir -p ../include/dep

cp -r glad/include/glad ../include/dep/
cp -r glfw/include/GLFW ../include/dep/
cp -r glm/glm	        ../include/dep/
cp -r glad/include/KHR/ ../include/dep/

cd ..

# copying the glfw libs
mkdir -p lib
cd lib
cp ../dep/glfw/static/src/libglfw3.a libglfw3.a
cp ../dep/glfw/shared/src/libglfw.so.3.3 libglfw.so.3.3
ln -s  libglfw.so.3.3 libglfw.so.3
ln -s  libglfw.so.3 libglfw.so
