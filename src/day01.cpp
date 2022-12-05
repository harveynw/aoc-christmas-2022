//
// Created by Harvey Temporary on 04/12/2022.
//

#include "day01.h"
#include "problem.h"
#include <string>
#include <iostream>

int main() {
    std::list<std::string> problemFile = loadProblem(1);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}

int problem1(const std::list<std::string> problemFile) {
    return 0;
}

int problem2(const std::list<std::string> problemFile) {
    return 0;
    }