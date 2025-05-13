#pragma once
#include "Image.h"
#include "Parser.h"

class Controller {
public:
    void ApplyFilters(const std::vector<FilterParameters>& filters, Image& image);
};
