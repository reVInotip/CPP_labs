#include "i_helper.h"
#include "helper.h"
#include "../../view/screen/i_screen.h"
#include <unordered_map>
#include <string>
#include <memory>

using std::string, std::make_shared;
using HelperPtr = std::shared_ptr<I_Helper>;

HelperPtr I_Helper::CreateInstanse() {
    return make_shared<Helper>();
}

Helper::Helper() {
    screen_ = I_Screen::CreateInstanse();
}

const string Helper::GetInfoAboutCommand(const string& command) {
    return commands_[command];
}

const string Helper::GetInfoAboutAllCommands() {
    return commands_["dump"] + "\n" + commands_["tick"] + "\n" +
    commands_["exit"] + "\n" + commands_["docs"] + "\n" + commands_["help"];
}

const string Helper::GetDocumetation() const {
    return docs_;
}

void Helper::PrintHelp(const string& command) {
    if (command == "all") {
        screen_->PrintInfo(GetInfoAboutAllCommands());
    } else {
        screen_->PrintInfo(GetInfoAboutCommand(command));
    }
}

void Helper::PrintDocs() {
    screen_->PrintInfo(docs_);
};
