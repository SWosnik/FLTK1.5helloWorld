# FLTK1.5helloWorld
Build the “hello world” example from FLTK 1.5 under Windows (10) or Debian 12 with cmake.

## Windows 
Prerequisites: Download the FLTK library and build it with the desired toolchain (MinGW64 or Visual Studio 2019).


### build with mingw54
Change to the directory where you saved this example.

mkdir build_mingw64
cd build_mingw64
cmake -DFLTK_DIR:STRING=<PATH-TO-FLTK-BUILD-DIR> -G "MinGW Makefiles" ..
cmake --build .

The program will be created in the subdirectory "bin".

### build with Visual Studio 2019
Change to the directory where you saved this example

mkdir build_vs2019
cd build_vs2019
cmake -DFLTK_DIR:STRING=<PATH-TO-FLTK-BUILD-DIR> -G "Visual Studio 16 2019" ..
cmake --build .
The program will be created in the subdirectory "bin/Debug".

## build under debian, fltk installed
Change to the directory where you saved this example.

mkdir build_linux
cd build_linux
cmake ..
cmake --build .

The program will be created in the subdirectory "bin".
