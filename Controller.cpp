#include "Controller.h"
#include "filters/Crop.h"
#include "filters/EdgeDetection.h"
#include "filters/GaussianBlur.h"
#include "filters/Grayscale.h"
#include "filters/Negative.h"
#include "filters/Sharpening.h"
#include <cstdlib>
#include <stdexcept>
#include <string>

void Controller::ApplyFilters(const std::vector<FilterParameters>& filters, Image& image) {
    for (const FilterParameters& param : filters) {
        const std::string& name = param.name;
        const std::vector<std::string>& args = param.args;
        if (name == "-crop") {
            if (args.size() != 2) {
                throw std::runtime_error("Not enough or too many parametrs for -crop");
            }
            int width = std::stoi(args[0]);
            int height = std::stoi(args[1]);
            Crop crop;
            crop.Apply(width, height, image);
        } else if (name == "-gs") {
            Grayscale gs;
            gs.Apply(image);
        } else if (name == "-neg") {
            Negative neg;
            neg.Apply(image);
        } else if (name == "-sharp") {
            Sharpening sharp;
            sharp.Apply(image);
        } else if (name == "-edge") {
            if (args.size() != 1) {
                throw std::runtime_error("Not enough or too many parametrs for -edge");
            }
            float threshold = std::stof(args[0]);
            Grayscale gs;
            gs.Apply(image);
            EdgeDetection edge;
            edge.Apply(threshold, image);
        } else if (name == "-blur") {
            if (args.size() != 1) {
                throw std::runtime_error("Not enough or too many parametrs for -blur");
            }
            float sigma = std::stof(args[0]);
            GaussianBlur blur;
            blur.Apply(sigma, image);
        } else {
            throw std::runtime_error("Non-existing filter");
        }
    }
}