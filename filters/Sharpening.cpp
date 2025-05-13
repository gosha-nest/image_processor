#include "Sharpening.h"

void Sharpening::Apply(Image& image) {
    Image tmp_image(image.width, image.height);
    const float five = 5;
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            ApplyMatrix(x, y, 0, -1, 0, -1, five, -1, 0, -1, 0, image, tmp_image);
        }
    }
    image.pixels = std::move(tmp_image.pixels);
}