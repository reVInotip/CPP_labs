#include "../wav.h"
#include "file_incorrect.h"
#include "file_not_open.h"

wav::WavFileNotOpenException::WavFileNotOpenException(const string& openingMode) {
    exceptionString_ = "[[ERROR!]]\nFile not open in " + openingMode + " mode.\n";
}

const char* wav::WavFileNotOpenException::what() const noexcept {
    return exceptionString_.data();
}

wav::WavFileNotValidException::WavFileNotValidException(const string& invalidString) {
    exceptionString_ = "[[ERROR!]]\nInteral string " + invalidString + " does not exists in .wav file\n\
or value in this string is incorrect.\n";
}

const char* wav::WavFileNotValidException::what() const noexcept {
    return exceptionString_.data();
}

int wav::WavFileNotOpenException::code() const noexcept {
    return code_;
}

int wav::WavFileNotValidException::code() const noexcept {
    return code_;
}