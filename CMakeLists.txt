cmake_minimum_required(VERSION 3.7)
project(AliSimulator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp AliTracePreProcessor.h AliTracePreProcessor.cpp string_helper.cpp string_helper.h)
add_executable(AliSimulator ${SOURCE_FILES})