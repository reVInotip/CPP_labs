#pragma once

#include <cstdint>
#include <exception>
#include <fstream>
#include <utility>
#include <vector>

using std::ifstream, std::vector, std::string, std::pair, std::ofstream;

namespace wav {
    static constexpr uint32_t RIFF = 0x46464952; // "RIFF"
    static constexpr uint32_t FORMAT = 0x45564157; // "WAVE"
    static constexpr uint32_t SUBCHUNK_ONE_ID = 0x20746D66; // "fmt "
    static constexpr uint32_t SUBCHUNK_ONE_SIZE = 16; // for PCM
    static constexpr uint16_t AUDIO_FORMAT = 1; // for PCM
    static constexpr uint32_t SAMPLE_RATE = 44100;
    static constexpr uint16_t BITS_PER_SAMPLE = 16;
    static constexpr uint32_t SUBCHUNK_TWO_ID = 0x61746164;

    struct chunk {
        int32_t id;
        int32_t size;
    };

    struct WavHeader {
        // WAV-формат начинается с RIFF-заголовка:

        // Содержит символы "RIFF" в ASCII кодировке
        chunk mainChunk;

        // Содержит символы "WAVE"
        uint32_t format;

        // Формат "WAVE" состоит из двух подцепочек: "fmt " и "data":
        // Подцепочка "fmt " описывает формат звуковых данных:
        
        // Содержит символы "fmt "
        chunk firstSubchunk;

        // Для PCM = 1 (то есть, Линейное квантование).
        // Значения, отличающиеся от 1, обозначают некоторый формат сжатия.
        uint16_t audioFormat;

        // Количество каналов. Моно = 1, Стерео = 2 и т.д.
        uint16_t numChannels;

        // Частота дискретизации. 8000 Гц, 44100 Гц и т.д.
        uint16_t sampleRate;

        // sampleRate * numChannels * bitsPerSample/8
        uint32_t byteRate;

        // numChannels * bitsPerSample/8
        // Количество байт для одного сэмпла, включая все каналы.
        uint16_t blockAlign;

        // Так называемая "глубиная" или точность звучания. 8 бит, 16 бит и т.д.
        uint16_t bitsPerSample;

        // Подцепочка "data" содержит аудио-данные и их размер.

        // Содержит символы "data"
        chunk secondSubchunk;

        // Далее следуют непосредственно Wav данные.
    };

    class WavFileNotValidException;

    class WavFileNotOpenException;

    class WavReader {
        private:
            ifstream inputStream_;
            WavHeader header_;
            vector<int16_t> data_;

            const pair<bool, string> HeaderIsValid() const noexcept;
            void FindData();
        public:
            WavReader() = default;
            ~WavReader() = default;
            void ReadWav(const string& fileName);
            WavHeader GetHeader() const noexcept;
            vector<int16_t> GetData() const noexcept;
    };

    class WavWriter {
        private:
            ofstream outputStream_;

        public:
            WavWriter() = default;
            ~WavWriter() = default;
            void WriteWav(const string& fileName, const WavHeader& header, const vector<int16_t>& data);
    };
}