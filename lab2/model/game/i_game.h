#pragma once

#include "../../utils/game_params.h"
#include <memory>
#include <string>
#include <vector>
#include <unordered_set>

class I_Game;
class I_Screen;

using std::string, std::array, std::vector, std::unordered_set;
using GamePtr = std::shared_ptr<I_Game>;
using ScreenPtr = std::shared_ptr<I_Screen>;

class I_Game {
    protected:
        virtual ~I_Game() = default;
        I_Game& operator = (const I_Game&) = delete;
    public:
        static GamePtr CreateInstanse();
        static GamePtr CreateInstanse(const GameParams& gameParams);
        virtual string GetName() const = 0;
        virtual long long GetWidth() const = 0;
        virtual long long GetHeight() const = 0;
        virtual vector<char> GetField() const = 0;
        virtual unordered_set<char> GetBirth() const = 0;
        virtual unordered_set<char> GetSurvival() const = 0;
        virtual void SetField(const int countIterations) = 0;
        virtual void PrintField() const = 0;
        virtual void Dump(const string& fileName) = 0;
        virtual bool IsLife(long long x, long long y) const = 0;
        virtual char& operator [] (int i) = 0;
        virtual const char& operator [] (int i) const = 0;
};