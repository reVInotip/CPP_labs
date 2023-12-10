#include "field.h"
#include <vector>

using std::vector;

void Field::CalcBitsPosition(long long (&bits)[9], long long j) const {
    const long long size = width_ * height_;
    bits[0] = (((width_ + ((j - 1) % width_)) % width_) + (j / width_) * width_);
    bits[1] = j;
    bits[2] = (((j + 1) % width_) + (j / width_) * width_);
    bits[3] = ((size + ((j - width_ - 1) % size)) % size);
    bits[4] = ((size + ((j - width_) % size)) % size);
    bits[5] = ((size + ((j - width_ + 1) % size)) % size);
    bits[6] = ((j + width_ - 1) % size);
    bits[7] = ((j + width_) % size);
    bits[8] = ((j + width_ + 1) % size);
}

Field::Field() {
    width_ = 60;
    height_ = 40;
    index_ = 0;

    field_[0].resize(300);
    field_[1].resize(300);

    for (int i = 20; i < 300; i += 40) {
        field_[0][i] = 0b00011111;
    }
}

Field::Field(const vector<char>& field, const long long width, const long long height) {
    width_ = width;
    height_ = height;
    index_ = 0;
    field_[0] = field;
    field_[1].resize(field.size());
}

long long Field::GetWidth() const {
    return width_;
}

long long Field::GetHeight() const {
    return height_;
}

vector<char> Field::GetField() const {
    return field_[index_];
}

bool Field::IsLife(long long x, long long y) const {
    const long long bitNumber = y * width_ + x;
    return field_[index_][bitNumber / 8] & (1 << (7 - (bitNumber % 8)));
}

void Field::SetField(const int countIterations, unordered_set<char>& birth, unordered_set<char>& survival) {
    const long long size = width_ * height_;
    for (int i = 0; i < countIterations; ++i) {
        for (auto& k : field_[(index_ + 1) % 2]) {
            k = 0;
        }

        for (long long j = 0; j < size; ++j) {
            int sumNeighbors = 0;
            long long bits[9];
            CalcBitsPosition(bits, j);

            sumNeighbors = 
                !!(field_[index_][bits[0] / 8] & (1 << (7 - (bits[0] % 8)))) + !!(field_[index_][bits[2] / 8] & (1 << (7 - (bits[2] % 8)))) +
                !!(field_[index_][bits[7] / 8] & (1 << (7 - (bits[7] % 8)))) + !!(field_[index_][bits[4] / 8] & (1 << (7 - (bits[4] % 8)))) + 
                !!(field_[index_][bits[6] / 8] & (1 << (7 - (bits[6] % 8)))) + !!(field_[index_][bits[3] / 8] & (1 << (7 - (bits[3] % 8)))) +
                !!(field_[index_][bits[8] / 8] & (1 << (7 - (bits[8] % 8)))) + !!(field_[index_][bits[5] / 8] & (1 << (7 - (bits[5] % 8))));

            int isSurvive = 0, isLive = 0;
            if (field_[index_][bits[1] / 8] & (1 << (7 - (bits[1] % 8)))) {
                isSurvive = survival.count(sumNeighbors);
            } else {
                isLive = birth.count(sumNeighbors);
            }

            if (isLive || isSurvive) {
                field_[(index_ + 1) % 2][bits[1] / 8] |= (1 << (7 - (bits[1] % 8)));
            }
        }
        index_ = (index_ + 1) % 2;
    }
}

char& Field::operator [] (int i) {
    return field_[index_][i];
}

const char& Field::operator [] (int i) const {
    return field_[index_][i];
}