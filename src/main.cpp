#include "Simulator.hpp"
#include "markovChain.hpp"
#include "costAnalyzer.hpp"


int main(int argc, char* argv[])
{
    std::cout << "Start PW Refine simulator " << argc << std::endl;
    
    //PWEquipementRefineSimulator simulator;
    // simulator.run();

    uint level = atoi(argv[1]);
    uint trials = atoi(argv[2]);
    printMarkovChainProbabilities(level, trials);


    // RefineCostAnalyzer costAnalyzer(10000, 570000);
    // double money = atof(argv[1]);
    // costAnalyzer.analyzeCost(money, 5);
    return 0;
}
