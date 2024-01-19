cmake_minimum_required(VERSION 3.5)

project(wav_lib
    VERSION 1.0.0
    DESCRIPTION "Wav library for read and write .wav file in specific (PCM and settings) format"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC ../exceptions/exceptions.cpp ../wav_reader/wav_reader.cpp ../wav_writer/wav_writer.cpp)
set(HEADERS ../exceptions/file_incorrect.h ../exceptions/file_not_open.h ../wav.h)

add_library(${PROJECT_NAME} STATIC ${SRC} ${HEADERS})