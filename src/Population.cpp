#include "Population.hh"

using std::cout;
using std::endl;

Population::Population(int popSize, int taskSize): 
    populSize(popSize), taskSize(taskSize)
    {
        rng = std::mt19937(device());
    }



void Population::initPopulRandom()
{  
    std::vector<int> allValues;
    std::vector<int> possibleValuesToAdd;
    std::vector<int> tempAdd;

    std::uniform_int_distribution<int> distribution;

    this->popul.clear();

    // Create all possible values of gen
    for(int i=2; i<=this->taskSize; i++)
    {
        allValues.push_back(i);
    }
    
    for(int i=0;i<this->populSize;i++)
    {
        tempAdd.clear();
        possibleValuesToAdd = allValues;

        for(int j=0;j<this->taskSize-1;j++)
        {   
            distribution = std::uniform_int_distribution<int>(0, possibleValuesToAdd.size()-1);
            int idx = distribution(rng);
            tempAdd.push_back(possibleValuesToAdd[idx]);

            possibleValuesToAdd.erase(possibleValuesToAdd.begin()+idx);

        }

        this->popul.push_back(tempAdd);
    }


    // for(auto item : this->popul)
    // {
    //     for(auto i : item)
    //     {
    //         std::cout<<i<<" ";
    //     }
    //     std::cout<<std::endl;
    // }
}


std::vector<double> Population::calcPopulLen(const std::vector<std::vector<double>> & distMatrix)
{
    int pastIdx = 0; // vertex 1
    int currIdx;
    double dist;

    std::vector<double> toReturn;

    for(int i=0; i<this->populSize;i++)
    {   
        dist = 0.;
        for(int j=0; j<this->taskSize-1;j++)
        {
            currIdx = this->popul[i][j]-1; // new vertex
            dist += distMatrix[pastIdx][currIdx];
            // cout<<"Dist: "<< pastIdx+1<< "->"<<currIdx+1 << " = " << distMatrix[pastIdx][currIdx] <<endl;
            pastIdx = currIdx;
        }

        dist += distMatrix[0][currIdx];
        toReturn.push_back(dist);
    }

    return toReturn;

}

double Population::calcOneLen(int index, const std::vector<std::vector<double>> & distMatrix)
{
    int pastIdx = 0; // vertex 1
    int currIdx;
    double dist = 0.;

    for(int j=0; j<this->taskSize-1;j++)
    {
        currIdx = this->popul[index][j]-1; // new vertex
        dist += distMatrix[pastIdx][currIdx];
        pastIdx = currIdx;
    }
    dist += distMatrix[0][currIdx];
    return dist;
}

double Population::calcOneLenCheck (std::vector<int> toCheck, const std::vector<std::vector<double>> & distMatrix)
{
    int pastIdx = 0; // vertex 1
    int currIdx;
    double dist = 0.;
    
    for(int j=0; j<toCheck.size();j++)
    {
        currIdx = toCheck[j]-1; // new vertex
        dist += distMatrix[pastIdx][currIdx];
        pastIdx = currIdx;
    }
    dist += distMatrix[0][currIdx];
    return dist;
}

std::vector<int> Population::mutInversion(std::vector<int> toMutate, int start, int end)
{
    std::vector<int> swapped;

    for(int i=start;i<=end;i++)
    {
        swapped.insert(swapped.begin(), toMutate[i]);
    }

    int j = 0;

    for(int i=start;i<=end;i++)
    {
        toMutate[i] = swapped[j++];
    }

    return toMutate;
}

std::vector<int> Population::crossCx(int idx1, int idx2, int startIdx, int chooseLeading)
{
    std::vector<int> firstParent;
    std::vector<int> secondParent;
    std::vector<int> child(taskSize-1, -1);
    std::vector<int>::iterator nowCross;
    std::set<int> inserted;

    int currentVal;
    std::uniform_int_distribution<int> distribution(0, 1) ;
    
    int leading;

    if(chooseLeading == -1)
    {
        leading = distribution(rng);
    }
    else
    {
        leading=chooseLeading;
    }

    if(leading == 0)
    {
        firstParent =  this->popul[idx1];
        secondParent = this->popul[idx2];
    }
    else
    {
        firstParent =  this->popul[idx2];
        secondParent = this->popul[idx1];
    }
    
    distribution = std::uniform_int_distribution<int>(0, this->taskSize);


    if(startIdx == -1)
    {
        nowCross = firstParent.begin() + distribution(rng);
    }
    else
    {
        nowCross = firstParent.begin() + startIdx;
    }

    
    currentVal = *nowCross;
    child[nowCross - firstParent.begin()] = currentVal;
    inserted.insert(currentVal);
    while (true)
    {   
        currentVal = secondParent[nowCross - firstParent.begin()];
        
        if(inserted.find(currentVal)!= inserted.end()) // found in
        {
            break;
        }

        inserted.insert(currentVal);

        nowCross = std::find(firstParent.begin(), firstParent.end(), currentVal);

        child[nowCross - firstParent.begin()] = currentVal;
    }


    std::vector<int>::iterator it;

    for(it=child.begin();it<child.end();it++)
    {
        if(*it == -1)
        {
            *it = secondParent[it-child.begin()];
        }
    }

    return child;

}

int Population::tournament(int tour, const std::vector<std::vector<double>> & distMatrix)
{
    std::uniform_int_distribution<int> distribution;
    std::vector<int> basket;
    int draw;
    int best;
    int currVal;
    int bestVal = INT_MAX;

    for(int i=0; i<this->populSize;i++)
    {
        basket.push_back(i);
    }

    for(int i=0; i<tour;i++)
    {
        distribution = std::uniform_int_distribution<int>(0, basket.size()-1);
        draw = distribution(rng);

        currVal = this->calcOneLen(basket[draw], distMatrix);

        if(currVal < bestVal)
        {
            best = basket[draw];
            bestVal = currVal;
        }

        basket.erase(basket.begin()+draw);
    }


    return best; 
}