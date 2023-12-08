#include "field.h"
#include <vector>

using std::vector;

// попробовать получше сделать

void Field::CalcBitsPosition(long long (&bits)[9], long long j) const {
    const long long size = width_ * height_;
    bits[0] = 7 - ((((width_ + ((j - 1) % width_)) % width_) + (j / width_) * width_) % 8);
    bits[1] = 7 - (j % 8);
    bits[2] = 7 - ((((j + 1) % width_) + (j / width_) * width_) % 8);
    bits[3] = 7 - (((size + ((j - width_ - 1) % size)) % size) % 8);
    bits[4] = 7 - (((size + ((j - width_) % size)) % size) % 8);
    bits[5] = 7 - (((size + ((j - width_ + 1) % size)) % size) % 8);
    bits[6] = 7 - (((j + width_ - 1) % size) % 8);
    bits[7] = 7 - (((j + width_) % size) % 8);
    bits[8] = 7 - (((j + width_ + 1) % size) % 8);
}

void Field::CalcBytesPosition(long long (&pos)[9], long long j) const {
    const long long size = width_ * height_;
    pos[0] = (((width_ + ((j - 1) % width_)) % width_) + (j / width_) * width_) / 8;
    pos[1] = j / 8;
    pos[2] = (((j + 1) % width_) + (j / width_) * width_) / 8;
    pos[3] = ((size + ((j - width_ - 1) % size)) % size) / 8;
    pos[4] = ((size + ((j - width_) % size)) % size) / 8;
    pos[5] = ((size + ((j - width_ + 1) % size)) % size) / 8;
    pos[6] = ((j + width_ - 1) % size) / 8;
    pos[7] = ((j + width_) % size) / 8;
    pos[8] = ((j + width_ + 1) % size) / 8;
}

Field::Field() {
    width_ = 60;
    height_ = 40;

    field_.resize(300);

    for (int i = 20; i < 300; i += 40) {
        field_[i] = 0b00011111;
    }
}

Field::Field(const vector<char>& field, const long long width, const long long height) {
    width_ = width;
    height_ = height;
    field_ = field;
}

long long Field::GetWidth() const {
    return width_;
}

long long Field::GetHeight() const {
    return height_;
}

vector<char> Field::GetField() const {
    return field_;
}

bool Field::IsLife(long long x, long long y) const {
    const long long bitNumber = y * width_ + x;
    return field_[bitNumber / 8] & (1 << (7 - (bitNumber % 8)));
}

void Field::SetField(const int countIterations, unordered_set<char>& birth, unordered_set<char>& survival) {
    const long long size = width_ * height_;
    for (int i = 0; i < countIterations; ++i) {
        vector<char> newFiled;
        newFiled.resize((size / 8) + (size % 8 != 0));
        for (long long j = 0; j < size; ++j) {
            int sumNeighbors = 0;
            long long bits[9];
            CalcBitsPosition(bits, j);
            long long pos[9];
            CalcBytesPosition(pos, j);

            sumNeighbors = 
                !!(field_[pos[0]] & (1 << bits[0])) + !!(field_[pos[2]] & (1 << bits[2])) +
                !!(field_[pos[7]] & (1 << bits[7])) + !!(field_[pos[4]] & (1 << bits[4])) + 
                !!(field_[pos[6]] & (1 << bits[6])) + !!(field_[pos[3]] & (1 << bits[3])) +
                !!(field_[pos[8]] & (1 << bits[8])) + !!(field_[pos[5]] & (1 << bits[5]));

            int isSurvive = 0, isLive = 0;
            if (field_[pos[1]] & (1 << bits[1])) {
                isSurvive = survival.count(sumNeighbors);
            } else {
                isLive = birth.count(sumNeighbors);
            }

            if (isLive || isSurvive) {
                newFiled[pos[1]] |= (1 << bits[1]);
            }
        }
        field_ = newFiled;
    }
}

char& Field::operator [] (int i) {
    return field_[i];
}

const char& Field::operator [] (int i) const {
    return field_[i];
}