#pragma once

#include "../../model/game/i_game.h"
#include "../../model/helper/i_helper.h"
#include "../../utils/game_params.h"
#include "i_game_controller.h"
#include <fstream>
#include <string>
#include <memory>
#include <unordered_map>


using std::string, std::unordered_map, std::ifstream, std::pair;
using GamePtr = std::shared_ptr<I_Game>;
using HelperPtr = std::shared_ptr<I_Helper>;

class GameController final : public I_GameController {
    private:
        GamePtr game_;
        HelperPtr helper_;
        GameParams gameParams_;
        unordered_map<string, string> messages_ = {
            {"#N", "Файл не содержит метку name (#N)!"},
            {"#W", "Файл не содержит метку width (#W)!"},
            {"#H", "Файл не содержит метку height (#H)!"},
            {"#R", "Файл не содержит метку rules (#R)!"},
        };

        pair<bool, int> ArgumentsIsValid(char *argv[]);
        bool CreateGameAndHelper(int argc, char *argv[]);
        void FileParser(const string& fileName);
        pair<string, int> ArgumentsParser(int argc, char *argv[]);
    public:
        GameController() = default;
        ~GameController() = default;
        void InitGame(int argc, char *argv[]) override;
};