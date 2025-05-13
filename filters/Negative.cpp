#include "Negative.h"

void Negative::Apply(Image& image) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            Color color = image.GetPixel(x, y);
            image.SetPixel(x, y, Color(1 - color.r, 1 - color.g, 1 - color.b));
        }
    }
}