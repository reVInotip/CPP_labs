#pragma once

#include "../../model/game/i_game.h"
#include "../../model/helper/i_helper.h"
#include <memory>

class I_Screen;
using std::string;
using ScreenPtr = std::shared_ptr<I_Screen>;

class I_Screen {
    protected:
        virtual ~I_Screen() = default;
        I_Screen& operator = (const I_Screen&) = delete;
    public:
        static ScreenPtr CreateInstanse();
        virtual void PrintGame(const I_Game& game) = 0;
        virtual void PrintGame(const string outputFile, const I_Game& game) = 0;
        virtual void PrintHelp(const I_Helper& helper) = 0;
};