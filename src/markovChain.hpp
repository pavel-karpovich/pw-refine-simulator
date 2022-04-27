#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <Eigen/Dense>
 

 using StoneMatrix = Eigen::Matrix<double, 13, 13>;
 using RefineVector = Eigen::RowVector<double, 13>;

StoneMatrix mirazh_matrix()
{
    StoneMatrix matrix;
    matrix <<
        0.5 , 0.5 , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,
        0.7 , 0   , 0.3 , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,
        0.7 , 0   , 0   , 0.3 , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,
        0.7 , 0   , 0   , 0   , 0.3 , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,
        0.7 , 0   , 0   , 0   , 0   , 0.3 , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,
        0.7 , 0   , 0   , 0   , 0   , 0   , 0.3 , 0   , 0   , 0   , 0   , 0   , 0   ,
        0.7 , 0   , 0   , 0   , 0   , 0   , 0   , 0.3 , 0   , 0   , 0   , 0   , 0   ,
        0.7 , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0.3 , 0   , 0   , 0   , 0   ,
        0.75, 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0.25, 0   , 0   , 0   ,
        0.8 , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0.2 , 0   , 0   ,
        0.98, 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0.12, 0   ,
        0.95, 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0.05,
        0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 1.0 ;
    return matrix;
}

StoneMatrix nebeska_matrix()
{
    StoneMatrix matrix;
    matrix <<
        0.35, 0.65, 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,
        0.55, 0   , 0.45, 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,
        0.55, 0   , 0   , 0.45, 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,
        0.55, 0   , 0   , 0   , 0.45, 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   ,
        0.55, 0   , 0   , 0   , 0   , 0.45, 0   , 0   , 0   , 0   , 0   , 0   , 0   ,
        0.55, 0   , 0   , 0   , 0   , 0   , 0.45, 0   , 0   , 0   , 0   , 0   , 0   ,
        0.55, 0   , 0   , 0   , 0   , 0   , 0   , 0.45, 0   , 0   , 0   , 0   , 0   ,
        0.55, 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0.45, 0   , 0   , 0   , 0   ,
        0.6 , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0.4 , 0   , 0   , 0   ,
        0.65, 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0.35, 0   , 0   ,
        0.73, 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0.27, 0   ,
        0.8 , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0.2 ,
        0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0   , 0  , 1.0 ;
    return matrix;
}

StoneMatrix podzemka_matrix()
{
    StoneMatrix matrix;
    matrix <<
        0.465, 0.535, 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    ,
        0.665, 0    , 0.335, 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    ,
        0    , 0.665, 0    , 0.335, 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    ,
        0    , 0    , 0.665, 0    , 0.335, 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    ,
        0    , 0    , 0    , 0.665, 0    , 0.335, 0    , 0    , 0    , 0    , 0    , 0    , 0    ,
        0    , 0    , 0    , 0    , 0.665, 0    , 0.335, 0    , 0    , 0    , 0    , 0    , 0    ,
        0    , 0    , 0    , 0    , 0    , 0.665, 0    , 0.335, 0    , 0    , 0    , 0    , 0    ,
        0    , 0    , 0    , 0    , 0    , 0    , 0.665, 0    , 0.335, 0    , 0    , 0    , 0    ,
        0    , 0    , 0    , 0    , 0    , 0    , 0    , 0.715, 0    , 0.285, 0    , 0    , 0    ,
        0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0.765, 0    , 0.235, 0    , 0    ,
        0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0.845, 0    , 0.155, 0    ,
        0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0.915, 0    , 0.085,
        0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 0    , 1.0  ;
    return matrix;
}

