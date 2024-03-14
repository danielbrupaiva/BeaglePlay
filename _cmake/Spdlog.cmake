#---------------------------------------------------------------------------------------------
if(BUILD_FROM_SRC)
    include(FetchContent)
    FetchContent_Declare(
            spdlog
            GIT_REPOSITORY https://github.com/gabime/spdlog.git
            GIT_TAG v1.13.0
    )
    FetchContent_MakeAvailable(spdlog)
    FetchContent_GetProperties(spdlog)
else ()
    find_package(spdlog REQUIRED)
endif ()
#---------------------------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)