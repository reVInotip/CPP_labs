#pragma once

#include "../../model/helper/i_helper.h"
#include <memory>
#include <string>

class I_Screen;
class I_Game;

using std::string;
using ScreenPtr = std::shared_ptr<I_Screen>;
using GamePtr = std::shared_ptr<I_Game>;

class I_Screen {
    protected:
        virtual ~I_Screen() = default;
        I_Screen& operator = (const I_Screen&) = delete;
    public:
        static ScreenPtr CreateInstanse();
        virtual void PrintGame(const I_Game& game) = 0;
        virtual void PrintGame(const string& fileName, const I_Game& game) = 0;
        virtual void PrintInfo(const string& info) = 0;
};