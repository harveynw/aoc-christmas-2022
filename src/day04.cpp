//
// Created by Harvey Temporary on 04/12/2022.
//

#include "problem.h"
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

void parse_range(string line, int *a, int *b, int *x, int *y) {
    regex str_expr( "(\\d*)-(\\d*),(\\d*)-(\\d*)" );
    smatch sm;
    regex_match (line,sm,str_expr);

    *a = stoi(sm.str(1)); *b = stoi(sm.str(2));
    *x = stoi(sm.str(3)); *y = stoi(sm.str(4));
}

int problem1(vector<string> problemFile) {
    int count = 0;
    for(auto line : problemFile) {
        int a, b, x, y;
        parse_range(line, &a, &b, &x, &y);

        if ((a >= x && b <= y) || (x >= a && y <= b)) count++;
    }
    return count;
}

int problem2(vector<string> problemFile) {
    int count = 0;
    for(auto line : problemFile) {
        int a, b, x, y;
        parse_range(line, &a, &b, &x, &y);

        if ((a >= x && a <= y) || (b >= x && b <= y) || (a <= x && y <= b)) count++;
    }
    return count;
}

int main() {
    vector<string> problemFile = loadProblemVector(4);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}
