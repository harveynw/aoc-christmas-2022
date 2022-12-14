//
// Created by Harvey Temporary on 04/12/2022.
//

#include "problem.h"
#include <iostream>
#include <utility>
#include <vector>
#include <regex>

using namespace std;

class Value {
public:
    bool isArray = false;
    int v;
    vector<Value *> children;

    Value(string def);
    Value(Value *v);
    int cmp(Value *v);
    void print();
};

void Value::print() {
    if(isArray) {
        cout << "[";
        for(auto c : this->children) {
            c->print();
            cout << ",";
        }
        cout << "]";
    } else {
        cout << this->v;
    }
}

vector<Value *> parse_array(string def) {
    def = def.substr(1, def.length()-2); // remove outer brackets
    vector<Value *> v;

    int bracket_depth = 0;
    string s = "";
    for(auto c : def) {
        if (c == ',' && bracket_depth == 0) {
            v.push_back(new Value(s));
            s = "";
            continue;
        } else if (c == '[')
            bracket_depth++;
        else if(c == ']')
            bracket_depth--;
        s.push_back(c);
    }
    if(s.size() > 0)
        v.push_back(new Value(s));
    return v;
}

Value::Value(string def) {
    this->isArray = def[0] == '[';

    if(this->isArray) {
        this->children = parse_array(def);
    } else {
        this->v = stoi(def);
    }
}

Value::Value(Value *v) {
    this->isArray = true;
    this->children = {v};
}

int Value::cmp(Value *val) {
    // Returns 0 = unresolved, -1 = not in right order, 1 = in right order
    if(!this->isArray && !val->isArray) {
        if(this->v == val->v)
            return 0;
        return this->v < val->v ? 1 : -1;
    }

    // Remaining cases
    if(this->isArray && val->isArray) {
        int s1 = this->children.size(); int s2 = val->children.size();
        for(int i = 0; true; i++) {
            if(i == s1 && i < s2) return 1;
            if(i == s2 && i < s1) return -1;
            if(i == s1 && i == s2) return 0;

            int result = this->children[i]->cmp(val->children[i]);
            if(result != 0)
                return result;
        }
    } else if(this->isArray) {
        // val is int, wrap in array
        auto *new_val = new Value(val);
        return this->cmp(new_val);
    } else {
        // this is int, wrap in array
        auto *new_val = new Value(this);
        return new_val->cmp(val);
    }
}

int problem1(const vector<string> problemFile) {
    int indices_sum = 0;
    for(int line = 0; line < problemFile.size(); line+=3) {
        auto *v1 = new Value(problemFile[line]);
        auto *v2 = new Value(problemFile[line+1]);

        int result = v1->cmp(v2);
        if(result == 1)
            indices_sum += (line/3 + 1);
    }

    return indices_sum;
}

int problem2(const vector<string> problemFile) {
    Value *div_1 = new Value("[[2]]");
    Value *div_2 = new Value("[[6]]");

    vector<Value *> packets = { div_1, div_2 };

    for(int line = 0; line < problemFile.size(); line+=3) {
        packets.push_back(new Value(problemFile[line]));
        packets.push_back(new Value(problemFile[line + 1]));
    }

    sort(packets.begin(), packets.end(), [](Value *v1, Value *v2) {
        return v1->cmp(v2) == 1;
    });

    int div1_line; int div2_line;
    for(int i = 0; i < packets.size(); i++) {
        // packets[i]->print(); cout << endl;
        if(packets[i] == div_1) div1_line = i+1;
        if(packets[i] == div_2) div2_line = i+1;
    }

    return div1_line * div2_line;
}

int main() {
    vector<string> problemFile = loadProblemVector(13);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}
