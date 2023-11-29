#include "../../model/game/i_game.h"
#include "screen.h"
#include <cstddef>
#include <memory>
#include <iostream>

using std::cout, std::endl, std::make_shared;

using ScreenPtr = std::shared_ptr<I_Screen>;

ScreenPtr I_Screen::CreateInstanse() {
    return make_shared<Screen>();
}

void Screen::PrintGame(const I_Game& game) {
    const size_t width = game.GetWidth();
    const size_t height = game.GetHeight();

    cout << game.GetName() << endl;
    cout << "Screen width: " << width << "; " <<
    "Screen height: " << height << endl;

    const size_t size = height * width;
    for (size_t i = 0; i < size; ++i) {
        if (i % width == 0) {
            cout << "\n" << "\t";
        }
            
        if (game[i / 8] & (1 << (size - i - 1))) {
            cout << "X";
        } else {
            cout << "-";
        }
    }
    cout << endl;
}