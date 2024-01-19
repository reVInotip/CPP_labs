#pragma once

#include "../wav.h"
#include <exception>
#include <string>

using std::string;

class wav::WavFileNotValidException {
    private:
        string exceptionString_;
        const int code_ = 31;
    public:
        WavFileNotValidException(const string& invalidString);
        ~WavFileNotValidException() = default;
        const char* what() const noexcept;
        int code() const noexcept;
};