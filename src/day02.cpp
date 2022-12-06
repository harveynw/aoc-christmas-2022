//
// Created by Harvey Temporary on 04/12/2022.
//

#include "problem.h"
#include <iostream>
#include <vector>

using namespace std;

const char OP_ROCK = 'A';
const char OP_PAPER = 'B';
const char OP_SCISSORS = 'C';

/** ROUND 1 **/
const char ROCK = 'X';
const char PAPER = 'Y';
const char SCISSORS = 'Z';

/** ROUND 2 **/
const char OUTCOME_LOSE = 'X';
const char OUTCOME_DRAW = 'Y';
const char OUTCOME_WIN = 'Z';


int outcome(char opponent, char you) {
    int score = 0;

    if(you==ROCK && opponent==OP_SCISSORS) score += 6;
    if(you==SCISSORS && opponent==OP_PAPER) score += 6;
    if(you==PAPER && opponent==OP_ROCK) score += 6;

    if(you==ROCK && opponent==OP_ROCK) score += 3;
    if(you==SCISSORS && opponent==OP_SCISSORS) score += 3;
    if(you==PAPER && opponent==OP_PAPER) score += 3;

    if(you==ROCK) score += 1;
    if(you==PAPER) score += 2;
    if(you==SCISSORS) score += 3;

    return score;
}

int outcome_predetermined(char opponent, char intention) {
    // Sort to win, draw, lose
    int outcomes[] = {outcome(opponent, ROCK), outcome(opponent, PAPER), outcome(opponent, SCISSORS)};
    sort(outcomes, outcomes + sizeof(outcomes)/sizeof(outcomes[0]));

    if(intention == OUTCOME_LOSE) return outcomes[0];
    if(intention == OUTCOME_DRAW) return outcomes[1];
    if(intention == OUTCOME_WIN) return outcomes[2];
    return -1;
}

int problem1(const std::list<std::string> problemFile) {
    int totalScore = 0;
    for(auto line : problemFile) {
        totalScore += outcome(line[0], line[2]);
    }
    return totalScore;
}

int problem2(const std::list<std::string> problemFile) {
    int totalScore = 0;
    for(auto line : problemFile) {
        totalScore += outcome_predetermined(line[0], line[2]);
    }
    return totalScore;
}

int main() {
    std::list<std::string> problemFile = loadProblem(2);

    // Problem 1
    std::cout << "First answer:" << std::endl << problem1(problemFile) << std::endl;

    // Problem 2
    std::cout << "Second answer:" << std::endl << problem2(problemFile) << std::endl;
}
