//
// Created by Harvey Temporary on 04/12/2022.
//

#include "problem.h"
#include <iostream>
#include <utility>
#include <vector>
#include <regex>
#include <map>

using namespace std;

class Directory {
public:
    int get_size();
    Directory *find_root();
    Directory *get_subdir(const string& name);
    void add_file(string name, int size);
    void populate_subdirs(vector<Directory *> *subdirs);

    map<string, int> files;
    map<string, Directory *> children;
    Directory *parent;
};

int Directory::get_size() {
    int size = 0;

    // Sum files
    for(auto &v : this->files) size += v.second;

    // Sum directories
    for(auto &dir : this->children) size += dir.second->get_size();

    return size;
}

Directory *Directory::find_root() {
    Directory *current = this;
    while(current->parent != nullptr) {
        current = current->parent;
    }
    return current;
}

void Directory::populate_subdirs(vector<Directory *> *subdirs) {
    subdirs->push_back(this);
    for(auto &dir : this->children) {
        dir.second->populate_subdirs(subdirs);
    }
}

Directory *Directory::get_subdir(const string& name) {
    if (this->children.count(name) == 0) { // if new, create
        auto *newDir = new Directory();
        newDir->parent = this;
        children.insert(make_pair(name, newDir));
        return newDir;
    } else
        return children[name];
}

void Directory::add_file(string name, int size) {
    files.insert(make_pair(name, size));
}

Directory * parseProblemFile(const vector<string> problemFile) {
    // Returns ptr to root directory
    auto *root = new Directory();
    root->parent = nullptr;
    Directory *currentDir = root;

    for(const auto& line : problemFile) {
        if(line.rfind('$', 0) == 0) {
            if(line == "$ cd /") {
                // Root
                currentDir = currentDir->find_root();
            } else if (line == "$ cd ..") {
                // Up dir
                currentDir = currentDir->parent;
            } else if (line.rfind("$ cd ", 0) == 0) {
                // CD subdir
                string name = line.substr(5);
                currentDir = currentDir->get_subdir(name);
            } else if (line == "$ ls") {
                // list
                continue;
            }
        } else {
            if(line.rfind("dir", 0) == 0) continue;
            // Not command, file
            regex str_expr( R"(^(\d+) ([\w|\.]+))" );
            smatch sm;
            regex_match (line,sm,str_expr);

            int size = stoi(sm.str(1));
            string name = sm.str(2);
            currentDir->add_file(name, size);
        }
    }

    return root;
}

int problem1(const vector<string> problemFile) {
    Directory *root = parseProblemFile(problemFile);

    // Count sizes of relevant directories
    vector<Directory *> allDirs;
    root->populate_subdirs(&allDirs);
    int sum = 0;
    for(auto dir : allDirs) {
        int size = dir->get_size();
        if(size <= 100000) sum += size;
    }
    return sum;
}

int problem2(const vector<string> problemFile) {
    Directory *root = parseProblemFile(problemFile);

    int root_size = root->get_size();
    int min_size = 30000000 - (70000000 - root_size);

    vector<Directory *> allDirs;
    root->populate_subdirs(&allDirs);

    int d = root_size; Directory *candidate = nullptr;
    for(auto dir : allDirs) {
        int candidate_d = dir->get_size();
        if(candidate_d >= min_size && candidate_d < d) {
            d = candidate_d;
            candidate = dir;
        }
    }
    return candidate->get_size();
}

int main() {
    vector<string> problemFile = loadProblemVector(7);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}
