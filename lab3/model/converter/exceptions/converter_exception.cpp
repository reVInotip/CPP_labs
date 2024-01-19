#include "converter_exception.h"
#include <string>

using namespace converterException;
using std::string;

int ConverterCreateException::code() const noexcept {
    return code_;
}

int InvalidStreamForMixConverterException::code() const noexcept {
    return code_;
}

int InvalidCountTimesException::code() const noexcept {
    return code_;
}

int TimeStartBiggerThenTimeEndException::code() const noexcept {
    return code_;
}

int InvalidStreamNumberException::code() const noexcept {
    return code_;
}

int InvalidCountStreamsException::code() const noexcept {
    return code_;
}

int InvalidCountMultipliersException::code() const noexcept {
    return code_;
}

int NoMultipliersException::code() const noexcept {
    return code_;
}

ConverterCreateException::ConverterCreateException(const string& converterName) {
    message_ = "![ERR] Creator for converter with name " + converterName + " does not exist!\
 Please add this converter to factory before create it!";
}

const char* ConverterCreateException::what() const noexcept {
    return message_.data();
}

InvalidStreamForMixConverterException::InvalidStreamForMixConverterException(const string& argument) {
    message_ = "![ERR] Mix converter has one required argument - stream number, and it must start with $.\
     Argument " + argument + " is invalid!";
}

const char* InvalidStreamForMixConverterException::what() const noexcept {
    return message_.data();
}

InvalidCountTimesException::InvalidCountTimesException(const unsigned argument) {
    message_ = "![ERR] All converters might have time for start convertation and time for end, time for start or none of them.\
 Count time intervals: " + std::to_string(argument) + " is invalid!";
}

const char* InvalidCountTimesException::what() const noexcept {
    return message_.data();
}

const char* TimeStartBiggerThenTimeEndException::what() const noexcept {
    return "![ERR] Time for start convertation can`t be bigger then time for end convertation!";
}

InvalidStreamNumberException::InvalidStreamNumberException(const unsigned number, const unsigned countStreams) {
    message_ = "![ERR] Stream number: " + std::to_string(number) + " is bigger then count streams: " + std::to_string(countStreams);
}

const char* InvalidStreamNumberException::what() const noexcept {
    return message_.data();
}

const char* InvalidCountStreamsException::what() const noexcept {
    return "![ERR] Count streams for volume and mute converters must be 1 or 0!";
}

const char* InvalidCountMultipliersException::what() const noexcept {
    return "![ERR] Multiplier for volume converter must be only one!";
}

const char* NoMultipliersException::what() const noexcept {
    return "![ERR] Required argument for volume converter: multiplier are missing!";
}