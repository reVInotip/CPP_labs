#pragma once

#include "../wav.h"
#include <exception>
#include <string>

using std::string;

class wav::WavFileNotOpenException {
    private:
        string exceptionString_;
        const int code_ = 32;
    public:
        WavFileNotOpenException(const string& openingMode);
        ~WavFileNotOpenException() = default;
        const char* what() const noexcept;
        int code() const noexcept;
};