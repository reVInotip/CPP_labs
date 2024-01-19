#pragma once

#include <exception>
#include <string>

using std::string;

namespace soundProcessorExceprions {
    class SoundProcessorException : public std::exception {
        public:
            SoundProcessorException() = default;
            virtual ~SoundProcessorException() = default;
            virtual const char* what() const noexcept = 0;
            virtual int code() const noexcept = 0;
    };

    class InvalidFirstCommandException final : public SoundProcessorException {
        private:
            const int code_ = 10;
            string message_;    
        public:
            InvalidFirstCommandException(const string& command);
            ~InvalidFirstCommandException() = default;
            const char* what() const noexcept override;
            int code() const noexcept override;
    };

    class InvalidSecondCommandException final : public SoundProcessorException {
        private:
            const int code_ = 11;
            string message_;
        public:
            InvalidSecondCommandException(const string& command);
            ~InvalidSecondCommandException() = default;
            const char* what() const noexcept override;
            int code() const noexcept override;
    };

    class InvalidConverterNameException final : public SoundProcessorException {
        private:
            const int code_ = 12;
            string message_;
        public:
            InvalidConverterNameException(const string& converterName);
            ~InvalidConverterNameException() = default;
            const char* what() const noexcept override;
            int code() const noexcept override;
    };

    class TooFewArgumentsException final : public SoundProcessorException {
        private:
            const int code_ = 13;
        public:
            TooFewArgumentsException() = default;
            ~TooFewArgumentsException() = default;
            const char* what() const noexcept override;
            int code() const noexcept override;
    };
}