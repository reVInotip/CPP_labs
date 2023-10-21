cmake_minimum_required(VERSION 3.5)
project(test)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/116b7e55281c4200151524b093ecc03757a4ffda.zip
)

enable_testing()

add_executable(
  tests
  tests.cpp
)

target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
