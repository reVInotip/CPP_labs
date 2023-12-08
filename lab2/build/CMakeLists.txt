cmake_minimum_required(VERSION 3.5)

project(lab2_life)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_EXE ../main.cpp)
set(SOURCE_LIB_CONTROLLER ../controller/game_controller/game_controller.cpp)
set(SOURCE_LIB_GAME ../model/field/field.cpp ../model/game/game.cpp ../model/helper/helper.cpp)
set(SOURCE_LIB_ERRORS ../utils/errors/errors.cpp)
set(SOURCE_LIB_SCREEN ../view/screen/screen.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/116b7e55281c4200151524b093ecc03757a4ffda.zip
)
FetchContent_MakeAvailable(googletest)

add_library(life STATIC ${SOURCE_LIB_CONTROLLER} ${SOURCE_LIB_GAME} ${SOURCE_LIB_ERRORS} ${SOURCE_LIB_SCREEN})

add_executable(${PROJECT_NAME} ${SOURCE_EXE})

target_link_libraries(${PROJECT_NAME} life GTest::gtest_main)
target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall -Wextra -Wpedantic
)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})