#pragma once
#include "Filter.h"

class Grayscale : public Filter {
public:
    void Apply(Image& image) override;
};
