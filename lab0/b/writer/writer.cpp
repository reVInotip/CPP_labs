#include <iostream>
#include <string>
#include "writer.h"
#include "../errors/errors.h"

using std::wofstream, std::string, std::wstring, std::cout, std::endl;

Writer::Writer(string fileName) {
    outputStream.open(fileName, std::ios::out);
    try {
        if (!outputStream.is_open()) {
            throw WrongFileException();
        }
    } catch(const WrongFileException& execption) {
        cout << execption.execptionText << endl;
    }
}

Writer::Writer(): Writer("out.txt") {}

Writer::~Writer() {
    outputStream.close();
}

void Writer::Write(list<pair<wstring, int>>& wordsByFreq) {
    for(const auto& [word, freq] : wordsByFreq) {
        outputStream << word << ";" << freq << "\n";
    }
}