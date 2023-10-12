#include <string>
#pragma once

using std::string;

struct WrongFileException {
    string execptionText = "Wrong file: ";
    WrongFileException(string inputFile);
    WrongFileException();
};