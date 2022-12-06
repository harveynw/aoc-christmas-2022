//
// Created by Harvey Temporary on 04/12/2022.
//

#include "problem.h"
#include <string>
#include <iostream>
#include <vector>

int problem1(const std::list<std::string> problemFile) {
    int currentSum = 0; int maxSum = 0;
    for(auto line : problemFile) {
        if(line == "") {
            maxSum = std::max(maxSum, currentSum);
            currentSum = 0;
        } else {
            currentSum += std::stoi(line);
        }
    }
    return maxSum;
}

int problem2(const std::list<std::string> problemFile) {
    std::vector<int> sums; int currentSum = 0;
    for(auto line : problemFile) {
        if(line == "") {
            sums.push_back(currentSum);
            currentSum = 0;
        } else {
            currentSum += std::stoi(line);
        }
    }

    std::sort(sums.begin(), sums.end());
    std::reverse(sums.begin(), sums.end());

    return sums[0] + sums[1] + sums[2];
}

int main() {
    std::list<std::string> problemFile = loadProblem(1);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}
