cmake_minimum_required(VERSION 3.5)
project(jpeg_tester)


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

#file(GLOB_RECURSE COMMON_FILES "${ROOT_PATH}/git/multimedia/common/classes/*.cpp")

set(SOURCE_FILES
        jpeg_tester_main.cpp jpeg_tester_main.h )

include_directories(${INCLUDE_DIR} ${ROOT_PATH}/git/multimedia/jpeg_utils)
link_directories(${LIB_DIR})

add_executable(jpeg_tester ${SOURCE_FILES} ${COMMON_FILES} )

#target_link_libraries(jpeg_tester ${ROOT_PATH}/git/multimedia/jpeg_utils/cmake-build-debug/libjpeg_utils.so pthread v4l2 EGL GLESv2 X11 nvbuf_utils nvjpeg nvosd drm)

target_link_libraries(jpeg_tester ${ROOT_PATH}/git/multimedia/jpeg_utils/cmake-build-debug/libjpeg_utils.so)