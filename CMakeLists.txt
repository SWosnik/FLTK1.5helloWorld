cmake_minimum_required(VERSION 3.15)
project(DataView)

if(MINGW)
  message("Building MinGW executable: ${PROJECT_NAME}")
  set(CMAKE_CXX_STANDARD_LIBRARIES "-lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 -static-libgcc -static-libstdc++ -lwsock32 -lws2_32 -static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CSS_STANDARD_LIBRARIES}")
  set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

  if(CMAKE_BUILD_TYPE STREQUAL "Debug") # keep console for Debug-Output in Debug build
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
  endif()

  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
elseif (MSVC)
  message("Building MSVC executable: ${PROJECT_NAME}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>)
  set(CMAKE_VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
else ()
  message("Building LINUX executable: ${PROJECT_NAME}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif ()

find_package(FLTK CONFIG REQUIRED)

find_package(FLTK 1.5 CONFIG REQUIRED)

add_subdirectory(src)
