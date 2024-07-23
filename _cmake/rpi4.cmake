#-DCMAKE_TOOLCHAIN_FILE=/home/daniel/CLionProjects/BeaglePlay/_cmake/rpi4.cmake
set(CROSS_COMPILER ON)
option(CROSS_COMPILER "Enable cross compiler?" ON)
message("${BoldYellow}-- TOOLCHAIN LOADED${ColourReset}")

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
# define target sysroot
set(TARGET_SYSROOT /home/daniel/CLionProjects/sysroots/rpi4)
set(CMAKE_SYSROOT ${TARGET_SYSROOT})
message("${BoldGreen}-- CMAKE_SYSROOT: ${CMAKE_SYSROOT} ${ColourReset}")
# define compiler work (used by custom toolchain)
set(TARGET_ARCHITECTURE aarch64-linux-gnu)
set(CMAKE_C_COMPILER_WORKS ON)
set(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc)
message("${BoldGreen}-- CMAKE_C_COMPILER: ${CMAKE_C_COMPILER} ${ColourReset}")
set(CMAKE_CXX_COMPILER_WORKS ON)
set(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++)
message("${BoldGreen}-- CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER} ${ColourReset}")
# define C/CXX flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${TARGET_SYSROOT}/usr/include -I${TARGET_SYSROOT}/usr/local/include -I${TARGET_SYSROOT}/usr/lib -I${TARGET_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}")
message("${BoldGreen}-- CMAKE_C_FLAGS: ${CMAKE_C_FLAGS} ${ColourReset}")
set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
message("${BoldGreen}-- CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS} ${ColourReset}")
#
#set(ENV{PKG_CONFIG_PATH} $PKG_CONFIG_PATH:${TARGET_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/pkgconfig)
#set(ENV{PKG_CONFIG_LIBDIR} ${TARGET_SYSROOT}/usr/lib/pkgconfig:${CMAKE_SYSROOT}/usr/share/pkgconfig/:${TARGET_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/pkgconfig:${TARGET_SYSROOT}/usr/lib/pkgconfig)
#set(ENV{PKG_CONFIG_SYSROOT_DIR} ${TARGET_SYSROOT})
# Qt specifics
#set(QT_COMPILER_FLAGS "-march=armv8-a")
#set(QT_COMPILER_FLAGS_RELEASE "-O2 -pipe")
#set(QT_LINKER_FLAGS "-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed")
# where is the target environment located
set(CMAKE_FIND_ROOT_PATH ${TARGET_SYSROOT})
# adjust the default behavior of the FIND_XXX() commands:
# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# search headers and libraries in the target environment
# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
#set(CMAKE_BUILD_RPATH ${TARGET_SYSROOT})

#include(CMakeInitializeConfigs)
#
#function(cmake_initialize_per_config_variable _PREFIX _DOCSTRING)
#    if (_PREFIX MATCHES "CMAKE_(C|CXX|ASM)_FLAGS")
#        set(CMAKE_${CMAKE_MATCH_1}_FLAGS_INIT "${QT_COMPILER_FLAGS}")
#
#        foreach (config DEBUG RELEASE MINSIZEREL RELWITHDEBINFO)
#            if (DEFINED QT_COMPILER_FLAGS_${config})
#                set(CMAKE_${CMAKE_MATCH_1}_FLAGS_${config}_INIT "${QT_COMPILER_FLAGS_${config}}")
#            endif()
#        endforeach()
#    endif()
#
#
#    if (_PREFIX MATCHES "CMAKE_(SHARED|MODULE|EXE)_LINKER_FLAGS")
#        foreach (config SHARED MODULE EXE)
#            set(CMAKE_${config}_LINKER_FLAGS_INIT "${QT_LINKER_FLAGS}")
#        endforeach()
#    endif()
#
#    _cmake_initialize_per_config_variable(${ARGV})
#endfunction()