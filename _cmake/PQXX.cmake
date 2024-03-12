include(FetchContent)
set(SKIP_BUILD_TEST ON)
set(INSTALL_TEST OFF)
#---------------------------------------------------------------------------------------------
FetchContent_Declare(
        pqxx
        GIT_REPOSITORY https://github.com/jtv/libpqxx.git
        GIT_TAG 7.8.1
)
FetchContent_MakeAvailable(pqxx)
FetchContent_GetProperties(pqxx)
#---------------------------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME} PUBLIC pqxx)