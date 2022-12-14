cmake_minimum_required(VERSION 3.24)
project(aoc_christmas_2022)

set(CMAKE_CXX_STANDARD 14)

include_directories(data)
include_directories(src)

add_executable(Problem1 src/day01.cpp)
add_executable(Problem2 src/day02.cpp)
add_executable(Problem3 src/day03.cpp)
add_executable(Problem4 src/day04.cpp)
add_executable(Problem5 src/day05.cpp)
add_executable(Problem6 src/day06.cpp)
add_executable(Problem7 src/day07.cpp)
add_executable(Problem8 src/day08.cpp)
add_executable(Problem9 src/day09.cpp)
add_executable(Problem10 src/day10.cpp)
add_executable(Problem11 src/day11.cpp)
add_executable(Problem12 src/day12.cpp)
add_executable(Problem13 src/day13.cpp)

