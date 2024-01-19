#include "sound_processor_exception.h"

using namespace soundProcessorExceprions;

InvalidFirstCommandException::InvalidFirstCommandException(const string& command) {
    message_ = "![ERR] First command might be -c or -h. Command " + command + " is invalid!";
}

const char* InvalidFirstCommandException::what() const noexcept {
    return message_.data();
}

int InvalidFirstCommandException::code() const noexcept {
    return code_;
}

int InvalidSecondCommandException::code() const noexcept {
    return code_;
}

int InvalidConverterNameException::code() const noexcept {
    return code_;
}

int TooFewArgumentsException::code() const noexcept {
    return code_;
}

InvalidSecondCommandException::InvalidSecondCommandException(const string& command) {
    message_ = "![ERR] First command might be -s. Command " + command + " is invalid!";
}

const char* InvalidSecondCommandException::what() const noexcept {
    return message_.data();
}

InvalidConverterNameException::InvalidConverterNameException(const string& converterName) {
    message_ = "![ERR] Converter name might be 'volume', 'mix', 'mute' or different name which you add to Sound Processor with your converter.\
 Name " + converterName + " is invalid!";
}

const char* InvalidConverterNameException::what() const noexcept {
    return message_.data();
}

const char* TooFewArgumentsException::what() const noexcept {
    return "![ERR] Too few arguments!";
}