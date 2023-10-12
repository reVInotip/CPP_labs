#include <fstream>
#include <string>
#include <map>
#pragma once

using std::wifstream, std::string, std::wstring, std::map;


/* Read all words consisting of letters and digits from file
(if file name is empty search standart input file)*/
class Reader {
    private:
        wifstream inputStream;
    public:
        Reader(string fileName);
        Reader();
        ~Reader();
        void Read(map<wstring, int>&);
};