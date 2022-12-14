//
// Created by Harvey Temporary on 04/12/2022.
//

#include "problem.h"
#include <iostream>
#include <utility>
#include <vector>
#include <regex>

using namespace std;

struct Line {
    vector<int> from;
    vector<int> to;
};

regex LINE_EXPR( "(\\d+),(\\d+)" );
typedef vector<char> Row;
typedef vector<Row> Grid;

vector<Line> parseLine(const string line) {
    vector<string> defs;
    string s;
    for(int i = 0; i < line.length(); i++) {
        if(line.substr(i, 4) == " -> ") {
            i += 3;
            defs.push_back(s);
            s.clear();
            continue;
        }
        s.push_back(line[i]);
    }
    defs.push_back(s);

    vector<Line> lines;
    smatch sm1; smatch sm2;
    for(int i = 1; i < defs.size(); i++) {
        regex_match (defs[i-1],sm1,LINE_EXPR);
        regex_match (defs[i],sm2,LINE_EXPR);
        struct Line l = {
                {stoi(sm1.str(2)), stoi(sm1.str(1))},
                {stoi(sm2.str(2)), stoi(sm2.str(1))}
        };
        lines.push_back(l);
    }

    return lines;
}

vector<Line> parseProblem(const vector<string> problemFile) {
    vector<Line> lines;
    for(const auto& line : problemFile) {
        auto parsedLines = parseLine(line);
        lines.insert(lines.end(), parsedLines.begin(), parsedLines.end());
    }
    return lines;
}

void initGrid(Grid &grid, int max_i, int max_j) {
    for(int i = 0; i <= max_i; i++) {
        grid.emplace_back();
        for(int j = 0; j <= max_j; j++)
            grid[i].push_back('.');
    }
}

void printGrid(Grid &grid) {
    for(auto row : grid) {
        for(auto c : row)
            cout << c;
        cout << endl;
    }
}

void pasteLine(Grid &grid, Line &line) {
    int i1 = line.from[0]; int i2 = line.to[0];
    int j1 = line.from[1]; int j2 = line.to[1];
    if(i1 != i2) { // Vertical line
        for(int i = i1; i1 < i2 ? i <= i2 : i >= i2; i1 < i2 ? i++ : i--)
            grid[i][j1] = '#';
    } else { // Horizontal line
        for(int j = j1; j1 < j2 ? j <= j2 : j >= j2; j1 < j2 ? j++ : j--)
            grid[i1][j] = '#';
    }
}

bool dropUnitSand(Grid &grid, int max_i) {
    int i = 0; int j = 500;
    while(true) {
        if(grid[i][j] == 'o')
            return true; // blocked
        else if(i == max_i)
            return true; // void
        if(grid[i+1][j] == '.')
            i++;
        else if(grid[i+1][j-1] == '.') {
            i++;
            j--;
        } else if(grid[i+1][j+1] == '.') {
            i++;
            j++;
        } else {
            grid[i][j] = 'o';
            return false;
        }
    }
}

int problem1(const vector<string> problemFile) {
    auto lines = parseProblem(problemFile);

    int max_i = 0; int max_j = 0;
    for(auto l : lines) {
        max_i = max(max_i, max(l.from[0], l.to[0]));
        max_j = max(max_j, max(l.from[1], l.to[1]));
    }

    // create grid
    vector<vector<char>> grid;
    initGrid(grid, max_i, max_j);
    for(auto l : lines)
        pasteLine(grid, l);

    int n_sand = 0;
    while(!dropUnitSand(grid, max_i))
        n_sand++;

    return n_sand;
}

int problem2(const vector<string> problemFile) {
    auto lines = parseProblem(problemFile);

    int max_i = 0; int max_j = 0;
    for(auto l : lines) {
        max_i = max(max_i, max(l.from[0], l.to[0]));
        max_j = max(max_j, max(l.from[1], l.to[1]));
    }

    // add floor
    struct Line floor = { {max_i+2, 0},{max_i+2, max_j+100} };
    lines.push_back(floor);

    // create grid
    vector<vector<char>> grid;
    initGrid(grid, max_i+2, max_j+100); // wide enough this time
    for(auto l : lines)
        pasteLine(grid, l);

    int n_sand = 0;
    while(!dropUnitSand(grid, max_i+2))
        n_sand++;

    return n_sand;
}

int main() {
    vector<string> problemFile = loadProblemVector(14);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}
