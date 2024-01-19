#include "converter.h"
#include "exceptions/converter_exception.h"
#include <climits>
#include <sstream>
#include <iostream>

using namespace converterException;
using std::get, std::istringstream;

void converter::VolumeConverter::ParseArguments(const string& args, ConverterDTO& info, tuple<unsigned, unsigned>& times, unsigned& stream, double& multiplier) {
   istringstream argsStream(args);

    string argument;
    int time[2] = {-1, -1};
    int countDollars = 0, countTimes = -1, countMultipliers = 0;
    while (argsStream >> argument) {
        if (argument[0] == '$') {
            ++countDollars;
            if (countDollars > 1) {
                throw InvalidCountStreamsException();
            }
            stream = stoi(argument.substr(1, argument.length() - 1));
        } else if (countTimes < 1) {
            ++countTimes;
            time[countTimes] = stoi(argument);
        } else {
            ++countMultipliers;
            if (countMultipliers > 1) {
                throw InvalidCountMultipliersException();
            }
            multiplier = stod(argument);
        }
    }

    if (countMultipliers == 0) {
        throw NoMultipliersException();
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
}

void converter::VolumeConverter::ChangeAudioData(const string& args, converter::ConverterDTO& info) {
    unsigned stream = 0;
    double multiplier;
    tuple<unsigned, unsigned> times;
    ParseArguments(args, info, times, stream, multiplier);

    if (stream > info.samples.size() - 1) {
        throw InvalidStreamNumberException(stream, info.samples.size() - 1);;
    }

    const long long startSample = info.sampleRate * get<0>(times) * info.numChannels;
    const long long endSample = info.sampleRate * get<1>(times) * info.numChannels;
        
    vector<int16_t> inputSample = info.samples[stream];

    for (long long i = startSample; i <= endSample; ++i) {
        if (i >= inputSample.size()) {
            break;
        }
        inputSample[i] *= multiplier;
    }

    info.samples[0] = inputSample;
}