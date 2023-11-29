#pragma once

#include "../../model/game/game.h"
#include "../../model/helper/helper.h"
#include "i_game_controller.h"
#include <string>

using std::string;

class GameController final : public I_GameController {
    private:
        Game* game_;
        Helper* helper_;
    public:
        GameController(Game& game, Helper& helper);
        ~GameController() = default;
        void Dump(string outputFile) override;
        void Tick(int countIterations) override;
        void Exit() override;
        void Help() override;
        void Read(string inputFile) override;
};