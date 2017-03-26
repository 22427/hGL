#!/bin/bash
git submodule init
git submodule update

mkdir -p include
mkdir -p lib

#build glad
#cd glad
#./build_glad.sh
#cd ..

#build stb
cd stb_build
./build_stb.sh
cd ..

#build glfw
cd glfw
cmake .
make -j4
cd ..

#generate links

cd include

ln -s ../glad/include/glad glad
ln -s ../glfw/include/GLFW GLFW
ln -s ../glm/ glm
ln -s ../glad/include/KHR/

cd ..
cd lib
ln -s ../glfw/src/libglfw3.a libglfw.a

