g++ -c -fPIC stb.cpp -I include/ -o r.o
ar rcs ../lib/libstb.a r.o 

mkdir -p stb

csplit ../stb/stb_image.h '/^#ifdef STB_IMAGE_IMPLEMENTATION$/'
mv xx00 stb/stb_image.h

csplit ../stb/stb_image_write.h '/^#ifdef STB_IMAGE_WRITE_IMPLEMENTATION$/'
mv xx00 stb/stb_image_write.h

