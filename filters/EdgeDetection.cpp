#include "EdgeDetection.h"

void EdgeDetection::Apply(Image& image) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            image.SetPixel(x, y, Color(0, 0, 0));
        }
    }
}

void EdgeDetection::Apply(float threshold, Image& image) {
    Image tmp_image(image.width, image.height);
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            ApplyMatrix(x, y, 0, -1, 0, -1, 4, -1, 0, -1, 0, image, tmp_image);
        }
    }
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            if (tmp_image.GetPixel(x, y).r > threshold) {
                tmp_image.SetPixel(x, y, Color(1, 1, 1));
            } else {
                tmp_image.SetPixel(x, y, Color(0, 0, 0));
            }
        }
    }
    image.pixels = std::move(tmp_image.pixels);
}
