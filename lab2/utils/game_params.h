#pragma once

#include <vector>
#include <unordered_set>
#include <string>

using std::vector, std::unordered_set, std::string;

struct GameParams {
    vector<char> field_;
    unordered_set<char> birth_;
    unordered_set<char> survival_;
    long long width_;
    long long height_;
    string name_;
};