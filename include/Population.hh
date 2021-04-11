#ifndef POPULATION_HH
#define POPULATION_HH

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <climits>
#include <random>

class Population
{
    public:
        Population(int popSize, int taskSize);
        void initPopulRandom();
        std::vector<double> calcPopulLen (const std::vector<std::vector<double>> & distMatrix);
        double calcOneLen (int index, const std::vector<std::vector<double>> & distMatrix);
        static double calcOneLenCheck (std::vector<int> toCheck, const std::vector<std::vector<double>> & distMatrix);
        int getPopulSize() const {return populSize;}
        std::vector<std::vector<int>> & getPopulMod(){return popul;}
        std::vector<std::vector<int>> getPopul(){return popul;}
        static std::vector<int> mutInversion(std::vector<int> toMutate, int start, int end);
        std::vector<int> crossCx(int idx1, int idx2, int startIdx=-1, int chooseLeading=-1);
        int tournament(int tour, const std::vector<std::vector<double>> & distMatrix);
    private:
        int populSize;
        int taskSize;
        std::random_device device;
        std::mt19937 rng;
        std::vector<std::vector<int>> popul;
        
};

#endif