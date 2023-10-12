cmake_minimum_required(VERSION 3.5)

project(lab0_b)

set(SOURCE_EXE ../main.cpp)
set(SOURCE_LIB_ERRORS ../errors/errors.cpp)
set(SOURCE_LIB_READER ../reader/reader.cpp)
set(SOURCE_LIB_WRITER ../writer/writer.cpp)

add_library(errors STATIC ${SOURCE_LIB_ERRORS})
add_library(reader STATIC ${SOURCE_LIB_READER})
add_library(writer STATIC ${SOURCE_LIB_WRITER})

add_executable(${PROJECT_NAME} ${SOURCE_EXE})

target_link_libraries(${PROJECT_NAME} reader errors writer)