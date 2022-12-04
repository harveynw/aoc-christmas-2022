cmake_minimum_required(VERSION 3.24)
project(aoc_christmas_2022)

set(CMAKE_CXX_STANDARD 14)

include_directories(data)
include_directories(src)

add_executable(aoc_christmas_2022
        data/input01.txt
        src/day01.cpp
        src/day01.h
        src/problem.h)
