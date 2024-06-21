#---------------------
# SDL3
#---------------------
if(SDL3)
    message("${BoldYellow}-- SDL3: ${SDL3}${ColourReset}")
    if(NOT BUILD_FROM_SRC)
        find_package(SDL3 REQUIRED)
    elseif( NOT SDL3_FOUND OR BUILD_FROM_SRC )
        message("${BoldYellow}-- SDL3 NOT FOUND${ColourReset}")
        message("${BoldYellow}-- BUILDING FROM SRC${ColourReset}")
        FetchContent_Declare(
                SDL3
                GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
                GIT_TAG 495e432fb9776fdc13a8d96179136064ccddf6e5
        )
        FetchContent_MakeAvailable(SDL3)
        FetchContent_GetProperties(SDL3)
    endif ()
    target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3)
endif()
#---------------------
# SDL3 image SDL3_image_FOUND
#---------------------
if(SDL3_image)
    message("${BoldYellow}-- SDL3_image: ${SDL3_image}${ColourReset}")
    if(NOT BUILD_FROM_SRC)
        find_package(SDL3_image REQUIRED)
    elseif ( NOT SDL3_image_FOUND OR BUILD_FROM_SRC )
        message("${BoldYellow}-- SDL3_IMAGE NOT FOUND${ColourReset}")
        message("${BoldYellow}-- BUILDING FROM SRC${ColourReset}")
        # set(SDL3IMAGE_BUILD_SHARED_LIBS OFF)
        FetchContent_Declare(
                SDL3_image
                GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
                GIT_TAG 5baa3c8c7a64ccb00c6a9ec926d238a7e2e6a50a
        )
        FetchContent_MakeAvailable(SDL3_image)
        FetchContent_GetProperties(SDL3_image)
        #        include_directories(${SDL3IMAGE_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME} PUBLIC SDL3_image)
    endif ()
    target_link_libraries(${PROJECT_NAME} PUBLIC SDL3_image::SDL3_image)
endif()
#---------------------