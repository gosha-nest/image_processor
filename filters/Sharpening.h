#pragma once
#include "Matrixes.h"

class Sharpening : public Matrix {
public:
    void Apply(Image& image) override;
};
