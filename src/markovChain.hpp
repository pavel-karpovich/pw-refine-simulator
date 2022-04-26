#include <iostream>
#include <Eigen/Dense>
 

 using StoneMatrix = Eigen::Matrix<double, 13, 13>;
 using RefineVector = Eigen::Vector<double, 13>;

std::unique_ptr<StoneMatrix> mirazh_matrix()
{
    auto matrix = std::make_unique<StoneMatrix>();
    *matrix <<
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

std::unique_ptr<StoneMatrix> nebeska_matrix()
{
    auto matrix = std::make_unique<StoneMatrix>();
    *matrix <<
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

std::unique_ptr<StoneMatrix> podzemka_matrix()
{
    auto matrix = std::make_unique<StoneMatrix>();
    *matrix <<
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

std::unique_ptr<StoneMatrix> mirozdanka_matrix()
{
    auto matrix = std::make_unique<StoneMatrix>();
    *matrix <<
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
    const std::unique_ptr<const StoneMatrix> mirazh;
    const std::unique_ptr<const StoneMatrix> nebeska;
    const std::unique_ptr<const StoneMatrix> podzemka;
    const std::unique_ptr<const StoneMatrix> mirozdanka;

public:
    RefineMathModel()
        :   mirazh(mirazh_matrix()),
            nebeska(nebeska_matrix()),
            podzemka(podzemka_matrix()),
            mirozdanka(mirozdanka_matrix())
    {}

    const std::unique_ptr<const RefineVector> getProbabilities(StoneType stone, uint steps = 1000)
    {
        const StoneMatrix* matrix = this->getStoneMatrix(stone);
        auto vector = std::make_unique<RefineVector>();
        *vector << 1.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
        for (size_t i = 0; i < steps; ++i)
        {
            *vector = *vector * *matrix;
        }
        return vector;
    }

private:
    const StoneMatrix* getStoneMatrix(StoneType stone)
    {
        switch (stone)
        {
        case StoneType::Mirazh:
            return this->mirazh.get();
        case StoneType::Nebeska:
            return this->nebeska.get();
        case StoneType::Podzemka:
            return this->podzemka.get();
        case StoneType::Mirozdanka:
            return this->mirozdanka.get();
        }
    }
};


void eigenTest()
{
    RefineMathModel model;
    auto prob_vector1 = model.getProbabilities(RefineMathModel::Mirazh);
    auto prob_vector2 = model.getProbabilities(RefineMathModel::Nebeska);
    auto prob_vector3 = model.getProbabilities(RefineMathModel::Podzemka);
    auto prob_vector4 = model.getProbabilities(RefineMathModel::Mirozdanka);
    std::cout << std::endl << "Probability for Refining with \"Mirazh\" after 1000 trials:" << std::endl << *prob_vector1 << std::endl;
    std::cout << std::endl << "Probability for Refining with \"Nebeska\" after 1000 trials:" << std::endl << *prob_vector2 << std::endl;
    std::cout << std::endl << "Probability for Refining with \"Podzemka\" after 1000 trials:" << std::endl << *prob_vector3 << std::endl;
    std::cout << std::endl << "Probability for Refining with \"Mirozdanka\" after 1000 trials:" << std::endl << *prob_vector4 << std::endl;
}


