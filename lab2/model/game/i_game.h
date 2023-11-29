#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <array>

class I_Game;

using std::string, std::array;
using GamePtr = std::shared_ptr<I_Game>;

class I_Game {
    protected:
        virtual ~I_Game() = default;
        I_Game& operator = (const I_Game&) = delete;
    public:
        static GamePtr CreateInstanse();
        virtual string GetName() const = 0;
        virtual size_t GetWidth() const = 0;
        virtual size_t GetHeight() const = 0;
        virtual void GetField() const = 0;
        virtual void SetField(const int countIterations) = 0;
        virtual void Dump(string& fileName) = 0;
        virtual void Exit() = 0;
        virtual char& operator [] (int i) = 0;
        virtual const char& operator [] (int i) const = 0;
};