cmake_minimum_required(VERSION 3.15)
project(DataView)

# Enable AddressSanitizer for all platforms
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # Visual Studio
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /fsanitize=address")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /fsanitize=address")
    set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} /fsanitize=address")
    set(CMAKE_LINKER_FLAGS_RELEASE "${CMAKE_LINKER_FLAGS_RELEASE} /fsanitize=address")
    message(STATUS "Using Visual Studio AddressSanitizer")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    # GCC (Linux and MinGW64)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fsanitize=address")
    set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address")
    set(CMAKE_LINKER_FLAGS_RELEASE "${CMAKE_LINKER_FLAGS_RELEASE} -fsanitize=address")

    # Add MinGW64-specific flags
    if(MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libasan")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libasan")
        message(STATUS "Using MinGW64 AddressSanitizer")
    else()
      message(STATUS "Using GCC AddressSanitizer")
    endif()
endif()

# Optional: Set AddressSanitizer runtime flags
set(ENV{ASAN_OPTIONS} "detect_leaks=1:malloc_context=1:log_path=asan_log.%p")

# Optional: Add AddressSanitizer libraries explicitly

# target_link_libraries(your_target_name -lasan)


if(MINGW)
  message("Building MinGW executable: ${PROJECT_NAME}")
  set(CMAKE_CXX_STANDARD_LIBRARIES "-lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 -static-libgcc -static-libstdc++ -lwsock32 -lws2_32 -static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CSS_STANDARD_LIBRARIES}")
  set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
elseif (MSVC)
  message("Building MSVC executable: ${PROJECT_NAME}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
else ()
  message("Building LINUX executable: ${PROJECT_NAME}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif ()

find_package(FLTK CONFIG REQUIRED)

find_package(FLTK 1.5 CONFIG REQUIRED)

add_subdirectory(src)



if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
elseif(MINGW)
endif()