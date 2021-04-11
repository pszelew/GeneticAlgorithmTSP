
#ifndef GA_HH
#define GA_HH

#include <vector>
#include <string>
#include <climits>
#include <iostream>
#include <random>
#include <memory>
#include <algorithm>
#include "Population.hh"
#include "Task.hh"

class GA
{
    public:
        GA(Task toSolve, int popSize, double pX, double pM, int tours, int iters, bool storeMetrics = false);
        double solve();
        int getSolutionLen(){return bestVal;}
        std::vector<int> getSolution() {return best;}
        const std::vector<double> & getBestValPerPopulation() {return bestValPerPopulation;}
        const std::vector<double> & getWorstValPerPopulation() {return worstValPerPopulation;}
        const std::vector<double> & getAvgValPerPopulation() {return avgValPerPopulation;}

    private:
        Task toSolve;
        std::shared_ptr<Population> pop;
        int tours;
        int iters;

        std::random_device device;
        std::mt19937 rng;

        std::bernoulli_distribution pXDistribution;
        std::bernoulli_distribution pMDistribution;
        std::uniform_int_distribution<int> cutsDistribution;

        int bestVal;
        std::vector<int> best;
        
        // Metrics
        int storeMetrics;
        std::vector<double> bestValPerPopulation;
        std::vector<double> worstValPerPopulation;
        std::vector<double> avgValPerPopulation;
};

#endif