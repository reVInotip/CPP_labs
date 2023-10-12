#include <cstdlib>
#include <iostream>
#include <locale>
#include <map>
#include <list>
#include <string>
#include "reader/reader.h"
#include "writer/writer.h"

using std::wstring, std::map, std::locale, std::numpunct, std::list, std::pair, std::cout, std::endl;

bool isLess(const pair<wstring, int>& p1, const pair<wstring, int>& p2) {
    return p2.second < p1.second || p1.first < p2.first;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Please, enter input file name and output file name" << endl;
        return EXIT_FAILURE;
    }

    locale::global(locale("ru_RU.utf8").combine<numpunct<wchar_t>>(locale("C")));
    Reader reader(argv[1]);
    map<wstring, int> freqs;
    reader.Read(freqs);

    list<pair<wstring, int>> sortedByFreq(freqs.begin(), freqs.end());

    sortedByFreq.sort(isLess);
    
    Writer writer(argv[2]);
    writer.Write(sortedByFreq);

    return EXIT_SUCCESS;
}