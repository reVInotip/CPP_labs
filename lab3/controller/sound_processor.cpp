#include "../utils/wav/wav.h"
#include "sound_processor.h"
#include "../model/converter/converter.h"
#include "exceptions/sound_processor_exception.h"
#include "../model/helper/helper.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace wav;
using namespace converter;
using namespace soundProcessorExceprions;
using std::string, std::ifstream, std::vector, std::cout, std::endl;

void SoundProcessor::InitSoundProcessor(int argc, char* argv[]) {
    if (argc < 4) {
        throw TooFewArgumentsException();
    }

    string confFileName = argv[2];

    if (argv[3][1] != 's') {
        throw InvalidSecondCommandException(argv[3]);
    }

    const int countFiles = argc - 4;

    if (countFiles <= 1) {
        cout << warnings_.nothingToDo << endl;
        return;
    }

    vector<WavHeader> wavFilesHeaders;
    wavFilesHeaders.resize(countFiles);
    vector<vector<int16_t>> wavFilesData;
    wavFilesData.resize(countFiles);

    WavReader reader;
    for (int i = 5; i < argc; ++i) {
        reader.ReadWav(argv[i]);
        wavFilesHeaders[i - 4] = reader.GetHeader();
        wavFilesData[i - 4] = reader.GetData();
    }

    ifstream in(confFileName);
    
    if (in.fail()) {
        cout << warnings_.openFileWarn << endl;
        return;
    }

    string line;
    ConverterDTO info;

    info.samples = {wavFilesData.begin(), wavFilesData.end()};
    info.sampleRate = wavFilesHeaders[1].sampleRate;
    info.numChannels = wavFilesHeaders[1].numChannels;

    while(in >> line) {
        if (line[0] == '#') {
            getline(in, line);
            continue;
        }

        if (converters_.count(line)) {
            string args;
            getline(in, args);

            //format args string
            args.erase(0, 1);
            args.push_back(' ');

            converters_[line]->ChangeAudioData(args, info);
        } else {
            throw InvalidConverterNameException(line);
        }
    }

    WavWriter writer;
    writer.WriteWav(argv[4], wavFilesHeaders[1], info.samples[0]);
}

SoundProcessor::SoundProcessor() {
    factory_.Add<MixConverter>("mix");
    factory_.Add<MuteConverter>("mute");
    factory_.Add<VolumeConverter>("volume");

    converters_["mix"] = factory_.CreateConverter("mix");
    converters_["mute"] = factory_.CreateConverter("mute");
    converters_["volume"] = factory_.CreateConverter("volume");
}

SoundProcessor::SoundProcessor(const array<string, 3>& converters) {
    factory_.Add<MixConverter>("mix");
    factory_.Add<MuteConverter>("mute");
    factory_.Add<VolumeConverter>("volume");

    for (const auto& converter: converters) {
        if (converter == "") {
            continue;
        } else if (converter != "mix" && converter != "mute" && converter != "volume") {
            cout << warnings_.invalidConverterName + converter << endl;
            continue;
        }
        converters_[converter] = factory_.CreateConverter(converter);
    }
}

void SoundProcessor::Init(int argc, char* argv[]) {
    if (argv[1][1] == 'h') {
        Helper helper = Helper();
        cout << helper.GetHelp() << endl;
    } else if (argv[1][1] == 'c') {
        InitSoundProcessor(argc, argv);
    } else {
        throw InvalidFirstCommandException(argv[1]);
    }
}