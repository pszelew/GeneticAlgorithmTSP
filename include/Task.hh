#ifndef TASK_HH
#define TASK_HH

#include <string>
#include <vector>
#include <cmath>

using std::string;
using std::pair;
using std::vector;

class Task
{
    public:
        Task(){}
        Task(string name, int taskSize, vector<pair<int, int>> coords);

        void init();
        
        const string & getName(){return name;}
        void setName(string name){this->name = name;}

        const int & getTaskSize() const {return taskSize;}
        void setTaskSize(int taskSize){this->taskSize = taskSize;}
        
        const vector<pair<int, int>> & getCoords() const {return coords;}
        vector<pair<int, int>> & getCoordsMod(){return coords;}
        void setCoords(vector<pair<int, int>>){this->coords = coords;}

        const vector<vector<double>> & getDistMatrix() const {return distMatrix;}
        vector<vector<double>> & getDistMatrixMod(){return distMatrix;}
    private:
        string name;
        int taskSize;
        vector<pair<int, int>> coords;
        vector<vector<double>> distMatrix;
};

#endif