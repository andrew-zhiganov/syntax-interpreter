cmake_minimum_required(VERSION 2.8)
project(TVP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.tpp messages.tpp tests/commonTests.cpp tests/catch.h)
add_executable(TVP ${SOURCE_FILES})