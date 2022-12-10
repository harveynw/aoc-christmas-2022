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

regex LINE_EXPR( "(\\w) (\\d+)" );

int sgn(int x) {
    return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

bool apply_follow(State &state) {
    int dx = state.T[0] - state.H[0]; int dy = state.T[1] - state.H[1];

    if(max(abs(dx), abs(dy)) < 2) return false; // T doesn't need moving

    state.T[0] -= sgn(dx);
    state.T[1] -= sgn(dy);
    return true;
}

void apply_move(State &state, char dir) {
    if(dir == 'R') state.H[0] += 1;
    if(dir == 'L') state.H[0] -= 1;
    if(dir == 'U') state.H[1] += 1;
    if(dir == 'D') state.H[1] -= 1;
}

void move_rope(vector<State> &states, char dir) {
    int n_states = states.size();
    for(int i = 0; i < n_states; i++) {
        if(i == 0) apply_move(states[i], dir); // Head
        if(!apply_follow(states[i])) break; // Successive knots

        if (i == n_states-1) {
            states[i].visited.emplace(states[i].T); // Tail
        } else {
            states[i+1].H = states[i].T; // Update next knot
        }
    }
}

void parse_move(string line, char &dir, int &amount) {
    smatch sm;
    regex_match (line,sm,LINE_EXPR);

    dir = sm.str(1)[0];
    amount = stoi(sm.str(2));
}

int simulate_rope(const vector<string> problemFile, int n_knots) {
    vector<State> knots;
    int n_states = n_knots-1; // State tracks two knots

    // Create rope
    for(int i = 0; i < n_states; i++) {
        State knot = {vector<int>{0, 0}, vector<int>{0, 0}, set<vector<int>>()};
        if(i == n_states-1) knot.visited.emplace(knot.T); // include origin
        knots.push_back(knot);
    }

    // Simulate rope
    for(const auto& line : problemFile) {
        char dir; int amount;
        parse_move(line, dir, amount);

        for(int steps = 0; steps < amount; steps++) move_rope(knots, dir);
    }

    return knots[n_states-1].visited.size();
}

int problem1(const vector<string> problemFile) {
    return simulate_rope(problemFile, 2);
}

int problem2(const vector<string> problemFile) {
    return simulate_rope(problemFile, 10);
}

int main() {
    vector<string> problemFile = loadProblemVector(9);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}
