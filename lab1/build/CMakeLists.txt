cmake_minimum_required(VERSION 3.5)

project(lab1_cbuffer)

set(SOURCE_EXE ../main.cpp)
set(SOURCE_LIB_BUFFER ../buffer/buffer.cpp)

add_library(buffer STATIC ${SOURCE_LIB_BUFFER})

add_executable(${PROJECT_NAME} ${SOURCE_EXE})

target_link_libraries(${PROJECT_NAME} buffer)