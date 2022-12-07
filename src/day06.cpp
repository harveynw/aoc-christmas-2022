//
// Created by Harvey Temporary on 04/12/2022.
//

#include "problem.h"
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int problem1(const vector<string> problemFile) {
    string buffer = problemFile[0];
    set<char> signal;
    for(int i = 4-1; i < buffer.length(); i++) {
        signal = {buffer[i-3], buffer[i-2], buffer[i-1], buffer[i]};

        if(signal.size() == 4) return i+1;

        signal.clear();
    }
    return -1;
}

int problem2(vector<string> problemFile) {
    string buffer = problemFile[0];
    set<char> signal;
    for(int i = 0; i+14 <= buffer.length(); i++) {
        string sub = buffer.substr(i, 14);
        for (char c: sub) {
            signal.emplace(c);
        }

        if(signal.size() == 14) return i+14;

        signal.clear();
    }
    return -1;
}

int main() {
    vector<string> problemFile = loadProblemVector(6);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}
