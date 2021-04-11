#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TEST
#include <boost/test/unit_test.hpp>

#include "Greedy.hh"
#include "DataLoader.hh"
#include "Population.hh"

inline bool is_close(double a, double b, double tolerance = 1e-3)
{ 
    return (a - b) * (a - b) < tolerance * tolerance;
}


struct MySolver
{
    MySolver()
    {
        DataLoader loader;
        Task simpleTask = loader.loadData("data/test_data");
        
        simpleTask.init();
        greedySolver = new Greedy(simpleTask);

        greedySolver->solve();
    }
   
    ~MySolver()
    {
        delete greedySolver;
    }
   
    Greedy * greedySolver;
};



BOOST_FIXTURE_TEST_CASE( testSolveSeq, MySolver )
{
    auto bestSol = greedySolver->getSolution();
    std::vector<int> vect{1, 4, 2, 3, 6, 5, 1};

    BOOST_CHECK( bestSol == vect);
}

BOOST_FIXTURE_TEST_CASE( testSolveVal, MySolver )
{
    auto bestSol = greedySolver->getSolutionLen();
    BOOST_CHECK( is_close(bestSol, 195.021));
}

BOOST_AUTO_TEST_CASE( testCalcOneLen )
{
    DataLoader loader;
    Task simpleTask = loader.loadData("data/test_data");
        
    simpleTask.init();
    
    Population population(1, simpleTask.getTaskSize());

    population.getPopulMod().push_back(vector<int>{2, 3, 4, 5, 6});
    
    double res = population.calcOneLen(0, simpleTask.getDistMatrix());
    BOOST_CHECK( is_close(res, 251.1633));
}

BOOST_AUTO_TEST_CASE( testCalcOneCheck )
{
    DataLoader loader;
    Task simpleTask = loader.loadData("data/test_data");
        
    simpleTask.init();
    
    double res = Population::calcOneLenCheck(vector<int>{2, 3, 4, 5, 6}, simpleTask.getDistMatrix());
    BOOST_CHECK( is_close(res, 251.1633));
}


BOOST_AUTO_TEST_CASE(testmutInversion)
{
    
    auto is = Population::mutInversion(vector<int>{9, 8, 2, 1, 7, 4, 5, 10, 6, 3}, 1, 5);

    auto shouldBe = vector<int>{9, 4, 7, 1, 2, 8, 5, 10, 6, 3};

    BOOST_CHECK( is == shouldBe);
}


BOOST_AUTO_TEST_CASE( testCrossCx )
{
    Population population(2, 11);

    population.getPopulMod().push_back(vector<int>{9, 8, 2, 1, 7, 4, 5, 10, 6, 3});
    population.getPopulMod().push_back(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    
    auto res1 = population.crossCx(0, 1, 0, 0);
    auto res2 = population.crossCx(0, 1, 0, 1);

    auto shouldBe1 = vector<int>{9, 2, 3, 1, 5, 4, 7, 8, 6, 10};
    auto shouldBe2 = vector<int>{1, 8, 2, 4, 7, 6, 5, 10, 9, 3};

    BOOST_CHECK( res1 == shouldBe1 && res2 == shouldBe2);
}

BOOST_AUTO_TEST_CASE( testTournament )
{
    DataLoader loader;
    Task simpleTask = loader.loadData("data/test_data");
        
    simpleTask.init();
    
    Population population(4, simpleTask.getTaskSize());

    population.getPopulMod().push_back(vector<int>{1, 2, 3, 4, 5, 6, 1});
    population.getPopulMod().push_back(vector<int>{1, 2, 5, 4, 3, 6, 1});
    population.getPopulMod().push_back(vector<int>{1, 3, 2, 4, 5, 6, 1});
    population.getPopulMod().push_back(vector<int>{1, 6, 5, 3, 4, 2, 1});
    
    int res = population.tournament(4, simpleTask.getDistMatrix());

    BOOST_CHECK( res == 0);
}