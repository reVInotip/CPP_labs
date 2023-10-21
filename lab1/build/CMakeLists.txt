cmake_minimum_required(VERSION 3.5)

project(lab1_cbuffer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_EXE ../test/tests.cpp)
set(SOURCE_LIB_BUFFER ../buffer/buffer.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/116b7e55281c4200151524b093ecc03757a4ffda.zip
)
FetchContent_MakeAvailable(googletest)

add_library(buffer STATIC ${SOURCE_LIB_BUFFER})

add_executable(${PROJECT_NAME} ${SOURCE_EXE})

target_link_libraries(${PROJECT_NAME} buffer GTest::gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})