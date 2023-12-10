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
        //void Sleep(long int nanoseconds) const;
        void Clear() const;
    public:
        Screen() = default;
        void PrintGame(const I_Game& game) override;
        void PrintGame(const string& fileName, const I_Game& game) override;
        void PrintInfo(const string& info) override;
        ~Screen() = default;
};