cmake_minimum_required(VERSION 3.24)
project(aoc_christmas_2022)

set(CMAKE_CXX_STANDARD 14)

include_directories(data)
include_directories(src)

add_executable(Problem1 src/day01.cpp)
add_executable(Problem2 src/day02.cpp)
add_executable(Problem3 src/day03.cpp)
add_executable(Problem4 src/day04.cpp)