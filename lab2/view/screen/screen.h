#pragma once

#include "../../model/helper/i_helper.h"
#include "../../model/game/i_game.h"
#include "i_screen.h"
#include <string>
#include <utility>

using std::string;

class Screen final : public I_Screen {
    private:
        static constexpr char life_ = '#';
        static constexpr char dead_ = '.';
    public:
        Screen();
        void PrintGame(const I_Game& game) override;
        void PrintGame(const string outputFile, const I_Game& game) override;
        void PrintHelp(const I_Helper& helper) override;
        ~Screen() = default;
};