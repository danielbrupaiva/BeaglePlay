include(FetchContent)
#---------------------------------------------------------------------------------------------
FetchContent_Declare(
        Core
        SOURCE_DIR $ENV{CORE_FOLDER}
)
FetchContent_MakeAvailable(Core)
FetchContent_GetProperties(Core)
#---------------------------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME} PUBLIC Core)