cmake_minimum_required(VERSION 3.14)
project(parse_tuples)

set(CMAKE_CXX_STANDARD 17)

add_executable(parse_tuples parse_tuples.hpp tests.cpp)