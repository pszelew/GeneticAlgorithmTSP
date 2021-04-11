#include "Task.hh"

double calcDistance(pair<int, int> first, std::pair<int, int> second)
{
    return sqrt(pow((second.first - first.first), 2) + pow((second.second - first.second), 2));
}


Task::Task(string name, int taskSize, std::vector<std::pair<int, int>> coords):
name(name), taskSize(taskSize), coords(coords) {}

void Task::init()
{
    std::vector<double> toAdd;
    
    for(int i=0;i<taskSize;i++)
    {
        toAdd.clear();
        for(int j=0;j<taskSize;j++)
        {
            toAdd.push_back(calcDistance(coords[i], coords[j]));
        }

        this->getDistMatrixMod().push_back(toAdd);        
    }
}