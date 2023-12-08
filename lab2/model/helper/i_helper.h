#pragma once

#include <memory>
#include <string>

class I_Helper;

using std::string;
using HelperPtr = std::shared_ptr<I_Helper>;

class I_Helper {
    protected:
        virtual ~I_Helper() = default;
        I_Helper& operator = (const I_Helper&) = delete;
    public:
        static HelperPtr CreateInstanse();
        virtual const string GetInfoAboutCommand(const string& command) = 0;
        virtual const string GetInfoAboutAllCommands() = 0;
        virtual const string GetDocumetation() const = 0;
        virtual void PrintHelp(const string& command) = 0;
        virtual void PrintDocs() = 0;
};