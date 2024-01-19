#include "../wav.h"
#include "../exceptions/file_not_open.h"

void wav::WavWriter::WriteWav(const string& fileName, const WavHeader& header, const vector<int16_t>& data) {
    if (outputStream_.is_open()) {
        outputStream_.close();
    }
    outputStream_.open(fileName, std::ios::out | std::ios::binary);
    
    if (outputStream_.is_open()) {
        outputStream_.write(reinterpret_cast<const char*>(&header), sizeof(WavHeader));
        outputStream_.write(reinterpret_cast<const char*>(data.data()), data.size() * header.blockAlign);
    } else {
        throw WavFileNotOpenException("write");
    }
}