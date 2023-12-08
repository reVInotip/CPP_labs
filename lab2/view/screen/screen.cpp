#include "../../model/game/i_game.h"
#include "screen.h"
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <unordered_set>
//#include <thread>
//#include <chrono>

using std::cout, std::endl, std::make_shared, std::string, std::ofstream, std::unordered_set;

using ScreenPtr = std::shared_ptr<I_Screen>;

void Screen::Clear() const {
    cout << "\x1B[2J\x1B[H";
}

ScreenPtr I_Screen::CreateInstanse() {
    return make_shared<Screen>();
}

void Screen::PrintGame(const I_Game& game) {
    Clear();
    const long long width = game.GetWidth();
    const long long height = game.GetHeight();

    cout << game.GetName() << endl;
    cout << "Screen width: " << width << "; " <<
    "Screen height: " << height << endl;

    const long long size = height * width;
    for (long long i = 0; i < size; ++i) {
        if (i % width == 0) {
            cout << "\n" << "\t";
        }
        
        if (game[i / 8] & (1 << (7 - (i % 8)))) {
            cout << life_;
        } else {
            cout << dead_;
        }
    }
    cout << endl;
}

void Screen::PrintGame(const string& fileName, const I_Game& game) {
    ofstream out(fileName);
    if (out.is_open()) {
        out << "#Life 1.06" << "\n" << "#N " << game.GetName() << endl;

        out << "#R B";
        const unordered_set<char> birth = game.GetBirth();
        const unordered_set<char> survival = game.GetSurvival();
        for (int i = 0; i < 9; ++i) {
            if (birth.count(i)) {
                out << i;
            }
        }
        out << "/S";
        for (int i = 0; i < 9; ++i) {
            if (survival.count(i)) {
                out << i;
            }
        }
        out << endl;

        out << "#W " << game.GetWidth() << endl;
        out << "#H " << game.GetHeight() << endl;

        for (long long y = 0; y < game.GetHeight(); ++y) {
            for (long long x = 0; x < game.GetWidth(); ++x) {
                if (game.IsLife(x, y)) {
                    out << x << " " << y << "\n";
                }
            }
        }
        out << endl;
    }
    out.close();
}

void Screen::PrintInfo(const string& info)  {
    Clear();
    cout << info << endl;
}