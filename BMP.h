#pragma once

#include <string>
#include "Image.h"

Image LoadBMP(const std::string& filename);

void SaveBMP(const Image& image, const std::string& filename);
