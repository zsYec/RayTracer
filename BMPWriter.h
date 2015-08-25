//
// Created by for Ye in Debugging : on 15/8/25.
//

#ifndef RAY_BMPWRITER_H
#define RAY_BMPWRITER_H

#include <fstream>
#include <iostream>
#include "Color.h"

class BMPWriter {
public:
    struct bmpheader {
        uint32_t filesz;
        uint16_t creator1;
        uint16_t creator2;
        uint32_t bmp_offset;
    };

    struct bmpinfo {
        uint32_t header_sz;
        int32_t width;
        int32_t height;
        uint16_t nplanes;
        uint16_t bitspp;
        uint32_t compress_type;
        uint32_t bmp_bytesz;
        int32_t hres;
        int32_t vres;
        uint32_t ncolors;
        uint32_t nimpcolors;
    };

    struct bgracolor {
        unsigned char blueChannel, greenChannel, redChannel, alphaChannel;
    };


    static void write_header(std::ofstream& f, int width, int height) {
        bmpheader header;
        bmpinfo info;
        int size = width * height * 4;
        memset(&header, 0, sizeof(header));
        memset(&info, 0, sizeof(info));
        header.filesz = size + 54;
        header.bmp_offset = 54;
        info.header_sz = 40;
        info.width = width;
        info.height = height;
        info.nplanes = 1;
        info.bitspp = 32;
        info.bmp_bytesz = size;
        f.write("BM", 2);
        f.write((char*)&header, sizeof(header));
        f.write((char*)&info, sizeof(info));
    }

    static void conv_color(bgracolor* out, const Color* in, int size) {
        for (int i = 0; i < size; ++i) {
            Color c = in[i].clamp();
            out[i].redChannel = c.r * 255;
            out[i].greenChannel = c.g * 255;
            out[i].blueChannel = c.b * 255;
            out[i].alphaChannel = 255;
        }
    }

    static void write_color(std::ofstream& f, bgracolor* bgra, int width, int height) {
        f.write((char*)bgra, width * height * sizeof(*bgra));
    }
    static void write(const std::string& filename, const Color* data, int width, int height) {
        std::ofstream f(filename.c_str(), std::ios::binary);
        if (!f) return;

        write_header(f, width, height);

        bgracolor* bgra = new bgracolor[width * height];
        conv_color(bgra, data, width * height);
        write_color(f, bgra, width, height);

        delete[] bgra;
    }
};

#endif //RAY_BMPWRITER_H
