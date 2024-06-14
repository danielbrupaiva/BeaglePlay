if(CROSS_COMPILER)
    message("${BoldYellow}-- CROSS_COMPILER: ${CROSS_COMPILER}${ColourReset}")
#    set(PostgreSQL_FOUND ON)
    set(PostgreSQL_LIBRARY ${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/libpq.so)
#    set(PostgreSQL_INCLUDE_DIRS ${CMAKE_SYSROOT}/usr/include/postgresql)
#    set(PostgreSQL_LIBRARY_DIRS ${CMAKE_SYSROOT}/usr/lib/postgresql)
#    target_include_directories(${PROJECT_NAME} PUBLIC ${PostgreSQL_INCLUDE_DIRS})
#    target_link_directories(${PROJECT_NAME} PUBLIC ${PostgreSQL_LIBRARY_DIRS})
#    target_link_libraries(${PROJECT_NAME} PUBLIC ${PostgreSQL_LIBRARY})
endif ()

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