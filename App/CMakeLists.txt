cmake_minimum_required(VERSION 3.22)
#---------------------------------------------------------------------------------------------
if(CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(FATAL_ERROR "-- In-source builds are not allowed.")
endif()
#---------------------------------------------------------------------------------------------
set(PROJECT_NAME App)
project(${PROJECT_NAME})
message("${BoldGreen}-- ${PROJECT_NAME} BUILD ${ColourReset}")
#---------------------------------------------------------------------------------------------
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")
#---------------------------------------------------------------------------------------------
add_executable(${PROJECT_NAME}
        main.cpp
        globals.hpp
        FSM.hpp
        app.hpp app.cpp
)
#---------------------------------------------------------------------------------------------
include(Core)
include(IMGUI)
#---------------------------------------------------------------------------------------------
