#---------------------
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()
#---------------------
set(ENV{APP_FOLDER} ${CMAKE_CURRENT_SOURCE_DIR}/App)
message("${BoldYellow}-- App folder: $ENV{APP_FOLDER}${ColourReset}")
#---------------------
set(ENV{CORE_FOLDER} ${CMAKE_CURRENT_SOURCE_DIR}/Core)
message("${BoldYellow}-- Core folder: $ENV{CORE_FOLDER}${ColourReset}")
#---------------------
set(ENV{VENDOR_FOLDER} ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
message("${BoldYellow}-- Vendor folder: $ENV{VENDOR_FOLDER}${ColourReset}")
#---------------------
option(ENV{CROSS_COMPILER} "CROSS COMPILER" OFF)
message("${BoldYellow}-- CROSS COMPILER: $ENV{CROSS_COMPILER}${ColourReset}")
#---------------------
option(ENV{BUILD_FROM_SRC} "BUILD FROM SOURCE" OFF)
message("${BoldYellow}-- BUILD_FROM_SRC: $ENV{BUILD_FROM_SRC}${ColourReset}")
#---------------------
option(ENV{OPENGL3} "OPENGL3" ON)
message("${BoldYellow}-- OPENGL3: $ENV{OPENGL3}${ColourReset}")
#---------------------
option(ENV{VULKAN} "VULKAN" OFF)
message("${BoldYellow}-- VULKAN: $ENV{VULKAN}${ColourReset}")
#---------------------
option(ENV{GLFW} "GLFW" ON)
message("${BoldYellow}-- GLFW: $ENV{GLFW}${ColourReset}")
#---------------------
option(ENV{SDL3} "SDL3" OFF)
message("${BoldYellow}-- SDL3: $ENV{SDL3}${ColourReset}")
#---------------------
option(ENV{SDL3_image} "SDL3_image" OFF)
message("${BoldYellow}-- SDL3_image: $ENV{SDL3_image}${ColourReset}")
#---------------------