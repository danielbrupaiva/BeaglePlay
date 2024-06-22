#---------------------
message("${BoldYellow}-- SPDLOG${ColourReset}")
if(BUILD_FROM_SRC)
#    if(CROSS_COMPILER)
    #    message("${BoldYellow}-- CROSS_COMPILER: ${CROSS_COMPILER}${ColourReset}")
    #    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    #    set(CMAKE_HAVE_THREADS_LIBRARY ON)
    #    set(CMAKE_USE_WIN32_THREADS_INIT OFF)
    #    set(CMAKE_USE_PTHREADS_INIT ON)
    #    set(THREADS_PREFER_PTHREAD_FLAG ON)
    #endif ()
    message("${BoldYellow}-- BUILDING FROM SRC${ColourReset}")
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
#---------------------
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)