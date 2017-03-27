#!/bin/bash
git submodule init
git submodule update

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

# copying includes
mkdir -p ../include/dep

cp -r stb_build/stb 	../include/dep/
cp -r glad/include/glad ../include/dep/
cp -r glfw/include/GLFW ../include/dep/
cp -r glm/	 	../include/dep/
cp -r glad/include/KHR/ ../include/dep/

cd lib
cp ../glfw/src/libglfw3.a libglfw.a