StoneMatrix mirozdanka_matrix()
{
    StoneMatrix matrix;
    matrix <<
        0       , 1.0     , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       ,
        0       , 0.75    , 0.25    , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       ,
        0       , 0       , 0.9     , 0.1     , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       ,
        0       , 0       , 0       , 0.96    , 0.04    , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       ,
        0       , 0       , 0       , 0       , 0.983333, 0.016667, 0       , 0       , 0       , 0       , 0       , 0       , 0       ,
        0       , 0       , 0       , 0       , 0       , 0.992308, 0.007692, 0       , 0       , 0       , 0       , 0       , 0       ,
        0       , 0       , 0       , 0       , 0       , 0       , 0.995349, 0.004651, 0       , 0       , 0       , 0       , 0       ,
        0       , 0       , 0       , 0       , 0       , 0       , 0       , 0.997531, 0.002469, 0       , 0       , 0       , 0       ,
        0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0.998667, 0.001333, 0       , 0       , 0       ,
        0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0.99927 , 0.00073 , 0       , 0       ,
        0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0.999634, 0.000396, 0       ,
        0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0.999785, 0.000215,
        0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 0       , 1.0     ;
    return matrix;
}

class RefineMathModel
{
public:
    enum StoneType
    {
        Mirazh, Nebeska, Podzemka, Mirozdanka
    };

private:
    const StoneMatrix mirazh;
    const StoneMatrix nebeska;
    const StoneMatrix podzemka;
    const StoneMatrix mirozdanka;

public:
    RefineMathModel()
        :   mirazh(mirazh_matrix()),
            nebeska(nebeska_matrix()),
            podzemka(podzemka_matrix()),
            mirozdanka(mirozdanka_matrix())
    {}

    const RefineVector getProbabilities(StoneType stone, uint steps = 1000)
    {
        const StoneMatrix* matrix = this->getStoneMatrix(stone);
        RefineVector vector;
        vector << 1.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
        for (size_t i = 0; i < steps; ++i)
        {
            vector = vector * *matrix;
        }
        return vector;
    }

private:
    const StoneMatrix* getStoneMatrix(StoneType stone)
    {
        switch (stone)
        {
        case StoneType::Mirazh:
            return &this->mirazh;
        case StoneType::Nebeska:
            return &this->nebeska;
        case StoneType::Podzemka:
            return &this->podzemka;
        case StoneType::Mirozdanka:
            return &this->mirozdanka;
        }
        return nullptr;
    }
};


std::vector<std::string> refine_levels { "0", "+1", "+2", "+3", "+4", "+5", "+6", "+7", "+8", "+9", "+10", "+11", "+12"};
void printVector(const std::vector<std::string> &vector)
{
    std::cout << std::left << std::setw(12) << " ";
    for (auto member : vector)
    {
        std::cout << std::left << std::setw(12) << member;
        std::cout << " ";
    }
    std::cout << std::endl;
}

void printMarkovChainProbabilities()
{
    RefineMathModel model;
    RefineVector prob_vector1 = model.getProbabilities(RefineMathModel::Mirazh);
    RefineVector prob_vector2 = model.getProbabilities(RefineMathModel::Nebeska);
    RefineVector prob_vector3 = model.getProbabilities(RefineMathModel::Podzemka);
    RefineVector prob_vector4 = model.getProbabilities(RefineMathModel::Mirozdanka);

    std::cout << std::endl;
    std::cout << "Probability for Refining with \"Mirazh\" after 1000 trials:" << std::endl;
    printVector(refine_levels);
    std::cout << std::left << std::setw(12) << prob_vector1 << std::endl;
    std::cout << std::endl;
    std::cout << "Probability for Refining with \"Nebeska\" after 1000 trials:" << std::endl;
    printVector(refine_levels);
    std::cout << std::left << std::setw(12) << prob_vector2 << std::endl;
    std::cout << std::endl;
    std::cout << "Probability for Refining with \"Podzemka\" after 1000 trials:" << std::endl;
    printVector(refine_levels);
    std::cout << std::left << std::setw(12) << prob_vector3 << std::endl;
    std::cout << std::endl;
    std::cout << "Probability for Refining with \"Mirozdanka\" after 1000 trials:" << std::endl;
    printVector(refine_levels);
    std::cout << std::left << std::setw(12) << prob_vector4 << std::endl;
}


