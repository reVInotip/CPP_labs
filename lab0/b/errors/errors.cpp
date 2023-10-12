#include "errors.h"
#include <string>

using std::string;

WrongFileException::WrongFileException(string fileName) {
    execptionText = execptionText + fileName;
}

WrongFileException::WrongFileException() {
    execptionText = "Something went wrong!";
}