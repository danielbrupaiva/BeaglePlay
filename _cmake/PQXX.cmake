set(SKIP_BUILD_TEST ON)
set(INSTALL_TEST OFF)
#---------------------------------------------------------------------------------------------
message("${BoldYellow}-- PQXX${ColourReset}")
if(BUILD_FROM_SRC)
    message("${BoldYellow}-- BUILDING FROM SRC${ColourReset}")
    include(FetchContent)
    FetchContent_Declare(
            pqxx
            GIT_REPOSITORY https://github.com/jtv/libpqxx.git
            GIT_TAG 7.8.1
    )
    FetchContent_MakeAvailable(pqxx)
    FetchContent_GetProperties(pqxx)
    target_link_libraries(${PROJECT_NAME} PUBLIC pqxx)
else ()
    find_package(libpqxx REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC libpqxx::pqxx)
endif ()
#---------------------------------------------------------------------------------------------
