cmake_minimum_required(VERSION 2.8)
project(syntax-interpreter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.tpp messages.tpp tests/commonTests.cpp tests/catch.h)
add_executable(syntax-interpreter ${SOURCE_FILES})