//
// Created by Harvey Temporary on 04/12/2022.
//

#include "problem.h"
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

struct crane_move {
    int amount;
    int from;
    int to;
};

void parseProblem(const vector<string> problemFile, vector<vector<char>> *stacks, vector<crane_move> *moves) {
    vector<string> stacksDef;
    vector<string> movesDef;

    // Split problem file
    int i = 0;
    while(true) {
        if(problemFile[i] == "") {
            stacksDef = vector<string>(problemFile.begin(), problemFile.begin() + i);
            movesDef = vector<string>(problemFile.begin() + i + 1, problemFile.end());
            break;
        }
        i++;
    }

    // Parse stacks
    int n_stacks = (stacksDef.back().length()+1)/4;
    for(int k = 0; k < n_stacks; k++) stacks->push_back(vector<char>());
    stacksDef.pop_back();
    for(auto line : stacksDef) {
        for (int cursor = 1; cursor < line.length(); cursor += 4) {
            char item = line[cursor];
            if (item != ' ') {
                stacks->at((cursor-1)/4).push_back(item);
            }
        }
    }
    // (last is first)
    for(int k = 0; k < n_stacks; k++) reverse(stacks->at(k).begin(), stacks->at(k).end());

    // Parse moves
    for(auto line : movesDef) {
        regex str_expr( "move (\\d+) from (\\d+) to (\\d+)" );
        smatch sm;
        regex_match (line,sm,str_expr);

        crane_move move = {
                stoi(sm.str(1)),
                stoi(sm.str(2)),
                stoi(sm.str(3))
        };
        moves->push_back(move);
    }
}

void performMove(crane_move move, vector<vector<char>> *stacks) {
    int from = move.from-1; int to = move.to-1; // index
    for(int i = 0; i < move.amount; i++) {
        stacks->at(to).push_back(stacks->at(from).back());
        stacks->at(from).pop_back();
    }
}

void performMove9001(crane_move move, vector<vector<char>> *stacks) {
    int from = move.from-1; int to = move.to-1; // index

    vector<char> pickup(
            stacks->at(from).end() - move.amount,
            stacks->at(from).end()
            );

    // Remove
    stacks->at(from).resize(
            stacks->at(from).size() - move.amount
            );

    // Place
    stacks->at(to).insert(
            stacks->at(to).end(),
            pickup.begin(),
            pickup.end()
            );
}

string problem1(const vector<string> problemFile) {
    vector<vector<char>> stacks; vector<crane_move> moves;

    parseProblem(problemFile, &stacks, &moves);

    for(crane_move move : moves) {
        performMove(move, &stacks);
    }

    string result;
    for(vector<char> stack : stacks) {
        result.push_back(stack.back());
    }
    return result;
}

string problem2(vector<string> problemFile) {
    vector<vector<char>> stacks; vector<crane_move> moves;

    parseProblem(problemFile, &stacks, &moves);

    for(crane_move move : moves) {
        performMove9001(move, &stacks);
    }

    string result;
    for(vector<char> stack : stacks) {
        result.push_back(stack.back());
    }
    return result;
}

int main() {
    vector<string> problemFile = loadProblemVector(5);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}
