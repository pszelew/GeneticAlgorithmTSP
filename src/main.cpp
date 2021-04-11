#include <iostream>
#include "DataLoader.hh"
#include "Population.hh"
#include "Greedy.hh"
#include "GA.hh"
#include <fstream>

using namespace std;

void solveTestData(int popSize, double pX, double pM, int tours, int iters)
{
    string fileName = "test_data";
    cout << "Solving " + fileName + ". Just to show that everything works" << endl;
    
    DataLoader loader;
    Task simpleTask = loader.loadData("data/test_data");    
    simpleTask.init();

    Greedy greedySolver(simpleTask);
    Greedy randomSolver(simpleTask, true);
    GA geneticSolver(simpleTask, popSize, pX, pM, tours, iters);

    cout << "Greedy: " << greedySolver.solve() << endl;
    cout << "GA: " << geneticSolver.solve() << endl;
    cout << "Random: " << randomSolver.solve() << endl;
    cout << "-------------------------------------------------------------" << endl;
}


void solveMyChosen(int popSize, double pX, double pM, int tours, int iters)
{
    string fileName = "A-n48-k7";
    cout << "Solving " + fileName + ". It might take a while!" << endl;
    
    DataLoader loader;
    Task task = loader.loadData("data/" + fileName);
    task.init();

    Greedy greedySolver(task);
    GA geneticSolver(task, popSize, pX, pM, tours, iters, true);
    Greedy randomSolver(task, true);

    cout << "Greedy: " << greedySolver.solve() << endl;
    cout << "GA: " << geneticSolver.solve() << endl;
    cout << "Random: " << randomSolver.solve() << endl;
    cout << "-------------------------------------------------------------" << endl;

    auto bestHistory = geneticSolver.getBestValPerPopulation();
    auto worstHistory = geneticSolver.getWorstValPerPopulation();
    auto avgHistory = geneticSolver.getAvgValPerPopulation();

    std::ofstream outFile;
    string line;

    outFile.open("data/results/" + fileName + ".csv");

    if(outFile.is_open())
    {
        for(int i=0;i<bestHistory.size();i++)
        {
            line = std::to_string(bestHistory[i]) + ";" + std::to_string(worstHistory[i]) + ";" +std::to_string(avgHistory[i]) + "\n"; 
            outFile << line;
        }
        cout << "Results shoud be in data/restults directory" << endl;
    }

    outFile.close();
}

int main()
{
    int pop_size = 100;
    double pX = 0.7;
    double pM = 0.1;
    int tours = 5;
    int iters = 100;

    // solveTestData(pop_size, pX, pM, tours, iters);
    solveMyChosen(pop_size, pX, pM, tours, iters);
}
    
