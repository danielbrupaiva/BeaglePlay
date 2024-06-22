#-DCMAKE_TOOLCHAIN_FILE=_cmake/beagleplay.cmake
set(CROSS_COMPILER ON)
option(CROSS_COMPILER "Enable cross compiler?" ON)
message("${BoldYellow}-- TOOLCHAIN LOADED${ColourReset}")
set(TARGET_ARCHITECTURE aarch64-linux-gnu)
# define compilers
set(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++)
# define C/CXX flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
# define compiler work (used by custom toolchain)
set(CMAKE_C_COMPILER_WORKS ON)
set(CMAKE_CXX_COMPILER_WORKS ON)
# define target sysroot
set(CMAKE_SYSROOT /home/daniel/CLionProjects/sysroots/beagleplay)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)