#include "Parser.h"
#include <stdexcept>

Parser::Parser(int argc, char** argv) {
    if (argc <= 3) {
        throw std::runtime_error("not enough arguments given");
    }
    input_file = argv[1];
    output_file = argv[2];
    int i = 3;
    while (i < argc) {
        std::string name = argv[i];
        FilterParameters filter;
        filter.name = name;
        ++i;
        while (i < argc && argv[i][0] != '-') {
            filter.args.push_back(argv[i]);
            ++i;
        }
        filters.push_back(filter);
    }
}