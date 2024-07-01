cmake_minimum_required(VERSION 3.22)
#---------------------
if(CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(FATAL_ERROR "-- In-source builds are not allowed.")
endif()
#---------------------
set(PROJECT_NAME App)
project(${PROJECT_NAME} C CXX)
message("${BoldGreen}-- ${PROJECT_NAME} BUILD ${ColourReset}")
#---------------------
add_executable(${PROJECT_NAME}
        main.cpp
        globals.hpp
        glfw.hpp glfw.cpp
        backend.hpp
        image.hpp
        ui.hpp
        screen_1.hpp
        screen_2.hpp
        screen_3.hpp
        screen_4.hpp
        screen_5.hpp
)
#---------------------
include(Core)
include(IMGUI)
include(stb)