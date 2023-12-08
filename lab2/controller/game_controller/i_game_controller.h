#pragma once

#include <string>
#include <memory>

class I_GameController;

using std::string;
using GameControlPtr = std::shared_ptr<I_GameController>;

class I_GameController {
    protected:
        virtual ~I_GameController() = default;
        I_GameController& operator = (const I_GameController&) = delete;
    public:
        static GameControlPtr CreateInstanse();
        virtual void InitGame(int argc, char *argv[]) = 0;
};