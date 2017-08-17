//
// Created by ubuntu on 8/17/17.
//

#include "jpeg_tester_main.h"


int main(int argc, char *argv[]) {

    cout << "jpeg_tester started" << endl;

    uint32_t w = 960;
    uint32_t h = 720;
    uint32_t buf_size = w*h*1.5;
    unsigned char in_buf[buf_size];
    unsigned char out_buf[buf_size];
    unsigned long jpeg_size = 0;
    uint32_t requested_pix_fmt = PIX_FMT_YVU420p;

    ifstream* jpeg_file = new ifstream("vis3.jpg");
    if(!jpeg_file->is_open())
    {
        cout << "file vis3.jpg not found!" << endl;
        return -1;
    }
    memset(in_buf, 0, buf_size);
    memset(out_buf, 0, buf_size);

    jpeg_file->seekg(0, fstream::end);
    jpeg_size = jpeg_file->tellg();
    jpeg_file->seekg(0, fstream::beg);

    jpeg_file->read((char*)in_buf, jpeg_size);
    jpeg_file->close();

    void* decoder = createDecoder();
    int res = jpeg_decode(decoder, in_buf, jpeg_size, out_buf, buf_size, requested_pix_fmt, w, h);
    destroyDecoder(decoder);

    if(res < 0)
    {
        cout << "error calling jpeg_decode" << endl;
        return -1;
    }
    ofstream* decodedFile  = new ofstream("vis3_decoded.raw");
    decodedFile->write((char*)out_buf, buf_size);
    decodedFile->close();

    //return 0;

    //encoding
    memset(in_buf, 0, buf_size);
    memset(out_buf, 0, buf_size);

    ifstream* decoded_file = new ifstream("vis3_decoded.raw");
    if(!decoded_file->is_open())
    {
        cout << "file vis3_decoded.raw not found!" << endl;
        return -1;
    }
    void* encoder = createEncoder();

    //decoded_file->seekg(32, std::fstream::beg); //needed only for recorded file with header
    decoded_file->read((char*)in_buf, buf_size);
    decoded_file->close();

    //when buffer comes from augmentor it will have header and format is PIX_FMT_YVU420p instead!!
    res = jpeg_encode(encoder,in_buf, w, h, PIX_FMT_YVU420p, buf_size, out_buf, buf_size, 85, jpeg_size );
    destroyEncoder(encoder);
    if(res < 0)
    {
        cout << "error calling jpeg_encode" << endl;
        return -1;
    }
    ofstream* encoded_file = new ofstream("vis3_encoded.jpg");
    encoded_file->write((char*)out_buf, jpeg_size);
    encoded_file->close();



    //TODO: comp_name of decoder/encoder


}