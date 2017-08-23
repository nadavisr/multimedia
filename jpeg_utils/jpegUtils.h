/*
 * Created by Nadav Israeli
 *
 * part of libjpeg_utils.so *
 * provides Jpeg Encoding / Decoding
 * uses Nvidia's Tegra's hardware acceleration thru libjpeg API
 * may be used with other implementation of libjpeg (windows/linux386) (not checked yet)
 *
 * */

#pragma once


#ifndef JPEG_UTILS_H
#define JPEG_UTILS_H

#include "NvJpegEncoder.h"
#include "NvVideoConverter.h"
#include <fstream>
#include <queue>
#include <pthread.h>
#include <iostream>
#include <stdio.h>

#ifdef _MCS_VER
    #ifdef  JPEG_UTILS_EXPORTS
        #define JPEG_UTILS_API __declspec(dllexport)
    #else
        #define JPEG_UTILS_API __declspec(dllimport)
    #endif
#else   //gcc
    #ifdef JPEG_UTILS_EXPORTS
        #define JPEG_UTILS_API __attribute__((visibility("default")))
    #else
        #define JPEG_UTILS_API
    #endif
#endif

using namespace std;

#define JPG_ERROR -1

#define JPG_OK 0

#define JPG_CHECK_OK(val, msg, ret) if(val < JPG_OK) { \
                                        cout << msg << endl; \
                                        return ret; }

#define JPG_CHECK_OK_DELETE(val, msg, del, ret) if(val < JPG_OK) { \
                                        cout << msg << endl; \
                                        delete del;  \
                                        return ret; }

#define JPG_CHECK_NULL_PTR(val, msg, ret) if(val == nullptr) { \
                                        cout << msg << endl; \
                                        return ret; }

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


enum {
    PIX_FMT_YUV420p = 1, //Y,U,V order also know as I420
    PIX_FMT_YVU420p = 2    //Y,V,U order
};

JPEG_UTILS_API void *createEncoder(int32_t enable_profiling=0);

JPEG_UTILS_API void *createDecoder(int32_t enable_profiling=0);

JPEG_UTILS_API void destroyEncoder(void *encoder);

JPEG_UTILS_API void destroyDecoder(void *decoder);

JPEG_UTILS_API void printEncoderProfiling(void* encoder);

JPEG_UTILS_API void printDecoderProfiling(void* decoder);

//encode yuv420p raw image to jpeg
JPEG_UTILS_API int jpeg_encode(void *encoder, unsigned char *src, uint32_t width, uint32_t height, uint32_t pix_fmt, uint32_t src_buf_size,
                                unsigned char *dst_buf, unsigned long dst_buf_size, int32_t quality, unsigned long &jpeg_size);

//decode jpeg image to yuv420p raw image
JPEG_UTILS_API int jpeg_decode(void *decoder, unsigned char *src, uint32_t jpg_size, unsigned char *dst, uint32_t dst_buf_size, uint32_t dst_buf_pixfmt,
                                uint32_t &width, uint32_t &height);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif  //JPEG_UTILS_H