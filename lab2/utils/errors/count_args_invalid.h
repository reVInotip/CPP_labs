#pragma once

#include <exception>
#include <string>

using std::string;

class InvalidCountArgsException : public std::exception {
    private:
        const string countAgrumentsInvalid_ = "Count arguments is invalid\n";
    public:
        InvalidCountArgsException() = default;
        ~InvalidCountArgsException() = default;
        const char* what() const noexcept override;
};