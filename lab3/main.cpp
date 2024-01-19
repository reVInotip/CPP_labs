#include "controller/sound_processor.h"
#include "model/converter/exceptions/converter_exception.h"
#include "controller/exceptions/sound_processor_exception.h"
#include "utils/wav/exceptions/file_incorrect.h"
#include "utils/wav/exceptions/file_not_open.h"
#include <array>
#include <iostream>
#include <stdexcept>

using namespace soundProcessorExceprions;
using namespace converterException;
using namespace wav;
using std::cerr, std::endl;

int main(int argc, char *argv[]) {
    try {
        SoundProcessor s = SoundProcessor{array<string, 3>{"mute", "mix", "volume"}};
        s.Init(argc, argv);
    } catch (const SoundProcessorException& exception) {
        cerr << exception.what() << endl;
        return exception.code();
    } catch (const ConverterException& exception) {
        cerr << exception.what() << endl;
        return exception.code();
    } catch (const WavFileNotOpenException& exception) {
        cerr << exception.what() << endl;
        return exception.code();
    } catch (const WavFileNotValidException& exception) {
        cerr << exception.what() << endl;
        return exception.code();
    } catch (std::invalid_argument& exception) {
        cerr << exception.what() << endl;
        return 4;
    } catch (std::out_of_range& exception) {
        cerr << exception.what() << endl;
        return 5;
    }
    return 0;
}