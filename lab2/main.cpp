#define test

#ifdef test

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

#endif
#ifndef test

#include "model/game/i_game.h"
#include "utils/game_params.h"
#include <vector>
#include <unordered_set>
#include <fstream>
#include <gtest/gtest.h>

using GamePtr = std::shared_ptr<I_Game>;
using std::vector, std::unordered_set, std::ifstream;

TEST(LifeTest, InitTest) {
    vector<char> vec;
    vec.resize(16*32/8);
    unordered_set<char> set = {2, 3};
    GameParams params = {
        vec,
        set,
        set,
        16,
        32,
        "Aboba"
    };
    GamePtr life = I_Game::CreateInstanse(params);
    EXPECT_EQ(life->GetHeight(), 32);
    EXPECT_EQ(life->GetWidth(), 16);
    EXPECT_EQ(life->GetName(), "Aboba");
    EXPECT_EQ(life->GetBirth(), set);
    EXPECT_EQ(life->GetSurvival(), set);
    EXPECT_EQ(life->GetField(), vec);
}

TEST(LifeTest, RunTest) {
    vector<char> vec;
    vec.resize(2);
    vec[0] = 0b00011010;
    unordered_set<char> birth = {3};
    unordered_set<char> survival = {2, 3};
    GameParams params = {
        vec,
        birth,
        survival,
        3,
        3,
        "Aboba"
    };
    GamePtr life = I_Game::CreateInstanse(params);
    life->SetField(1);
    
    EXPECT_TRUE(life->IsLife(0, 0));
    EXPECT_TRUE(life->IsLife(1, 0));
    EXPECT_FALSE(life->IsLife(2, 0));
    EXPECT_TRUE(life->IsLife(0, 1));
    EXPECT_TRUE(life->IsLife(0, 2));
    EXPECT_TRUE(life->IsLife(1, 1));
    EXPECT_TRUE(life->IsLife(1, 2));
    EXPECT_TRUE(life->IsLife(2, 1));
    EXPECT_FALSE(life->IsLife(2, 2));
}

TEST(LifeTest, GetArenaTest) {
    GamePtr life = I_Game::CreateInstanse();
    auto res = life->GetField();
    vector<char> vec;
    vec.resize(life->GetWidth() * life->GetHeight() / 8);

    EXPECT_FALSE(res == vec);
}

TEST(LifeTest, FileReadWriteTest) {
    vector<char> vec;
    vec.resize(2);
    vec[0] = 0b00011010;
    unordered_set<char> birth = {3};
    unordered_set<char> survival = {2, 3};
    GameParams params = {
        vec,
        birth,
        survival,
        3,
        3,
        "Aboba"
    };
    GamePtr life = I_Game::CreateInstanse(params);
    life->SetField(1);
    life->Dump("in.txt");

    ifstream in("in.txt");
    EXPECT_TRUE(in.is_open());

    string line;

    getline(in, line);
    EXPECT_TRUE(line == "#Life 1.06");

    getline(in, line);
    EXPECT_TRUE(line == "#N Aboba");

    getline(in, line);
    EXPECT_TRUE(line == "#R B3/S23");

    getline(in, line);
    EXPECT_TRUE(line == "#W 3");

    getline(in, line);
    EXPECT_TRUE(line == "#H 3");

    int x = 0, y = 0;
    in >> x >> y;
    EXPECT_TRUE(x == 0 && y == 0);
    in >> x >> y;
    EXPECT_TRUE(x == 1 && y == 0);
    in >> x >> y;
    EXPECT_TRUE(x == 0 && y == 1);
    in >> x >> y;
    EXPECT_TRUE(x == 1 && y == 1);
    in >> x >> y;
    EXPECT_TRUE(x == 2 && y == 1);
    in >> x >> y;
    EXPECT_TRUE(x == 0 && y == 2);
    in >> x >> y;
    EXPECT_TRUE(x == 1 && y == 2);
}

#endif
