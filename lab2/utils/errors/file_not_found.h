#pragma once

#include <exception>
#include <string>

using std::string;

class FileNotFoundException : public std::exception {
    private:
        string fileNotFound_;
    public:
        FileNotFoundException(const string& fileName);
        ~FileNotFoundException() = default;
        const char* what() const noexcept override;
};