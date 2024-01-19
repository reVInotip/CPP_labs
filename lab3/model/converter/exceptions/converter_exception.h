#pragma once

#include <exception>
#include <string>

using std::string;

namespace converterException {
    class ConverterException : public std::exception {
        public:
            ConverterException() = default;
            virtual ~ConverterException() = default;
            virtual const char* what() const noexcept = 0;
            virtual int code() const noexcept = 0;
    };

    class ConverterFactoryException : public ConverterException {
        public:
            ConverterFactoryException() = default;
            virtual ~ConverterFactoryException() = default;
            virtual const char* what() const noexcept = 0;
            virtual int code() const noexcept = 0;
    };

    class MixConverterException : public ConverterException {
        public:
            MixConverterException() = default;
            virtual ~MixConverterException() = default;
            virtual const char* what() const noexcept = 0;
            virtual int code() const noexcept = 0;
    };

    class MuteConverterException : public ConverterException {
        public:
            MuteConverterException() = default;
            virtual ~MuteConverterException() = default;
            virtual const char* what() const noexcept = 0;
            virtual int code() const noexcept = 0;
    };

    class VolumeConverterException : public ConverterException {
        public:
            VolumeConverterException() = default;
            virtual ~VolumeConverterException() = default;
            virtual const char* what() const noexcept = 0;
            virtual int code() const noexcept = 0;
    };

    class ConverterCreateException final : public ConverterFactoryException {
        private:
            const int code_ = 20001;
            string message_;
        public:
            ConverterCreateException(const string& converterName);
            ~ConverterCreateException() = default;
            const char* what() const noexcept override;
            int code() const noexcept override;
    };

    class InvalidStreamForMixConverterException final : public MixConverterException {
        private:
            const int code_ = 21000;
            string message_;
        public:
            InvalidStreamForMixConverterException(const string& argument);
            ~InvalidStreamForMixConverterException() = default;
            const char* what() const noexcept override;
            int code() const noexcept override;
    };

    class InvalidCountTimesException final : public MixConverterException, public MuteConverterException {
        private:
            const int code_ = 21100;
            string message_;
        public:
            InvalidCountTimesException(const unsigned count);
            ~InvalidCountTimesException() = default;
            const char* what() const noexcept override;
            int code() const noexcept override;
    };

    class TimeStartBiggerThenTimeEndException final : public MixConverterException, public MuteConverterException, public VolumeConverterException {
        private:
            const int code_ = 211101;
        public:
            TimeStartBiggerThenTimeEndException() = default;
            ~TimeStartBiggerThenTimeEndException() = default;
            const char* what() const noexcept override;
            int code() const noexcept override;
    };

    class InvalidStreamNumberException final : public MixConverterException, public MuteConverterException, public VolumeConverterException {
        private:
            const int code_ = 211102;
            string message_;
        public:
            InvalidStreamNumberException(const unsigned number, const unsigned countStreams);
            ~InvalidStreamNumberException() = default;
            const char* what() const noexcept override;
            int code() const noexcept override;
    };

    class InvalidCountStreamsException final : public MuteConverterException, public VolumeConverterException {
        private:
            const int code_ = 20110;
        public:
            InvalidCountStreamsException() = default;
            ~InvalidCountStreamsException() = default;
            const char* what() const noexcept override;
            int code() const noexcept override;
    };

    class InvalidCountMultipliersException final : public VolumeConverterException {
        private:
            const int code_ = 200101;
        public:
            InvalidCountMultipliersException() = default;
            ~InvalidCountMultipliersException() = default;
            const char* what() const noexcept override;
            int code() const noexcept override;
    };

    class NoMultipliersException final : public VolumeConverterException {
        private:
            const int code_ = 200102;
        public:
            NoMultipliersException() = default;
            ~NoMultipliersException() = default;
            const char* what() const noexcept override;
            int code() const noexcept override;
    };
}