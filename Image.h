#pragma once
#include "Color.h"
#include <vector>

class Image {
public:
    int width;
    int height;
    std::vector<Color> pixels;
    Image(int width, int height);
    Color GetPixel(int x, int y) const;
    void SetPixel(int x, int y, const Color& color);
};
