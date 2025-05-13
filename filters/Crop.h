#pragma once
#include "Filter.h"

class Crop : public Filter {
public:
    void Apply(Image& image) override;
    void Apply(int width, int height, Image& image);
};
