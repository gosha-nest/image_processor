#include "BMP.h"
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>

static_assert(true);  // это чтобы clang-tidy не ругался на то, что снизу (баг)
#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BMPInfoHeader {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

Image LoadBMP(const std::string& filename) {
    BMPFileHeader fileheader;
    BMPInfoHeader infoheader;
    try {
        std::ifstream input_file(filename, std::ios::in | std::ios::binary);
        if (!input_file.is_open()) {
            throw std::runtime_error(filename + "could not be opened");
        }
        input_file.read(reinterpret_cast<char*>(&fileheader), sizeof(fileheader));
        // проверка на BM
        const int fileheader_bftype = 0x4D42;
        if (fileheader.bfType != fileheader_bftype) {
            throw std::runtime_error(filename + "not BMP");
        }
        input_file.read(reinterpret_cast<char*>(&infoheader), sizeof(infoheader));
        const int infoheader_bitcnt = 24;
        if (infoheader.biBitCount != infoheader_bitcnt) {
            throw std::runtime_error(filename + "not 24-bit");
        }
        if (infoheader.biCompression != 0) {
            throw std::runtime_error(filename + "compressed :(");
        }
        int width = infoheader.biWidth;
        int height = infoheader.biHeight;
        Image image(width, height);
        int padding = (4 - (width * 3) % 4) % 4;
        const float weight = 255.0f;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                unsigned char colors[3];
                input_file.read(reinterpret_cast<char*>(colors), 3);
                float r = static_cast<float>(colors[2]) / weight;
                float g = static_cast<float>(colors[1]) / weight;
                float b = static_cast<float>(colors[0]) / weight;
                image.SetPixel(x, y, Color(r, g, b));
            }
            input_file.ignore(padding);
        }
        input_file.close();
        return image;
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string(e.what()) + "<<<< went bad here");
    }
}

void SaveBMP(const Image& image, const std::string& filename) {
    BMPFileHeader fileheader;
    BMPInfoHeader infoheader;
    try {
        std::ofstream output_file(filename, std::ios::out | std::ios::binary);
        if (!output_file.is_open()) {
            throw std::runtime_error(filename + "could not be opened");
        }
        int width = image.width;
        int height = image.height;
        int padding = (4 - (width * 3) % 4) % 4;
        const int fileheader_bftype = 0x4D42;
        fileheader.bfType = fileheader_bftype;
        fileheader.bfSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + width * height * 3 + padding * height;
        fileheader.bfReserved1 = 0;
        fileheader.bfReserved2 = 0;
        fileheader.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
        const int infoheader_bitcnt = 24;
        infoheader.biSize = sizeof(BMPInfoHeader);
        infoheader.biWidth = width;
        infoheader.biHeight = height;
        infoheader.biPlanes = 1;
        infoheader.biBitCount = infoheader_bitcnt;
        infoheader.biCompression = 0;
        infoheader.biSizeImage = width * height * 3 + padding * height;
        infoheader.biXPelsPerMeter = 0;
        infoheader.biYPelsPerMeter = 0;
        infoheader.biClrUsed = 0;
        infoheader.biClrImportant = 0;
        output_file.write(reinterpret_cast<char*>(&fileheader), sizeof(fileheader));
        output_file.write(reinterpret_cast<char*>(&infoheader), sizeof(infoheader));
        unsigned char bmppad[3] = {0, 0, 0};
        const float weight = 255.0f;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Color color = image.GetPixel(x, y);
                unsigned char r = static_cast<unsigned char>(color.r * weight);
                unsigned char g = static_cast<unsigned char>(color.g * weight);
                unsigned char b = static_cast<unsigned char>(color.b * weight);
                unsigned char colors[] = {b, g, r};
                output_file.write(reinterpret_cast<char*>(colors), 3);
            }
            output_file.write(reinterpret_cast<char*>(bmppad), padding);
        }
        output_file.close();
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string(e.what()) + "<<<< went bad here");
    }
}
