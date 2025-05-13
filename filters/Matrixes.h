#pragma once
#include "Filter.h"

class Matrix : public Filter {
public:
    void ApplyMatrix(int x, int y, float a1, float b1, float c1, float a2, float b2, float c2, float a3, float b3,
                     float c3, Image& image, Image& tmp_image) {
        float r =
            std::min(1.0f, std::max(0.0f, a1 * image.GetPixel(x - 1, y - 1).r + b1 * image.GetPixel(x, y - 1).r +
                                              c1 * image.GetPixel(x + 1, y - 1).r + a2 * image.GetPixel(x - 1, y).r +
                                              b2 * image.GetPixel(x, y).r + c2 * image.GetPixel(x + 1, y).r +
                                              a3 * image.GetPixel(x - 1, y + 1).r + b3 * image.GetPixel(x, y + 1).r +
                                              c3 * image.GetPixel(x + 1, y + 1).r));
        float g =
            std::min(1.0f, std::max(0.0f, a1 * image.GetPixel(x - 1, y - 1).g + b1 * image.GetPixel(x, y - 1).g +
                                              c1 * image.GetPixel(x + 1, y - 1).g + a2 * image.GetPixel(x - 1, y).g +
                                              b2 * image.GetPixel(x, y).g + c2 * image.GetPixel(x + 1, y).g +
                                              a3 * image.GetPixel(x - 1, y + 1).g + b3 * image.GetPixel(x, y + 1).g +
                                              c3 * image.GetPixel(x + 1, y + 1).g));
        float b =
            std::min(1.0f, std::max(0.0f, a1 * image.GetPixel(x - 1, y - 1).b + b1 * image.GetPixel(x, y - 1).b +
                                              c1 * image.GetPixel(x + 1, y - 1).b + a2 * image.GetPixel(x - 1, y).b +
                                              b2 * image.GetPixel(x, y).b + c2 * image.GetPixel(x + 1, y).b +
                                              a3 * image.GetPixel(x - 1, y + 1).b + b3 * image.GetPixel(x, y + 1).b +
                                              c3 * image.GetPixel(x + 1, y + 1).b));
        tmp_image.SetPixel(x, y, Color(r, g, b));
    }
    void Apply(Image& image) override = 0;
};
