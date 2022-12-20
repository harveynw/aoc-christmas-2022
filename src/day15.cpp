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

regex LINE_EXPR( R"(Sensor\sat\sx=(-\d+|\d+),\sy=(-\d+|\d+):\sclosest\sbeacon\sis\sat\sx=(-\d+|\d+),\sy=(-\d+|\d+))" );

struct Interval
{
    int low, high;
};

struct IntervalNode
{
    Interval *i;
    IntervalNode *left;
    IntervalNode *right;
public:
    int cardinality();
    bool in(int i);
};

IntervalNode* newNode(Interval i)
{
    auto *temp = new IntervalNode;
    temp->i = new Interval(i);
    temp->left = temp->right = nullptr;
    return temp;
};

IntervalNode* insert(IntervalNode *root, Interval i)
{
    // Base case
    if (root == nullptr)
        return newNode(i);

    // Non overlapping amounts either side of root
    int low_size = max(0, root->i->low - i.low);
    int high_size = max(0, i.high - root->i->high);

    // If lower sub interval, append to left
    if(low_size > 0)
        root->left = insert(root->left, {i.low, min(i.high, root->i->low-1)});

    // If higher sub interval, append to right
    if(high_size > 0)
        root->right = insert(root->right, {max(root->i->high+1, i.low), i.high});

    return root;
}

int IntervalNode::cardinality() {
    int sum = (this->i->high+1) - this->i->low;

    if(this->left != nullptr)
        sum += this->left->cardinality();

    if(this->right != nullptr)
        sum += this->right->cardinality();

    return sum;
}

bool IntervalNode::in(int i) {
    if(i >= this->i->low && i <= this->i->high)
        return true;

    if(i < this->i->low)
        return this->left != nullptr && this->left->in(i);

    if(i > this->i->high)
        return this->right != nullptr && this->right->in(i);
}


struct Coord {
    int x;
    int y;
};

int manhattan_distance(Coord &a, Coord &b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void parse_line(const string &line, Coord &sensor, Coord &beacon) {
    smatch sm; regex_match (line,sm, LINE_EXPR);

    sensor.x = stoi(sm.str(1)); sensor.y = stoi(sm.str(2));
    beacon.x = stoi(sm.str(3)); beacon.y = stoi(sm.str(4));
}

void parseProblem(const vector<string>& problemFile, vector<pair<Coord, Coord>> &sensors_beacons) {
    for(const auto& line : problemFile) {
        Coord s{};
        Coord b{};
        parse_line(line, s, b);
        sensors_beacons.emplace_back(s, b);
    }
}

int problem1(const vector<string> problemFile) {
    vector<pair<Coord, Coord>> sensors_beacons;
    parseProblem(problemFile, sensors_beacons);

    IntervalNode *root = nullptr; set<int> beacons_included_x;
    int y = 2000000;

    for(auto pair : sensors_beacons) {
        if(pair.second.y == y) // Include beacons on y=n
            beacons_included_x.emplace(pair.second.x);

        // Interval on x defined implicitly by (y=n)
        // | s.x - x | + | s.y - y | <= MDIST(s, b)
        int rhs = manhattan_distance(pair.first, pair.second) - abs(pair.first.y - y);
        if(rhs < 0) // No solution for y=n
            continue;
        int x_min = pair.first.x - rhs;
        int x_max = pair.first.x + rhs;
        if(x_max < x_min)
            swap(x_min, x_max);

        root = insert(root, {x_min, x_max});
    }

    if(root == nullptr)
        return 0;

    return root->cardinality() - beacons_included_x.size();
}

int64_t problem2(const vector<string> problemFile) {
    vector<pair<Coord, Coord>> sensors_beacons;
    parseProblem(problemFile, sensors_beacons);

    //int MAX_COORD = 20;
    int MAX_COORD = 4000000;

    IntervalNode *root;
    for(int y = 0; y <= MAX_COORD; y++) {
        root = nullptr;

        for(auto pair : sensors_beacons) {
            // Interval on x defined implicitly by (y=n)
            // | s.x - x | + | s.y - y | <= MDIST(s, b)
            int rhs = manhattan_distance(pair.first, pair.second) - abs(pair.first.y - y);
            if(rhs < 0) // No solution for y=n
                continue;

            int x_min = pair.first.x - rhs; int x_max = pair.first.x + rhs;
            if(x_max < x_min)
                swap(x_min, x_max);
            x_min = max(0, x_min); x_max = min(x_max, MAX_COORD);

            root = insert(root, {x_min, x_max});
        }

        if(root == nullptr)
            continue;

        if(root->cardinality() != MAX_COORD + 1) {
            for(int x = 0; x <= MAX_COORD; x++) {
                if(!root->in(x)) {
                    return 4000000 * ((int64_t) x) + ((int64_t) y);
                }
            }
        }
    }

    return -1;
}


int main() {
    vector<string> problemFile = loadProblemVector(15);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}
