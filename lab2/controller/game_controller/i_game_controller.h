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
        virtual void Dump(string outputFile) = 0;
        virtual void Tick(int countIterations) = 0;
        virtual void Exit() = 0;
        virtual void Help() = 0;
        virtual void Read(string inputFile) = 0;
};