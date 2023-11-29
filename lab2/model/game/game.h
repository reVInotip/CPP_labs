#pragma once

#include "i_game.h"
#include <cstddef>
#include <string>
#include <unordered_set>
#include <vector>

using std::vector, std::string, std::unordered_set;

class Game final : public I_Game {
    private:
        vector<char> field_;
        size_t width_;
        size_t height_;
        string name_;
        struct Rules {
            unordered_set<char> birth_;
            unordered_set<char> survival_;
        } rules_;
        void SetRules();
        void SetRules(unordered_set<char>& birth, unordered_set<char>& survival);
    public:
        Game();
        Game(const vector<char>& field, const size_t width, const size_t height);
        ~Game() = default;
        string GetName() const override;
        size_t GetWidth() const override;
        size_t GetHeight() const override;
        void GetField() const override;
        void SetField(const int countIterations) override;
        void Dump(string& fileName) override;
        void Exit() override;
        char& operator [] (int i) override;
        const char& operator [] (int i) const override;
};