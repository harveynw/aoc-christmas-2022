//
// Created by Harvey Temporary on 04/12/2022.
//

#include "problem.h"
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int itemPriority(char item) {
    int x = item;
    if(x >= 65 && x <= 90) return (x - 65) + 27;
    if(x >= 97 && x <= 122) return (x - 97) + 1;
    return -1;
}

int groupPriority(const vector<string> backpacks) {
    int counts[52] = { };

    for(auto backpack : backpacks) {
        set<char> backpack_items(begin(backpack), end(backpack));
        for(auto item : backpack_items) {
            counts[itemPriority(item) - 1] += 1;
        }
    }

    for(int i = 0; i < 52; i++) {
        if(counts[i] == 3) return i+1; // in all three, return priority
    }
    return -1;
}

int problem1(const vector<string> problemFile) {
    int totalScore = 0;
    for(auto line : problemFile) {
        int l = line.length()/2;
        string first = line.substr(0, l);
        string second = line.substr(l, l);
        for(auto c : first) {
            if(second.find(c) != string::npos) { // is in both
                totalScore += itemPriority(c);
                break;
            }
        }
    }
    return totalScore;
}

int problem2(vector<string> problemFile) {
    int totalCount = 0; int cursor = 0;
    while(cursor < problemFile.size()) {
        vector<string> group = {problemFile.begin() + cursor, problemFile.begin() + cursor + 3};
        totalCount += groupPriority(group);
        cursor += 3;
    }
    return totalCount;
}

int main() {
    vector<string> problemFile = loadProblemVector(3);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}
