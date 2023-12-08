#include "controller/game_controller/i_game_controller.h"
#include "utils/errors/file_not_found.h"
#include "utils/errors/invalid_argument.h"
#include "utils/errors/count_args_invalid.h"
#include <memory>
#include <iostream>

using GamePtr = std::shared_ptr<I_GameController>;
using std::cout;

int main(int argc, char *argv[]) {
    try {
        GamePtr game = I_GameController::CreateInstanse();
        game->InitGame(argc, argv);
    } catch(const FileNotFoundException& execption) {
        cout << execption.what();
    } catch(const InvalidArgException& execption) {
        cout << execption.what();
    } catch(const InvalidCountArgsException& execption) {
        cout << execption.what();
    }
    return 0;
}