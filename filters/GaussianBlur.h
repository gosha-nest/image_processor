#pragma once
#include "Filter.h"

class GaussianBlur : public Filter {
public:
    void Apply(Image& image) override;
    void Apply(float sigma, Image& image);
};
