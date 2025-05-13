#include "Grayscale.h"

void Grayscale::Apply(Image& image) {
    const float red = 0.299;
    const float green = 0.587;
    const float blue = 0.114;
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            Color color = image.GetPixel(x, y);
            float mutual_color = red * color.r + green * color.g + blue * color.b;
            image.SetPixel(x, y, Color(mutual_color, mutual_color, mutual_color));
        }
    }
}