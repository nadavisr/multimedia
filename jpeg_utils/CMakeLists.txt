cmake_minimum_required(VERSION 3.5)
project(jpeg_utils)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(ROOT_PATH /media/ubuntu/mSata)
set(INCLUDE_DIR ${ROOT_PATH}/git/multimedia/include ${ROOT_PATH}/git/multimedia/include/libjpeg-8b /usr/include/libdrm)
set(LIB_DIR /usr/lib/aarch64-linux-gnu /usr/lib/aarch64-linux-gnu/tegra)

file(GLOB_RECURSE COMMON_FILES "${ROOT_PATH}/git/multimedia/common/classes/*.cpp")

set(SOURCE_FILES jpegUtils.cpp jpegUtils.h)

include_directories(${INCLUDE_DIR} )

link_directories(${LIB_DIR})

add_definitions(-DJPEG_UTILS_EXPORTS)

add_library(jpeg_utils SHARED ${SOURCE_FILES} ${COMMON_FILES})

target_link_libraries(jpeg_utils pthread v4l2 EGL GLESv2 X11 nvbuf_utils nvjpeg nvosd drm)



