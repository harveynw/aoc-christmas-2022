//
// Created by Harvey Temporary on 04/12/2022.
//

#include "problem.h"
#include <iostream>
#include <utility>
#include <vector>
#include <set>
#include <regex>

using namespace std;

struct State {
    vector<int> H;
    vector<int> T;
    set<vector<int>> visited;
};

int sgn(int x) {
    return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

bool tail_follow(State &state) {
    vector<int> diff = {state.T[0] - state.H[0], state.T[1] - state.H[1]};

    if(max(abs(diff[0]), abs(diff[1])) < 2) return false; // T doesn't need moving

    if(diff[0] == 0 || diff[1] == 0) {
        // Directly above/below/to the side
        state.T[0] += sgn(diff[0]) * -1;
        state.T[1] += sgn(diff[1]) * -1;
    } else {
        // Diagonal move logic
        state.T[0] += (sgn(diff[0]) * -1);
        state.T[1] += (sgn(diff[1]) * -1);
    }

    return true;
}

void apply_move(State &state, char dir) {
    if(dir == 'R') state.H[0] += 1;
    if(dir == 'L') state.H[0] -= 1;
    if(dir == 'U') state.H[1] += 1;
    if(dir == 'D') state.H[1] -= 1;

    if(tail_follow(state)) state.visited.emplace(state.T);
}

void parse_move(string line, char &dir, int &amount) {
    regex str_expr( "(\\w) (\\d+)" );
    smatch sm;
    regex_match (line,sm,str_expr);

    dir = sm.str(1)[0];
    amount = stoi(sm.str(2));
}

int problem1(const vector<string> problemFile) {
    // just move+follow
    State state = {vector<int>{0, 0}, vector<int>{0, 0}, set<vector<int>>()};
    state.visited.emplace(state.T);

    for(auto line : problemFile) {
        char dir; int amount;
        parse_move(line, dir, amount);

        for(int i = 0; i < amount; i++) {
            apply_move(state, dir);
        }

    }

    return state.visited.size();
}

int problem2(const vector<string> problemFile) {
    // move+follow+...+follow
    vector<State> knots;
    int n = 10;
    int n_states = n-1; // State tracks two knots

    // Create rope
    for(int i = 0; i < n_states; i++) {
        State knot = {vector<int>{0, 0}, vector<int>{0, 0}, set<vector<int>>()};
        if(i == n_states-1) knot.visited.emplace(knot.T); // include origin
        knots.push_back(knot);
    }

    // Simulate rope
    for(auto line : problemFile) {
        char dir; int amount;
        parse_move(line, dir, amount);

        for(int steps = 0; steps < amount; steps++) {
            for(int i = 0; i < n_states; i++) {
                if (i == 0) {
                    // Head
                    apply_move(knots[0], dir);
                    knots[1].H = knots[0].T;
                } else {
                    if(!tail_follow(knots[i])) break;
                    if (i == n_states-1) {
                        // Tail
                        knots[i].visited.emplace(knots[i].T);
                        continue;
                    }
                }
                knots[i+1].H = knots[i].T;
            }

        }
    }

    return knots[n_states-1].visited.size();
}

int main() {
    vector<string> problemFile = loadProblemVector(9);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}
