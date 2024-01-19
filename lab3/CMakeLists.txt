cmake_minimum_required(VERSION 3.5)

project(lab3_sound_processor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(utils/wav/build ./build)

set(SOURCE_EXE main.cpp)
set(SOURCE_LIB_CONTROLLER controller/sound_processor.cpp)
set(SOURCE_LIB_MODEL model/converter/mix_converter.cpp model/converter/mute_converter.cpp 
  model/converter/volume_converter.cpp model/helper/helper.cpp)
set(SOURCE_LIB_ERRORS utils/wav/exceptions/exceptions.cpp model/converter/exceptions/converter_exception.cpp
  controller/exceptions/sound_processor_exception.cpp)

add_library(sound_processor STATIC ${SOURCE_LIB_CONTROLLER} ${SOURCE_LIB_MODEL} ${SOURCE_LIB_ERRORS})

add_executable(${PROJECT_NAME} ${SOURCE_EXE})

target_link_libraries(${PROJECT_NAME} sound_processor wav_lib)
target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall -Wextra -Wpedantic
)