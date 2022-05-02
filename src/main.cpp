#include "Simulator.hpp"
#include "markovChain.hpp"
#include "RefineCostAnalyzer.hpp"
#include "ExecutionTimer.hpp"


int main(int argc, char* argv[])
{
    std::cout << "Start PW Refine simulator " << argc << argv << std::endl;
    ExecutionTimer execTimer(std::cout);
    
    //PWEquipementRefineSimulator simulator;
    // simulator.run();

    // uint level = atoi(argv[1]);
    // uint trials = atoi(argv[2]);
    // printMarkovChainProbabilities(level, trials);


    RefineCostAnalyzer costAnalyzer(10000, 570000);
    costAnalyzer.analyzeUltimate();
    // uint level = atoi(argv[1]);
    // double money = atoi(argv[2]);
    // costAnalyzer.analyzeCost(level, money);
    return 0;
}
