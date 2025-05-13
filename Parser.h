#pragma once
#include <string>
#include <vector>

struct FilterParameters {
    std::string name;
    std::vector<std::string> args;
};

class Parser {
public:
    std::string input_file;
    std::string output_file;
    std::vector<FilterParameters> filters;
    Parser(int argc, char** argv);
};