#include "Greedy.hh"

Greedy::Greedy(Task toSolve, bool random): toSolve(toSolve), random(random){}

double Greedy::solve()
{
    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<int> distribution;
    
    int pastIdx = 0; // vertex 1
    int currIdx;
    int bestIdx;

    int bestI;
    double bestVal = INT_MAX;
    
    int taskSize = toSolve.getTaskSize();
    
    auto distMatrix = toSolve.getDistMatrix();

    this->solution.clear();

    std::vector<int> availablePoints;
    
    this->solution.push_back(1);

    for(int i=2; i<=taskSize; i++)
    {
        availablePoints.push_back(i);
    }

    while (!(availablePoints.empty()))
    {   
        if(this->random)
        {
            distribution = std::uniform_int_distribution<int>(0, availablePoints.size()-1);
            bestI = distribution(rng);
        }
        else
        {
            bestVal = INT_MAX;
            for(int i=0; i<availablePoints.size(); i++)
            {  
                currIdx = availablePoints[i] - 1;
                double tempDist = distMatrix[pastIdx][currIdx];
                if(tempDist < bestVal)
                {
                    bestVal = tempDist;
                    bestI = i;
                    bestIdx = currIdx;
                }
            }
            pastIdx = bestIdx;
        }
        this->solution.push_back(availablePoints[bestI]);

        availablePoints.erase(availablePoints.begin()+bestI);
        
    }

    this->solution.push_back(1);
    
    return evaluate();
}

double Greedy::evaluate()
{
    int pastIdx = 0; // vertex 1
    int currIdx;
    double dist = 0.;
    auto distMatrix = toSolve.getDistMatrix();
    int taskSize = toSolve.getTaskSize();

    for(int j=1; j<=taskSize;j++)
    {
        currIdx = this->solution[j]-1; // new vertex
        dist += distMatrix[pastIdx][currIdx];
        pastIdx = currIdx;
    }
    this->solutionLen = dist;

    return dist;
}


