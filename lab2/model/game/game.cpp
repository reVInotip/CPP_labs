#include "game.h"
#include "../../view/screen/i_screen.h"
#include "../../utils/game_params.h"
#include <codecvt>
#include <iostream>
#include <memory>
#include <string>

using GamePtr = std::shared_ptr<I_Game>;
using ScreenPtr = std::shared_ptr<I_Screen>;
using std::make_shared, std::string;

GamePtr I_Game::CreateInstanse() {
    return make_shared<Game>(Game());
}

GamePtr I_Game::CreateInstanse(const GameParams& gameParams) {
    return make_shared<Game>(Game(gameParams));
}

void Game::SetRules() {
    const auto rg = {2, 3};
    rules_.birth_.insert(3);
    rules_.survival_.insert(rg.begin(), rg.end());
}

void Game::SetRules(unordered_set<char>& birth, unordered_set<char>& survival) {
    rules_.birth_ = birth;
    rules_.survival_ = survival;
}

Game::Game() : Field() {
    name_ = "Default Game";
    screen_ = I_Screen::CreateInstanse();

    SetRules();
}

Game::Game(const GameParams& gameParams) : 
Field(gameParams.field_, gameParams.width_, gameParams.height_) {
    screen_ = I_Screen::CreateInstanse();

    rules_.birth_ = gameParams.birth_;
    rules_.survival_ = gameParams.survival_;
    name_ = gameParams.name_;
}

string Game::GetName() const {
    return name_;
}

long long Game::GetWidth() const {
    return Field::GetWidth();
}

long long Game::GetHeight() const {
    return Field::GetHeight();
}

vector<char> Game::GetField() const {
    return Field::GetField();
}

unordered_set<char> Game::GetBirth() const {
    return rules_.birth_;
}

unordered_set<char> Game::GetSurvival() const {
    return rules_.survival_;
}

void Game::SetField(const int countIterations) {
    Field::SetField(countIterations, rules_.birth_, rules_.survival_);
}

void Game::PrintField() const {
    screen_->PrintGame(*this);
}

void Game::Dump(const string& fileName) {
    screen_->PrintGame(fileName, *this);
}

bool Game::IsLife(long long x, long long y) const {
    return Field::IsLife(x, y);
}

char& Game::operator [] (int i) {
    return Field::operator [] (i);
}

const char& Game::operator [] (int i) const {
    return Field::operator [] (i);
}