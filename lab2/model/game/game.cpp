#include "game.h"
#include <cstddef>
#include <iostream>

void Game::SetRules() {
    const auto rg = {2, 3};
    rules_.birth_.insert(3);
    rules_.survival_.insert(rg.begin(), rg.end());
}

void Game::SetRules(unordered_set<char>& birth, unordered_set<char>& survival) {
    rules_.birth_ = birth;
    rules_.survival_ = survival;
}

Game::Game() {
    width_ = 2;
    height_ = 3;
    name_ = "Default Game";

    SetRules();

    field_.reserve(1);

    field_[0] = 0b00101010;
}

Game::Game(const vector<char>& field, const size_t width, const size_t height) {
    width_ = width;
    height_ = height;

    SetRules();

    const size_t size = width * height;
    const size_t fieldSize = (size / 8) + (size % 8 != 0);
    field_ = field;
}

void Game::SetField(const int countIterations) {
    const size_t size = width_ * height_;
    for (int i = 0; i < countIterations; ++i) {
        for (size_t j = 0; j < size; ++j) {
            const char currentPoint = field_[j / 8] & (1 << (size - j - 1));
        }
    }
}