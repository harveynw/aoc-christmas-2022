//
// Created by Harvey Temporary on 04/12/2022.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
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
        std::stringstream s_day;
        s_day << std::setw(2) << std::setfill('0') << day;
        std::ifstream f("../data/input" + s_day.str() + ".txt");
        if(!f)
        {
            std::cerr << "ERROR: Cannot open problem file" << std::endl;
            exit(1);
        }

        std::string line;
        while (std::getline(f,line))
        {
            problem.push_back(line);
        }
    }
    catch(const std::exception& ex)
    {
        std::cerr << "ERROR: Exception loading problem file, '" << ex.what() << std::endl;
        exit(1);
    }
    return problem;
}


#endif //AOC_CHRISTMAS_2022_PROBLEM_H
