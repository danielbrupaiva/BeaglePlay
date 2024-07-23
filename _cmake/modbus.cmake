include(FetchContent)
#---------------------
message("${BoldYellow}-- LIBMODBUS${ColourReset}")
if(BUILD_FROM_SRC)
    message("${BoldYellow}-- BUILDING FROM SRC${ColourReset}")
    include(FetchContent)
    FetchContent_Declare(
            modbus
            GIT_REPOSITORY https://github.com/stephane/libmodbus.git
            GIT_TAG dde16d5  # Adjust this tag to the version you need
    )
    FetchContent_MakeAvailable(modbus)
endif ()
#---------------------
target_link_libraries(${PROJECT_NAME} PUBLIC modbus)
