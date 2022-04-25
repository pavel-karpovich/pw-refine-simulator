#include "Simulator.hpp"
#include "markovChain.hpp"


int main(int argc, char* argv[])
{
    std::cout << "Start PW Refine simulator" << std::endl
        << "argc: " << argc << std::endl
        << "argv: 0 = " << (*argv)[0] << ", 1 = " << (*argv)[1] << std::endl;
    PWEquipementRefineSimulator simulator;
    // simulator.run();

    eigenTest();
    return 0;
}
