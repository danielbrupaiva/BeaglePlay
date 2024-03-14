set(SKIP_BUILD_TEST ON)
set(INSTALL_TEST OFF)
#---------------------------------------------------------------------------------------------
if(BUILD_FROM_SRC)
    include(FetchContent)
    FetchContent_Declare(
            pqxx
            GIT_REPOSITORY https://github.com/jtv/libpqxx.git
            GIT_TAG 7.8.1
    )
    FetchContent_MakeAvailable(pqxx)
    FetchContent_GetProperties(pqxx)
else ()
    find_package(libpqxx REQUIRED)
endif ()
#---------------------------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME} PUBLIC libpqxx::pqxx)