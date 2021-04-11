#include "GA.hh"

GA::GA(Task toSolve, int popSize, double pX, double pM, int tours, int iters, bool storeMetrics): 
    toSolve(toSolve), tours(tours), iters(iters),
    pXDistribution(pX), pMDistribution(pM), cutsDistribution(0, toSolve.getTaskSize()-2)
    {
        this->storeMetrics = storeMetrics;
        pop = std::make_shared<Population>(popSize, toSolve.getTaskSize());
        rng = std::mt19937(device());
        toSolve.init();
        pop->initPopulRandom();
    }

double GA::solve()
{
    int popSize = pop->getPopulSize();
    std::shared_ptr<Population> newPop = std::make_shared<Population>(popSize, toSolve.getTaskSize());
    vector<int> toAdd;
    vector<int> best;
    double bestVal=INT_MAX;
    auto distMatrix = toSolve.getDistMatrix();    

    auto lenResults = pop->calcPopulLen(distMatrix);

    auto bestIt = std::min_element(lenResults.begin(), lenResults.end());
    
    best = pop->getPopul()[bestIt - lenResults.begin()];
    bestVal = *bestIt;


    if(this->storeMetrics) // population 0
    {
        this->bestValPerPopulation.push_back(bestVal);

        auto worstIt = std::max_element(lenResults.begin(), lenResults.end());
        this->worstValPerPopulation.push_back(*worstIt);

        double sum = std::accumulate(lenResults.begin(), lenResults.end(), 0.0);
        this->avgValPerPopulation.push_back(sum/lenResults.size());
    }


    for(int i=0;i<iters;i++)
    {
        newPop = std::make_shared<Population>(popSize, toSolve.getTaskSize());

        while (newPop->getPopul().size() != popSize)
        {
            toAdd.clear();
            auto p1 = pop->tournament(tours, distMatrix);
            auto p2 = pop->tournament(tours, distMatrix);

            if(pXDistribution(rng))
            {
                toAdd = pop->crossCx(p1, p2);
            }
            else
            {
                toAdd = pop->getPopul()[p1];
            }

            if(pMDistribution(rng))
            {   
                int a = cutsDistribution(rng);
                int b = cutsDistribution(rng);
                
                if (b > a)
                {
                    toAdd = Population::mutInversion(toAdd, a, b);
                }
                else if (a > b)
                {
                    toAdd = Population::mutInversion(toAdd, b, a);
                }
                
                
            }

            double currVal = Population::calcOneLenCheck(toAdd, distMatrix);

            if(currVal < bestVal)
            {
                bestVal = currVal;
                best = toAdd;
            }

            newPop->getPopulMod().push_back(toAdd);
        }
    
        pop = newPop;

        lenResults = pop->calcPopulLen(distMatrix);

        if(this->storeMetrics) // next populations
        {

            auto bestPopIt = std::min_element(lenResults.begin(), lenResults.end());
            this->bestValPerPopulation.push_back(*bestPopIt);

            auto worstIt = std::max_element(lenResults.begin(), lenResults.end());
            this->worstValPerPopulation.push_back(*worstIt);

            double sum = std::accumulate(lenResults.begin(), lenResults.end(), 0.0);
            this->avgValPerPopulation.push_back(sum/lenResults.size());
        }
    }

    return bestVal;
}