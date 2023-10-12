#include <fstream>
#include <list>
#pragma once

using std::wofstream, std::string, std::wstring, std::pair, std::list;

/*Write */
class Writer {
    private:
        wofstream outputStream;
    public:
        Writer(string fileName);
        Writer();
        ~Writer();
        void Write(list<pair<wstring, int>>&);
};