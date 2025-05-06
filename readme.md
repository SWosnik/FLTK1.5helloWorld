# build with mingw54

mkdir build_mingw64
cd build_mingw64
cmake -DFLTK_DIR:STRING=<PATH-TO-FLTK-DIR> -G "MinGW Makefiles" ..
cmake --build .

# build with Visual Studio 2019

mkdir build_vs2019
cd build_vs2019
cmake -DFLTK_DIR:STRING=<PATH-TO-FLTK-DIR> -G "Visual Studio 16 2019" ..
cmake --build .

# build under debian, fltk installed

mkdir build_linux
cd build_linux
cmake ..
cmake --build .
