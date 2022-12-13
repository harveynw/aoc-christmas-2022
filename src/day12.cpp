//
// Created by Harvey Temporary on 04/12/2022.
//

#include "problem.h"
#include <iostream>
#include <utility>
#include <vector>
#include <regex>
#include <queue>

using namespace std;

class Vertex {
public:
    int coord[2] = {0};
    int height = 0;
    bool explored = false;
    bool goal = false;
    Vertex *parent = nullptr;

    Vertex(int i, int j) {
        this->coord[0] = i;
        this->coord[1] = j;
    }
};

int height(char c) {
    int x = c;
    return (x - 97) + 1;
}

bool valid_jump(Vertex *from, Vertex *to) {
    return (to->height - from->height) <= 1;
}

vector<Vertex *> adjacentVertices(const vector<vector<Vertex *>> &grid, Vertex* &v) {
    vector<Vertex *> adj;
    int i = v->coord[0]; int j = v->coord[1];
    int h = grid.size(); int w = grid[0].size();
    if(i+1 < h && valid_jump(v, grid[i+1][j])) adj.push_back(grid[i+1][j]);
    if(i-1 > -1 && valid_jump(v, grid[i-1][j])) adj.push_back(grid[i-1][j]);
    if(j+1 < w && valid_jump(v, grid[i][j+1])) adj.push_back(grid[i][j+1]);
    if(j-1 > -1 && valid_jump(v, grid[i][j-1])) adj.push_back(grid[i][j-1]);
    return adj;
}

void parseProblem(vector<vector<Vertex *>> &grid, Vertex* &root, const vector<string> problemFile) {
    // grid and root are populated by problemFile
    grid.clear();
    for(int i = 0; i < problemFile.size(); i++) {
        grid.push_back(vector<Vertex *>());
        for(int j = 0; j < problemFile[i].length(); j++) {
            auto *v = new Vertex(i, j);
            char c = problemFile[i][j];
            if(c == 'S') {
                root = v;
                root->height = height('a');
            } else if(c == 'E') {
                v->goal = true;
                v->height = height('z');
            } else
                v->height = height(c);
            grid[i].push_back(v);
        }
    }
}

Vertex* BFS(Vertex *root, const vector<vector<Vertex *>> &grid) {
    // https://en.wikipedia.org/wiki/Breadth-first_search
    queue<Vertex *> Q;
    root->explored = true;
    Q.push(root);

    while(!Q.empty()) {
        auto v = Q.front();
        Q.pop();

        if(v->goal)
            return v;

        vector<Vertex *> adj = adjacentVertices(grid, v);
        for(Vertex *w : adj) {
            if(!w->explored) {
                w->explored = true;
                w->parent = v;
                Q.push(w);
            }
        }
    }
    return nullptr;
}

void clear_grid(vector<vector<Vertex *>> &grid) {
    for(auto &row : grid) {
        for(auto v : row) {
            v->explored = false;
            v->parent = nullptr;
        }
    }
}

int min_distance(vector<vector<Vertex *>> grid, Vertex *root) {
    auto E = BFS(root, grid);
    if(E == nullptr) return INT_MAX;

    int count = 1;
    while(E->parent != root) {
        count++;
        E = E->parent;
    }

    clear_grid(grid);
    return count;
}

int problem1(const vector<string> problemFile) {
    vector<vector<Vertex *>> grid;
    Vertex *root;
    parseProblem(grid, root, problemFile);

    return min_distance(grid, root);
}

int problem2(const vector<string> problemFile) {
    // Every possibility, super slow -> Dijkstra would have been better
    int shortest = INT_MAX;
    vector<vector<Vertex *>> grid;
    Vertex *root;
    parseProblem(grid, root, problemFile);

    for(auto &row : grid) {
        for(auto v : row) {
            if(v->height==1)
                shortest = min(min_distance(grid, v), shortest);
        }
    }
    return shortest;
}

int main() {
    vector<string> problemFile = loadProblemVector(12);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}
