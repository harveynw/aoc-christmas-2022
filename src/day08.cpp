//
// Created by Harvey Temporary on 04/12/2022.
//

#include "problem.h"
#include <iostream>
#include <utility>
#include <vector>
#include <regex>

using namespace std;

void parseProblemFile(const vector<string> problemFile, int** &grid, int &height, int &width) {
    height = problemFile.size(); width = problemFile[0].size();
    grid = new int*[height];

    for(int i = 0; i < height; i++) {
        grid[i] = new int[width];
        for(int j = 0; j < width; j++) {
            grid[i][j] = stoi(problemFile[i].substr(j, 1));
        }
    }
}

void problem1Scan(int ** grid, bool** visible, const vector<int> &vertical, const vector<int> &horizontal,
                  bool scanAcross) {
    for(auto i : (scanAcross ? vertical : horizontal)) {
        int max = -1;
        for(auto j : (scanAcross ? horizontal : vertical)) {
            int k = scanAcross ? i : j; int l = scanAcross ? j : i;
            if(grid[k][l] > max) {
                visible[k][l] = true;
                max = grid[k][l];
            }
        }
    }
}

int sumBoolGrid(bool ** grid, int height, int width) {
    int sum = 0;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(grid[i][j]) sum++;
        }
    }
    return sum;
}

int scenicScore(int ** grid, int height, int width, int i, int j) {
    int score = 1; int viewingHeight = grid[i][j];
    // top
    for(int k = 0; k+i < height; k++) {
        if(grid[k+i][j] >= viewingHeight && k > 0) {
            score *= k; break;
        }
        if(k+i == height-1) score *= k; // edge
    }
    // bottom
    for(int k = 0; i-k > -1; k++) {
        if(grid[i-k][j] >= viewingHeight && k > 0) {
            score *= k; break;
        }
        if(i-k == 0) score *= k; // edge
    }
    // left
    for(int l = 0; j+l < width; l++) {
        if(grid[i][j+l] >= viewingHeight && l > 0) {
            score *= l; break;
        }
        if(j+l == width-1) score *= l; // edge
    }
    // right
    for(int l = 0; j-l > -1; l++) {
        if(grid[i][j-l] >= viewingHeight && l > 0) {
            score *= l; break;
        }
        if(j-l == 0) score *= l; // edge
    }

    return score;
}

int problem1(const vector<string> problemFile) {
    int **grid; int height; int width;
    parseProblemFile(problemFile, grid, height, width);

    // Result grid
    bool **visible = new bool *[height];
    for(int i = 0; i < height; i++) {
        visible[i] = new bool[width];
        for(int j = 0; j < width; j++) visible[i][j] = false;
    }

    vector<int> vertical(height); vector<int> horizontal(width);

    // From left
    generate(vertical.begin(), vertical.end(), [n = 0] () mutable { return n++; });
    generate(horizontal.begin(), horizontal.end(), [n = 0] () mutable { return n++; });
    problem1Scan(grid, visible, vertical, horizontal, true);

    // From right
    generate(horizontal.begin(), horizontal.end(), [n = width-1] () mutable { return n--; });
    problem1Scan(grid, visible, vertical, horizontal, true);

    // From top
    problem1Scan(grid, visible, vertical, horizontal, false);

    // From bottom
    generate(vertical.begin(), vertical.end(), [n = height-1] () mutable { return n--; });
    problem1Scan(grid, visible, vertical, horizontal, false);

    return sumBoolGrid(visible, height, width);
}

int problem2(const vector<string> problemFile) {
    int **grid; int height; int width;
    parseProblemFile(problemFile, grid, height, width);

    int max = 0;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            int score = scenicScore(grid, height, width, i, j);
            if(score > max) max = score;
        }
    }

    return max;
}

int main() {
    vector<string> problemFile = loadProblemVector(8);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}
