#pragma once

#include "i_game.h"
#include "../../view/screen/i_screen.h"
#include "../field/field.h"
#include "../../utils/game_params.h"
#include <cstddef>
#include <string>
#include <unordered_set>
#include <vector>

using std::vector, std::string, std::unordered_set;
using ScreenPtr = std::shared_ptr<I_Screen>;

class Game final : public I_Game, public Field {
    private:
        ScreenPtr screen_;
        string name_;
        struct Rules {
            unordered_set<char> birth_;
            unordered_set<char> survival_;
        } rules_;

        void SetRules();
        void SetRules(unordered_set<char>& birth, unordered_set<char>& survival);
    public:
        Game();
        Game(const GameParams& gameParams);
        ~Game() = default;
        string GetName() const override;
        long long GetWidth() const override;
        long long GetHeight() const override;
        vector<char> GetField() const override;
        unordered_set<char> GetBirth() const override;
        unordered_set<char> GetSurvival() const override;
        void SetField(const int countIterations) override;
        void PrintField() const override;
        void Dump(const string& fileName) override;
        bool IsLife(long long x, long long y) const override;
        char& operator [] (int i) override;
        const char& operator [] (int i) const override;
};