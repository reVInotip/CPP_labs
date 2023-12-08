#include "game_controller.h"
#include "i_game_controller.h"
#include "../../model/game/i_game.h"
#include "../../model/helper/i_helper.h"
#include "../../utils/game_params.h"
#include "../../utils/errors/file_not_found.h"
#include "../../utils/errors/invalid_argument.h"
#include "../../utils/errors/count_args_invalid.h"
#include <cctype>
#include <cmath>
#include <cstddef>
#include <memory>
#include <iostream>
#include <string>
#include <fstream>
#include <utility>

using GameControlPtr = std::shared_ptr<I_GameController>;
using GamePtr = std::shared_ptr<I_Game>;
using HelperPtr = std::shared_ptr<I_Helper>;
using std::make_shared, std::cin, std::string, std::isdigit,
std::cout, std::ifstream, std::getline, std::endl, std::pair, std::pow;

GameControlPtr I_GameController::CreateInstanse() {
    return make_shared<GameController>();
}

pair<bool, int> GameController::ArgumentsIsValid(char *argv[]) {
    if (argv[2][1] != 'i' && argv[2][1] != 'o') {
        
        return pair<bool, int>(false, 2);
    } else if (argv[4][1] != 'i' && argv[4][1] != 'o') {
        return pair<bool, int>(false, 4);
    }

    int pos = argv[2][1] == 'i' ? 3 : 5;
    for (int i = 0; argv[pos][i] != '\0' && pos != 0; ++i) {
        if (!isdigit(argv[pos][i])) {
            return pair<bool, int>(false, pos);
        }
    }
    return pair<bool, int>(true, -1);
}

pair<string, int> GameController::ArgumentsParser(int argc, char *argv[]) {
    pair<bool, int> isValid = ArgumentsIsValid(argv);
    if(!(isValid.first)) {
        throw InvalidArgException(argv[isValid.second]);
    }

    pair<string, int> result = {"", 0};
    int pos = argv[2][1] == 'i' ? 3 : 5;
    int arraySize = 1;
    while(argv[pos][arraySize - 1] != '\0') {
        ++arraySize;
    }

    for (int i = 0; i < arraySize - 1; ++i) {
        result.second += (argv[pos][i] - '0') * pow(10, (arraySize - 2 - i));
    }

    pos = argv[2][1] == 'o' ? 3 : 5;
    result.first = argv[pos];

    return result;
}

bool GameController::CreateGameAndHelper(int argc, char *argv[]) {
    if (argc == 1) {
        game_ = I_Game::CreateInstanse();
        helper_ = I_Helper::CreateInstanse();
    } else if (argc >= 2) {
        if (argc > 6) {
            throw InvalidCountArgsException();
        }
        GameController::FileParser(argv[1]);
        game_ = I_Game::CreateInstanse(gameParams_);
        if (argc == 2) {
            helper_ = I_Helper::CreateInstanse();
        } else {
            helper_ = nullptr;
            return true;
        }
    }
    return false;
}

void GameController::FileParser(const string& filename) {
    ifstream in(filename);
    if (in.is_open()) {
        string line;

        getline(in, line);
        if (line != "#Life 1.06") {
            cout << "Неверный формат файла!" << endl;
        }

        in >> line;
        if (line != "#N") {
            cout << messages_["#N"] << endl;
        } else {
            getline(in, gameParams_.name_);
        }

        in >> line;
        if (line != "#R") {
            cout << messages_["#R"] << endl;
        } else {
            getline(in, line, '/');
            for (int i = 2; i < line.size(); ++i) {
                gameParams_.birth_.insert(line[i] - '0');
            }

            getline(in, line);
            for (int i = 1; i < line.size(); ++i) {
                gameParams_.survival_.insert(line[i] - '0');
            }
        }

        in >> line;
        if (line != "#W") {
            cout << messages_["#W"] << endl;;
        } else {
            in >> gameParams_.width_;
        }
        
        in >> line;
        if (line != "#H") {
            cout << messages_["#H"] << endl;;
        } else {
            in >> gameParams_.height_;
        }

        const long long size = gameParams_.width_ * gameParams_.height_;
        gameParams_.field_.resize((size / 8) + (size % 8 != 0));

        long long x = 0, y = 0;
        while (in >> x >> y) {
            const long long bitNumber = y * gameParams_.width_ + x;
            gameParams_.field_[bitNumber / 8] |= (1 << (7 - (bitNumber % 8)));
        }
    } else {
        throw FileNotFoundException(filename);
    }
}

void GameController::InitGame(int argc, char *argv[]) {
    bool isOffline = CreateGameAndHelper(argc, argv);
    if (isOffline) {
        const pair<string, int> data =
        GameController::ArgumentsParser(argc, argv);
        game_->SetField(data.second);
        game_->Dump(data.first);
    }

    while(!isOffline) {
        string command;
        cout << "Введите команду: ";
        cin >> command;
        if (command == "tick" || command == "t") {
            int countIterations;
            cout << "Введите число итераций: ";
            cin >> countIterations;
            game_->SetField(countIterations);
            game_->PrintField();
        } else if (command == "exit") {
            break;
        } else if (command == "dump") {
            string fileName;
            cout << "Введите название файла: ";
            cin >> fileName;
            game_->Dump(fileName);
        } else if (command == "help") {
            string commandInfo;
            cout << "Имя команды (all для всех команд): ";
            cin >> commandInfo;
            helper_->PrintHelp(commandInfo);
        } else if (command == "docs") {
            helper_->PrintDocs();
        } else {
            cout << "Не существет команды " << command << "\n" <<
                "Введите help для получения информации о командах" << endl;
        }
    }
}