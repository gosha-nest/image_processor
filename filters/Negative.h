#pragma once
#include "Filter.h"

class Negative : public Filter {
public:
    void Apply(Image& image) override;
};
