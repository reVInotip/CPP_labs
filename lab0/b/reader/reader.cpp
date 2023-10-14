#include <bits/types/locale_t.h>
#include <cctype>
#include <cwctype>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <sys/types.h>
#include "reader.h"
#include "../errors/errors.h"

using std::wifstream, std::string, std::wstring, std::cout, std::map,
std::endl, std::getline, std::isalnum, std::locale;

Reader::Reader(string fileName) {
    inputStream.open(fileName, std::ios::in);
    try {
        if (!inputStream.is_open()) {
            throw WrongFileException(fileName);
        }
    } catch(const WrongFileException& execption) {
        cout << execption.execptionText << endl;
    }
}

Reader::Reader(): Reader("in.txt") {}

Reader::~Reader() {
    inputStream.close();
}

void Reader::Read(map<wstring, int>& words) {
    wstring currentString;
    while (getline(inputStream, currentString)) {
        wstring str;
        str.reserve(currentString.size());
        for(const wchar_t& var : currentString) {
            if (isalnum(var, locale())) {
                str += var;
            } else {
                ++words[str];
                str.clear();
            }
        }
        ++words[str];
    }
}
