#include "Image.h"
#include <vector>

Image::Image(int width, int height) : width(width), height(height), pixels(std::vector<Color>(width * height)) {
}

Color Image::GetPixel(int x, int y) const {
    if (x < 0) {
        x = 0;
    }
    if (x >= width) {
        x = width - 1;
    }
    if (y < 0) {
        y = 0;
    }
    if (y >= height) {
        y = height - 1;
    }
    return pixels[y * width + x];
}

void Image::SetPixel(int x, int y, const Color& color) {
    if (x < 0) {
        x = 0;
    }
    if (x >= width) {
        x = width - 1;
    }
    if (y < 0) {
        y = 0;
    }
    if (y >= height) {
        y = height - 1;
    }
    pixels[y * width + x] = color;
}
