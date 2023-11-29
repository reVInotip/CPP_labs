#pragma once

#include "i_helper.h"
#include <unordered_map>
#include <string>

using std::unordered_map, std::string;

class Helper final : public I_Helper {
    private:
        unordered_map<string, string> commands;
    public:
        Helper();
        void GetInfoAboutRule(const string& rule) const override;
        void GetInfoAboutAllRules() const override;
        ~Helper();
};