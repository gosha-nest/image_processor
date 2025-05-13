#pragma once
#include "Matrixes.h"

class EdgeDetection : public Matrix {
public:
    void Apply(Image& image) override;
    void Apply(float threshold, Image& image);
};
