include(FetchContent)
#---------------------
message("${BoldYellow}-- FMT${ColourReset}")
if(BUILD_FROM_SRC)
    message("${BoldYellow}-- BUILDING FROM SRC${ColourReset}")
    include(FetchContent)
    FetchContent_Declare(
            fmt
            GIT_REPOSITORY https://github.com/fmtlib/fmt
            GIT_TAG        0c9fce2ffefecfdce794e1859584e25877b7b592) #11.0.2
    FetchContent_MakeAvailable(fmt)
endif ()
#---------------------
target_link_libraries(${PROJECT_NAME} PUBLIC fmt)
