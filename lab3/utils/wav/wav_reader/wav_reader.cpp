#include "../wav.h"
#include "../exceptions/file_incorrect.h"
#include "../exceptions/file_not_open.h"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

using std::string, std::pair;
using namespace wav;

const pair<bool, string> wav::WavReader::HeaderIsValid() const noexcept {
    if (header_.mainChunk.id != RIFF) {
        return pair<bool, string>(false, "chunk id");
    } else if (header_.format != FORMAT) {
        return pair<bool, string>(false, "format");
    } else if (header_.firstSubchunk.id != SUBCHUNK_ONE_ID) {
        return pair<bool, string>(false, "subchunk one id");
    } else if (header_.firstSubchunk.size != SUBCHUNK_ONE_SIZE) {
        return pair<bool, string>(false, "subchunk one size");
    } else if (header_.audioFormat != AUDIO_FORMAT) {
        return pair<bool, string>(false, "audio format");
    } else if (header_.sampleRate != SAMPLE_RATE) {
        return pair<bool, string>(false, "sample rate");
    } else if (header_.bitsPerSample != BITS_PER_SAMPLE) {
        return pair<bool, string>(false, "bits per sample");
    }
    return pair<bool, string>(true, "ok");
};

void wav::WavReader::FindData() {
    char* buffer = new char[header_.mainChunk.size]();
    while(header_.secondSubchunk.id != SUBCHUNK_TWO_ID) {
        if (
            !inputStream_.read(buffer, header_.secondSubchunk.size) ||
            !inputStream_.read(reinterpret_cast<char*>(&header_.secondSubchunk), sizeof(chunk))
        ) {
            throw WavFileNotValidException("data");
        }
    }
    delete [] buffer;
}

void wav::WavReader::ReadWav(const string& fileName) {
    if (inputStream_.is_open()) {
        inputStream_.close();
    }
    inputStream_.open(fileName, std::ios::in | std::ios::binary);
    if (inputStream_.is_open()) {
        if (!inputStream_.read(reinterpret_cast<char*>(&header_), sizeof(WavHeader))) {
            throw WavFileNotValidException("chunk id");
        }
        
        pair<bool, string> isValid = HeaderIsValid();
        if (!isValid.first) {
            throw WavFileNotValidException(isValid.second);
        }

        if (header_.secondSubchunk.id != SUBCHUNK_TWO_ID) {
            FindData();
        }
        header_.mainChunk.size = sizeof(WavHeader) - 8 + header_.secondSubchunk.size;
        data_.resize(header_.numChannels * header_.secondSubchunk.size / header_.blockAlign);
        
        if (!inputStream_.read(reinterpret_cast<char*>(data_.data()), data_.size() * header_.blockAlign)) {
            throw WavFileNotValidException("data field");
        }
    } else {
        throw WavFileNotOpenException("read");
    }
}

WavHeader wav::WavReader::GetHeader() const noexcept {
    return header_;
}

vector<int16_t> wav::WavReader::GetData() const noexcept {
    return data_;
}