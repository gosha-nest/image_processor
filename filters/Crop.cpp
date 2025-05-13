#include "Crop.h"
#include <algorithm>

void Crop::Apply(Image& image) {
    int new_width = image.width;
    int new_height = image.height;
    Image tmp_pixels(new_width, new_height);
    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            tmp_pixels.SetPixel(x, y, image.GetPixel(x, image.height - new_height + y));
        }
    }
    image.height = new_height;
    image.width = new_width;
    image.pixels = std::move(tmp_pixels.pixels);
}

void Crop::Apply(int width, int height, Image& image) {
    int new_width = std::min(width, image.width);
    int new_height = std::min(height, image.height);
    Image tmp_pixels(new_width, new_height);
    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            tmp_pixels.SetPixel(x, y, image.GetPixel(x, image.height - new_height + y));
        }
    }
    image.height = new_height;
    image.width = new_width;
    image.pixels = std::move(tmp_pixels.pixels);
}
