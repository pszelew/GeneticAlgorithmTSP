
#ifndef GREEDY_HH
#define GREEDY_HH

#include <vector>
#include <string>
#include <climits>
#include <iostream>
#include <random>
#include "Task.hh"



class Greedy
{
    public:
        Greedy(Task toSolve, bool random = false);
        double solve();
        vector<int> getSolution(){return solution;}
        double getSolutionLen(){return solutionLen;}
    private:
        Task toSolve;
        vector<int> solution;
        double solutionLen;
        double evaluate();
        int random;
};

#endif