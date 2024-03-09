cmake_minimum_required(VERSION 3.22)
#---------------------------------------------------------------------------------------------
if(CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(FATAL_ERROR "-- In-source builds are not allowed.")
endif()
#---------------------------------------------------------------------------------------------
set(PROJECT_NAME BeaglePlay)
project(${PROJECT_NAME} )
message("${BoldGreen}${PROJECT_NAME} BUILD ${ColourReset}")
#---------------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
#---------------------------------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/_cmake)
include(options)
#---------------------------------------------------------------------------------------------
message("${BoldGreen}Copy external resources to build folder ${ColourReset}")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/logo.png
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/App/resources )
#---------------------------------------------------------------------------------------------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/App)