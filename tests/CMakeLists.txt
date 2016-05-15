cmake_minimum_required(VERSION 2.8)

if(USE_CPP11)
    message(STATUS "Enabling C++11")
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif()

set(SOURCES catch.h ../main.cpp commonTests.cpp 1.txt)

add_executable(test_list ${SOURCES})
enable_testing()