#pragma once

#include <string>

using std::string;

class Helper {
    private:
        const string message_ = "***DESIGNATIONS***\n[] - optional parameter\n(sec) - units of measurement\n\
***GENERAL INFORMATION***\nThe sound processor can update your audio data encoded in WAV format. Input data:\n\
./lab3_sound_processor -c config_file_name.txt -s output_file.wav input_file_1.wav [input_file_2.wav ... input_file_n.wav] or\n\
./lab3_sound_processor -h to call help. Output file can be only one and input files could be one or more.\n\
***CONFIG FILE STRUCTURE***\n# - comment\nDefault available converters:\n - mix $sample [$sample_1 ... $sample_n] time_start(sec) time_end(sec):\
 mix one or more samples in time interval\n - mix [$sample] time_start(sec) time_end(sec): mute one sample in time interval\n -\
 volume [$sample] time_start(sec) time_end(sec) k: increase volume by k times.\n\
All converters might have time for start convertation and time for end, time for start or none of them.\n\
All converters overwrite output sample after work.\nIf you don`t write sample number for volume and mute converter or write only one\
sample number for mix converter they will be used output sample.\nThis allows you to combine this converters.\n***CREATE YOUR CONVERTER***\n\
You can create your own converter. For this you must write converter(it should be the heir of ConverterInterface class).\n\
After that you can add it to the converter factory directly or using Sound Processor interface(recommended).";
    public:
        Helper() = default;
        ~Helper() = default;
        const string& GetHelp() const noexcept;
};