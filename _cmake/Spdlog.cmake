include(FetchContent)
#---------------------------------------------------------------------------------------------
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(spdlog)
FetchContent_GetProperties(spdlog)
#---------------------------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)