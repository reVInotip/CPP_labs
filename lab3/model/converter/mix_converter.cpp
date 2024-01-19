#include "converter.h"
#include "exceptions/converter_exception.h"
#include <algorithm>
#include <climits>
#include <initializer_list>
#include <sstream>
#include <vector>
#include <set>

using namespace converterException;
using std::get, std::max_element, std::set, std::istringstream, std::stoi;

void converter::MixConverter::ParseArguments(const string& args, ConverterDTO& info, tuple<unsigned, unsigned>& times, vector<unsigned>& streams) {
    set<unsigned> streamsSet;
    istringstream argsStream(args);

    string argument;
    argsStream >> argument;

    if (argument[0] != '$') {
        throw InvalidStreamForMixConverterException(argument);
    }
    streamsSet.insert(stoi(argument.substr(1, argument.length() - 1)));

    int countTimes = -1;
    int time[2] = {-1, -1};
    while (argsStream >> argument) {
        if (argument[0] == '$') {
            streamsSet.insert(stoi(argument.substr(1, argument.length() - 1)));
        } else {
            ++countTimes;
            if (countTimes > 1) {
                throw InvalidCountTimesException(countTimes);
            }
            time[countTimes] = stoi(argument);
        }
    }

    if (time[0] == -1) {
        time[0] = 0;
    }
    if (time[1] == -1) {
        time[1] = INT_MAX / (info.sampleRate * info.numChannels);
    }

    if (time[0] >= time[1]) {
        throw TimeStartBiggerThenTimeEndException();
    }

    times = {time[0], time[1]};

    if (streamsSet.size() == 1) {
        streamsSet.insert(0);
    }

    streams = {streamsSet.begin(), streamsSet.end()};
}

void converter::MixConverter::ChangeAudioData(const string& args, ConverterDTO& info) {
    vector<unsigned> streams;
    tuple<unsigned, unsigned> times;
    ParseArguments(args, info, times, streams);

    const long long countSamplesStart = info.sampleRate * get<0>(times) * info.numChannels;
    const long long countSamplesEnd = info.sampleRate * get<1>(times) * info.numChannels;

    auto longest = [](const vector<int16_t> s1, const vector<int16_t> s2)
                   {
                       return s1.size() < s2.size();
                   };
    const auto max = max_element(info.samples.begin(), info.samples.end(), longest);
    
    info.samples[0].resize(max->size());
    int16_t average = 0;
    int countEnd = 0;
    for (long long i = countSamplesStart; i <= countSamplesEnd; ++i) {
        for (const auto& streamNumber: streams) {
            if (streamNumber > info.samples.size() - 1) {
                throw InvalidStreamNumberException(streamNumber, info.samples.size() - 1);
            }
            if (i >= info.samples[streamNumber].size()) {
                ++countEnd;
                continue;
            }
            average += info.samples[streamNumber][i];
        }
        if (i >= info.samples[0].size() || countEnd == streams.size()) {
            break;
        }
        average /= streams.size() - countEnd;
        info.samples[0][i] = average;
        average = 0;
    }
}