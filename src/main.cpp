#include "Simulator.hpp"
#include "markovChain.hpp"
#include "costAnalyzer.hpp"


int main(int argc, char* argv[])
{
    std::cout << "Start PW Refine simulator" << std::endl
        << "argc: " << argc << std::endl
        << "argv: 0 = " << (*argv)[0] << ", 1 = " << (*argv)[1] << std::endl;
    PWEquipementRefineSimulator simulator;
    // simulator.run();

    // printMarkovChainProbabilities();
    RefineCostAnalyzer costAnalyzer(10000, 570000);
    double money = atof(argv[1]);
    costAnalyzer.analyzeCost(money, 5);
    return 0;
}
