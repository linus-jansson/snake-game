project(screensaver)
cmake_minimum_required(VERSION 3.10)

set(CXX_STANDARD 11)

if(WIN32)
    add_executable(DVDscreensaver WIN32 main.cpp)
else()
    add_executable(DVDscreensaver main.cpp)
endif()

include_directories(deps/include)

add_library(my_library STATIC
    Window.h
    Window.cpp
    DVD_logo.h
)

if(WIN32)
    find_library(
        SDL2
        NAMES SDL2 
        HINTS ${CMAKE_CURRENT_SOURCE_DIR}/deps/lib
        NO_DEFAULT_PATH
    )
    find_library(
        SDL2main
        NAMES SDL2main
        HINTS ${CMAKE_CURRENT_SOURCE_DIR}/deps/lib
        NO_DEFAULT_PATH
    )
    find_library(
        SDL2_image
        NAMES SDL2_image
        HINTS ${CMAKE_CURRENT_SOURCE_DIR}/deps/lib
        NO_DEFAULT_PATH
    )
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/deps/dlls/libjpeg-9.dll ${CMAKE_CURRENT_BINARY_DIR}/Release/libjpeg-9.dll COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/deps/dlls/libpng16-16.dll ${CMAKE_CURRENT_BINARY_DIR}/Release/libpng16-16.dll COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/deps/dlls/libtiff-5.dll ${CMAKE_CURRENT_BINARY_DIR}/Release/libtiff-5.dll COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/deps/dlls/libwebp-7.dll ${CMAKE_CURRENT_BINARY_DIR}/Release/libwebp-7.dll COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/deps/dlls/SDL2.dll ${CMAKE_CURRENT_BINARY_DIR}/Release/SDL2.dll COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/deps/dlls/SDL2_image.dll ${CMAKE_CURRENT_BINARY_DIR}/Release/SDL2_image.dll COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/deps/dlls/zlib1.dll ${CMAKE_CURRENT_BINARY_DIR}/Release/zlib1.dll COPYONLY)
else()
    find_library(
        SDL2
        NAMES SDL2
    )
    find_library(
        SDL2main
        NAMES SDL2main
    )
    find_library(
        SDL2_image
        NAMES SDL2_image
    )
endif()

MESSAGE(STATUS "LIBS: ${SDL2}, ${SDL2main}, ${SDL2_image}")
target_link_libraries(DVDscreensaver my_library ${SDL2} ${SDL2main} ${SDL2_image} )
