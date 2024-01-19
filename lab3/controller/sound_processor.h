#pragma once

#include "../model/converter/converter.h"
#include <array>
#include <string>
#include <map>

using std::string, std::array, std::map;
using namespace converter;

class SoundProcessor final {
    private:
        struct Warnings {
            const string invalidConverterName =
            "[WARN] Invalid converter name ";
            const string nothingToDo = "[WARN] Nothing to do!";
            const string openFileWarn = "[WARN] Can`t open config file. Nothing to do!";
        } warnings_;
        ConverterFactory factory_;
        map<string, ConverterPtr> converters_;

        void InitSoundProcessor(int argc, char* argv[]);
    public:
        SoundProcessor();
        SoundProcessor(const array<string, 3>& converters);
        ~SoundProcessor() = default;

        template<typename Converter>
        void AddConverter(const string& converterId) {
            factory_.Add<Converter>(converterId);
            converters_[converterId] = factory_.CreateConverter(converterId);
        }

        void Init(int argc, char* argv[]);
};