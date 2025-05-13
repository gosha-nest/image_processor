#include "BMP.h"
#include "Controller.h"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char** argv) {
    try {
        Parser parser(argc, argv);
        Image image = LoadBMP(parser.input_file);
        std::cout << "passed LoadBMP" << std::endl;
        Controller controller;
        controller.ApplyFilters(parser.filters, image);
        SaveBMP(image, parser.output_file);
        std::cout << "image saved in " << parser.output_file;
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string(e.what()));
    }
    return 0;
}
