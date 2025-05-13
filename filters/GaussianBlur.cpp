#include "GaussianBlur.h"
#include <math.h>
#include <cmath>

void GaussianBlur::Apply(Image& image) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            image.SetPixel(x, y, Color(0, 0, 0));
        }
    }
}

void GaussianBlur::Apply(float sigma, Image& image) {
    int width = image.width;
    int height = image.height;
    int radius = static_cast<int>(std::ceil(3 * sigma));
    int kernel_size = 2 * radius + 1;
    std::vector<float> kernel(kernel_size, 0.0f);
    float fraction = static_cast<float>((1 / (std::sqrt(2 * M_PI) * sigma)));
    float sum = 0;
    for (int i = -radius; i <= radius; ++i) {
        float x = static_cast<float>(i);
        float value = fraction * static_cast<float>(std::exp(-(x * x) / (2 * sigma * sigma)));
        kernel[i + radius] = value;
        sum += value;
    }
    for (float& v : kernel) {
        v /= sum;
    }
    Image tmp_image(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            float red = 0;
            float green = 0;
            float blue = 0;
            for (int k = -radius; k <= radius; ++k) {
                int new_x = x + k;
                Color color = image.GetPixel(new_x, y);
                float weight = kernel[k + radius];
                red += color.r * weight;
                green += color.g * weight;
                blue += color.b * weight;
            }
            tmp_image.SetPixel(x, y, Color(red, green, blue));
        }
    }
    Image result(width, height);
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            float red = 0;
            float green = 0;
            float blue = 0;
            for (int k = -radius; k <= radius; ++k) {
                int new_y = y + k;
                Color color = tmp_image.GetPixel(x, new_y);
                float weight = kernel[k + radius];
                red += color.r * weight;
                green += color.g * weight;
                blue += color.b * weight;
            }
            result.SetPixel(x, y, Color(red, green, blue));
        }
    }
    image.pixels = std::move(result.pixels);
}
