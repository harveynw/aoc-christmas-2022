//
// Created by Harvey Temporary on 04/12/2022.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <exception>
#include <cerrno>
#include <cstdlib>

#ifndef AOC_CHRISTMAS_2022_PROBLEM_H
#define AOC_CHRISTMAS_2022_PROBLEM_H


std::list<std::string> loadProblem(int day) {
    std::list<std::string> problem;
    try
    {
        std::ifstream f("data/input.txt");

        if(!f)
        {
            std::cerr << "ERROR: Cannot open 'teste.txt'!" << std::endl;
            exit(1);
        }
        std::string line;
        std::list<std::string> mylist;

        while (std::getline(f,line))
        {
            mylist.push_back(line);
            std::cout << mylist.back() << std::endl;
        }
    }
    catch(const std::exception& ex)
    {
        std::cerr << "Exception: '" << ex.what() << "'!" << std::endl;
        exit(1);
    }
    return problem;
}


#endif //AOC_CHRISTMAS_2022_PROBLEM_H
