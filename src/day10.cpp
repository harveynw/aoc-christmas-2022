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

void blit(bool (&screen)[width*height], int cycle, int reg) {
    int hor = ((cycle-1) % 40);
    if(reg-1 == hor || reg == hor || reg+1 == hor) screen[cycle-1] = true;
}

void runProblem(const vector<string> problemFile, function<void(int, int)> perCycle) {
    int cycle = 1; int reg = 1;
    for(int i = 0; i < problemFile.size(); i++) {
        string call = problemFile[i];

        perCycle(cycle, reg);

        if(call != "noop") {
            perCycle(cycle+1, reg);
            cycle++;
            reg += addx(call);
        }
        cycle++;
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
    int signal_strength = 0;
    set<int> cycles = {20, 60, 100, 140, 180, 220};
    auto sumStrength = [&signal_strength, &cycles] (int cycle, int reg) {
        if(inSet(cycle, cycles)) signal_strength += cycle*reg;
    };
    runProblem(problemFile, sumStrength);
    return signal_strength;
}

void problem2(const vector<string> problemFile) {
    bool screen[width*height] = { 0 };
    auto blitScreen = [&screen] (int cycle, int reg) {
        blit(screen, cycle, reg);
    };
    runProblem(problemFile, blitScreen);
    print(screen);
}

int main() {
    vector<string> problemFile = loadProblemVector(10);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl; problem2(problemFile);
}
