//
// Created by Harvey Temporary on 04/12/2022.
//

#include "problem.h"
#include <iostream>
#include <utility>
#include <vector>
#include <regex>
#include <set>

using namespace std;

regex LINE_EXPR( "addx (-\\d+|\\d+)" );
const static int width = 40;
const static int height = 6;

int addx(string call) {
    smatch sm;
    regex_match (call,sm,LINE_EXPR);
    return stoi(sm.str(1));
}

bool inSet(int x, set<int> &s) {
    auto search = s.find(x);
    return search != s.end();
}

int signalStrengthSum(const vector<string> problemFile, set<int> atCycles) {
    int cycle = 1; int reg = 1;
    int sum = 0;
    for(int i = 0; i < problemFile.size(); i++) {
        string call = problemFile[i];

        if(inSet(cycle, atCycles)) sum += cycle*reg;

        if(call != "noop") {
            if(inSet(cycle+1, atCycles)) sum += (cycle+1)*reg;
            cycle += 2;
            reg += addx(call);
        } else {
            cycle++;
        }
    }
    return sum;
}

void blit(bool (&screen)[width*height], int cycle, int reg) {
    int hor = ((cycle-1) % 40);
    if(reg-1 == hor || reg == hor || reg+1 == hor) screen[cycle-1] = true;
}

void render(const vector<string> problemFile, bool (&screen)[width*height]) {
    int cycle = 1; int reg = 1;
    for(int i = 0; i < problemFile.size(); i++) {
        string call = problemFile[i];

        blit(screen, cycle, reg);

        if(call != "noop") {
            blit(screen, cycle+1, reg);
            cycle += 2;
            reg += addx(call);
        } else {
            cycle++;
        }
    }
}

void print(bool (&screen)[width*height]) {
    for(int i = 0; i < width*height; i++) {
        if(i % 40 == 0) cout << endl;
        cout << (screen[i] ? '#' : '.');
    }
    cout << endl;
}

int problem1(const vector<string> problemFile) {
    return signalStrengthSum(problemFile, set<int>{20, 60, 100, 140, 180, 220});
}

void problem2(const vector<string> problemFile) {
    bool screen[width*height] = { 0 };
    render(problemFile, screen);
    print(screen);
}

int main() {
    vector<string> problemFile = loadProblemVector(10);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl; problem2(problemFile);
}
