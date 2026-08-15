#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string Utils::readFileToString(const char *fileName) {
    std::ifstream inputFile(fileName);

    if (!inputFile.is_open()) {
        throw std::runtime_error("Invalid file");
    }

    std::ostringstream buffer;
    buffer << inputFile.rdbuf();
    return buffer.str();
}
