#include <NvJpegDecoder.h>
#include "jpegUtils.h"

void* createEncoder()
{
    cout << "createEncoder called" << endl;

    NvJPEGEncoder* jpegenc = NvJPEGEncoder::createJPEGEncoder("jpenenc");

    if(jpegenc != NULL)
    {
        jpegenc->setCropRect(0, 0, 0, 0 );
    }
    return jpegenc;
}

void destroyEncoder(void* encoder)
{
    cout << "destroyEncoder called" << endl;
    NvJPEGEncoder* enc = reinterpret_cast<NvJPEGEncoder*>(encoder);

    if(enc == nullptr)
    {
        cout << "encoder is null" << endl;
        return;
    }
    delete enc;
}


//encode yuv420p raw image to jpeg
int jpeg_encode(void* encoder, unsigned char* src, uint32_t width, uint32_t height, uint32_t pix_fmt, uint32_t src_buf_size,
                unsigned char* dst_buf, unsigned long dst_buf_size, int32_t quality, uint32_t& jpeg_size)
{
    NvJPEGEncoder* enc = reinterpret_cast<NvJPEGEncoder*>(encoder);
    JPG_CHECK_NULL_PTR(enc, "encoder is null", -1);

    uint32_t src_pix_fmt;

    switch (pix_fmt){
        case PIX_FMT_YUV420p:
            src_pix_fmt = V4L2_PIX_FMT_YUV420M;
            break;
        case PIX_FMT_YVU420p:
            src_pix_fmt = V4L2_PIX_FMT_YVU420M;
            break;
        default:
            cout << "unknown pix_fmt " << pix_fmt << endl;
            return -1;
            break;
    }

    //create temp NvBuffer that uses src buffer
    NvBuffer buffer(V4L2_PIX_FMT_YUV420M, width, height, 0, src, src_buf_size, src_pix_fmt);

    buffer.allocateMemory();

    unsigned char** dst_buf_ref = &dst_buf;
    unsigned long dst_buf_size_new = dst_buf_size;

    int ret = enc->encodeFromBuffer(buffer, JCS_YCbCr, dst_buf_ref, dst_buf_size_new, quality);

    if(dst_buf_ref != &dst_buf)
    {
        //encoder allocated new buffer because dst_buf was too small
        cout << "dst_buf size " << " is too small. size required is " << dst_buf_size_new << endl;
        delete[] (*dst_buf_ref);    //delete new buffer (allocated by encoder)
        return -1;
    }

    JPG_CHECK_OK(ret, "Error while encoding from buffer", -1);

    return JPG_OK;
}

void* createDecoder()
{
    cout << "createDecoder called" << endl;

    NvJPEGDecoder* jpegdec = NvJPEGDecoder::createJPEGDecoder("jpegdec");
    return jpegdec;
}

void destroyDecoder(void* decoder)
{
    cout << "destroyEncoder called" << endl;
    NvJPEGDecoder* dec = reinterpret_cast<NvJPEGDecoder*>(decoder);

    if(dec == nullptr)
    {
        cout << "decoder is null" << endl;
        return;
    }
    delete dec;
}

//decode jpeg image to yuv420p raw image
int jpeg_decode(void* decoder, unsigned char* src, uint32_t jpg_size, unsigned char* dst, uint32_t dst_buf_size,
                uint32_t& width, uint32_t& height, uint32_t& pix_fmt)
{
    NvJPEGDecoder* dec = reinterpret_cast<NvJPEGDecoder*>(decoder);
    JPG_CHECK_NULL_PTR(dec, "decoder is null", -1);

    //create temp NvBuffer that uses src buffer
    NvBuffer* nvBuffer = nullptr;
    uint32_t pix_fmt_int;

    int ret = dec->decodeToBuffer(&nvBuffer, src, jpg_size, &pix_fmt_int, &width, &height, dst, dst_buf_size);

    if(nvBuffer != nullptr)
    {
        //needed only during decoding. we use external buffer
        delete nvBuffer;
    }

    JPG_CHECK_OK(ret, "Could not decode image", -1);

    switch (pix_fmt_int){
        case V4L2_PIX_FMT_YUV420M:
            pix_fmt = PIX_FMT_YUV420p;
            break;
        case V4L2_PIX_FMT_YVU420M:
            pix_fmt = PIX_FMT_YVU420p;
            break;
        default:
            cout << "unknown pix_fmt " << pix_fmt_int << endl;
            pix_fmt = 0;
            break;
    }

    cout << "decoded Image Resolution - " << width << " x " << height << " pix_fmt " << pix_fmt << endl;

    return JPG_OK;
}