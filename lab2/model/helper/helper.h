#pragma once

#include "../../view/screen/i_screen.h"
#include "i_helper.h"
#include <unordered_map>
#include <string>

using ScreenPtr = std::shared_ptr<I_Screen>;
using std::unordered_map, std::string;

class Helper final : public I_Helper {
    private:
        unordered_map<string, string> commands_ = {
            {"dump", "dump <filename> - сохранить вселенную в файл"},
            {"tick", "tick <n> (и сокращенно t <n>) - рассчитать n итераций и напечатать результат"},
            {"exit", "завершить игру"},
            {"docs", "docs - документация к игре"},
            {"help", "help <command (опцинально)> - информация о команде(ах)"}
        };

        const string docs_ = "Добро пожаловать в игру 'Жизнь'!\n\
        Программа умеет работать в трёх режимах\n\
            1. Онлайн с аргументом в виде имени файла, содержащего вселенную в формате #Life 1.06\n\
            2. Онлайн с стандартными настройками поля\n\
            3. Офлайн с аргументами в виде имени входного файла (обязательно первым аргументом),\n\
            числа итераций <-i n> и имени выходного файла <-o filename>\n\
        Поле в Oxy задаётся так: начало отсчёта - верхний левый угол, положительное направление оси Oy\n\
        направлено вниз, оси Ox вправо. Поле тороидально.";
        
        ScreenPtr screen_;
    public:
        Helper();
        const string GetInfoAboutCommand(const string& command) override;
        const string GetInfoAboutAllCommands() override;
        const string GetDocumetation() const override;
        void PrintHelp(const string& command) override;
        void PrintDocs() override;
        ~Helper() = default;
};