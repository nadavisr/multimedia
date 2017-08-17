cmake_minimum_required(VERSION 3.5)
project(jpeg_encode_mod)


set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

#set(CMAKE_FIND_ROOT_PATH  ${CMAKE_FIND_ROOT_PATH} /usr/lib/aarch64-linux-gnu )
#set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_VERBOSE_MAKEFILE ON)

#set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(ROOT_PATH /media/ubuntu/mSata)

set(INCLUDE_DIR ${ROOT_PATH}/git/multimedia/include ${ROOT_PATH}/git/multimedia/include/libjpeg-8b /usr/include/libdrm)
set(LIB_DIR /usr/lib/aarch64-linux-gnu /usr/lib/aarch64-linux-gnu/tegra)

file(GLOB_RECURSE COMMON_CLASSES "${ROOT_PATH}/git/multimedia/common/classes/*.cpp" )
file(GLOB_RECURSE EXT_CLASSES "${ROOT_PATH}/git/multimedia/common/ext_classes/*.cpp")

set(SOURCE_FILES
        jpeg_encode.h
        jpeg_encode_csvparser.cpp
        jpeg_encode_main.cpp
        )

include_directories(${INCLUDE_DIR} )
link_directories(${LIB_DIR})

add_executable(jpeg_encode_mod ${SOURCE_FILES} ${COMMON_CLASSES} ${EXT_CLASSES})

target_link_libraries(jpeg_encode_mod  pthread v4l2 EGL GLESv2 X11 nvbuf_utils nvjpeg nvosd drm)