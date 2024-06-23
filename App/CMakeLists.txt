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
        FSM.hpp
        glfw.hpp glfw.cpp
        ui.hpp
        image.hpp
        backend.hpp
)
#---------------------
include(Core)
include(IMGUI)
include(stb)