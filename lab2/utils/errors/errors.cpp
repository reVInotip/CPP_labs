#include "file_not_found.h"
#include "invalid_argument.h"
#include "count_args_invalid.h"

FileNotFoundException::FileNotFoundException(const string& fileName) {
    fileNotFound_ = "File " + fileName + " not found\n";
}

InvalidArgException::InvalidArgException(const string& arg) {
    agrumentIsInvalid_ = "Argument " + arg + " is invalid\n";
}

const char* FileNotFoundException::what() const noexcept {
    return fileNotFound_.data();
}

const char* InvalidArgException::what() const noexcept {
    return agrumentIsInvalid_.data();
}

const char* InvalidCountArgsException::what() const noexcept {
    return countAgrumentsInvalid_.data();
}