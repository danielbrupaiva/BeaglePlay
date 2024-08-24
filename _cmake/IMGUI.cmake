include(FetchContent)
#---------------------
FetchContent_Declare(
        imgui
#        SOURCE_DIR /home/daniel/CLionProjects/BeaglePlay/vendor/imgui
        GIT_REPOSITORY https://github.com/danielbrupaiva/imgui.git
        GIT_TAG cmake
)
FetchContent_MakeAvailable(imgui)
FetchContent_GetProperties(imgui)
#---------------------
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)