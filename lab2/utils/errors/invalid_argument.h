#pragma once

#include <exception>
#include <string>

using std::string;

class InvalidArgException : public std::exception {
    private:
        string agrumentIsInvalid_;
    public:
        InvalidArgException(const string& arg);
        ~InvalidArgException() = default;
        const char* what() const noexcept override;
};