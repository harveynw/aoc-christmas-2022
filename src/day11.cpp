//
// Created by Harvey Temporary on 04/12/2022.
//

#include "problem.h"
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>
#include <regex>

using namespace std;

struct Monkey {
    vector<int64_t> items;
    function<int64_t(int64_t)> operation;
    int64_t divisibleByTest;
    int ifTrueIdx;
    int ifFalseIdx;
    int64_t itemInspections;
};

regex START_EXPR( R"(\s{2}Starting items:\s([\d+,\s|\s*]+))" );
regex OPERATION_EXPR(R"(\s{2}Operation:\snew\s=\s([\w\d]+)\s([*|+])\s([\w\d]+))");
regex TEST_EXPR(R"(\s{2}Test:\sdivisible\sby\s(\d+))");
regex IF_TRUE_EXPR(R"(\s{4}If\strue:\sthrow\sto\smonkey\s(\d+))");
regex IF_FALSE_EXPR(R"(\s{4}If\sfalse:\sthrow\sto\smonkey\s(\d+))");

void parseItems(const string& s, vector<int64_t> &v) {
    v.clear();
    stringstream ss(s); string item;
    while (std::getline(ss, item, ','))
        v.push_back((int64_t) stoi(item));
}

Monkey* parseMonkey(const vector<string>& def) {
    auto *monkey = new Monkey;

    // Parse initial items
    smatch start_sm; regex_match (def[1],start_sm,START_EXPR);
    parseItems(start_sm.str(1), monkey->items);

    // Parse the operation
    smatch op_sm; regex_match (def[2],op_sm,OPERATION_EXPR);
    string x = op_sm.str(1); string y = op_sm.str(3);
    string op = op_sm.str(2);
    monkey->operation = [x, y, op] (int64_t old) {
        if(x == "old" && y == "old") {
            return op == "+" ? old * 2 : old * old;
        } else if(x == "old") {
            return op == "+" ? old + (int64_t) stoi(y) : old * (int64_t) stoi(y);
        } else if(y == "old") {
            return op == "+" ? old + (int64_t) stoi(x) : old * (int64_t) stoi(x);
        }
    };

    // Parse test
    smatch div_sm; regex_match (def[3],div_sm,TEST_EXPR);
    smatch true_to_sm; regex_match(def[4], true_to_sm, IF_TRUE_EXPR);
    smatch false_to_sm; regex_match(def[5], false_to_sm, IF_FALSE_EXPR);

    monkey->divisibleByTest = stoi(div_sm.str(1));
    monkey->ifTrueIdx = stoi(true_to_sm.str(1));
    monkey->ifFalseIdx = stoi(false_to_sm.str(1));
    monkey->itemInspections = 0;

    return monkey;
}

int64_t shenanigans(const vector<string>& problemFile, int n_rounds, int problem) {
    // Parse
    vector<Monkey *> monkeys;
    //vector<int> mods;
    for(int i = 0; i+5 < problemFile.size(); i+=7) {
        vector<string> def(problemFile.begin() + i, problemFile.begin() + i + 6);
        Monkey *m = parseMonkey(def);
        monkeys.push_back(m);
    }

    int64_t mod = 1; // mod all the coprime divisors
    for(auto m : monkeys)
        mod *= m->divisibleByTest;

    // Do
    vector<int64_t> inspections;
    for(int round = 0; round < n_rounds; round++) {
        int m_idx = 0;
        for (auto monkey: monkeys) {
            for (int i = 0; i < monkey->items.size(); i++) {
                int64_t item = monkey->operation(monkey->items[i]);
                item = problem == 1 ? item/3 : item % mod;
                int idx = (item % monkey->divisibleByTest == 0) ? monkey->ifTrueIdx : monkey->ifFalseIdx;
                monkeys[idx]->items.push_back(item);
                monkey->itemInspections += 1;
            }
            monkey->items.clear();
            if(round==n_rounds-1)
                inspections.push_back(monkey->itemInspections);
            m_idx++;
        }
    }

    sort(inspections.begin(), inspections.end(), [](int64_t i, int64_t j) { return (i > j); });

    return inspections[0]*inspections[1];
}

int problem1(const vector<string>& problemFile) {
    return shenanigans(problemFile, 20, 1);
}

int64_t problem2(const vector<string> problemFile) {
    return shenanigans(problemFile, 10000, 2);
}

int main() {
    vector<string> problemFile = loadProblemVector(11);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}
