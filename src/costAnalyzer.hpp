#pragma once

#include <string>
#include <algorithm>
#include <Eigen/Dense>
#include "markovChain.hpp"


struct Step
{
    std::string name;
    double cost;
    StoneMatrix prob_matrix;
};

class Result
{
public:
    std::string path;
    RefineVector prob_vector;

    Result(std::string path, RefineVector prob_vector)
        : path(path), prob_vector(prob_vector) {}
};

class RefineCostAnalyzer
{
private:
    Step step_options[4];
    std::vector<Result> results;

public:
    RefineCostAnalyzer(double mirazh_cost, double stone_cost)
        : step_options({
            {"mirazh", mirazh_cost, mirazh_matrix()},
            {"nebeska", mirazh_cost + stone_cost, nebeska_matrix()},
            {"podzemka", mirazh_cost + stone_cost, podzemka_matrix()},
            {"mirozdanka", mirazh_cost + stone_cost, mirozdanka_matrix()}
        }) {}

    
    void analyzeCost(double money, uint target_refine)
    {
        
        RefineVector initial_prob_state;
        initial_prob_state << 1.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
        for (auto step_option : this->step_options)
        {
            step_option.prob_matrix.row(target_refine) *= 0;
            step_option.prob_matrix(target_refine, target_refine) = 1.0;
            std::cout << std::endl << "Matrix:" << std::endl << step_option.prob_matrix << std::endl;
        }
        std::cout << money << std::endl;
        // const Result* best_result = this->makeStepFurther(money, target_refine, initial_prob_state, 1, "");
        // std::cout << "Best path to refine +" << target_refine << " is found:" << std::endl;
        // std::cout << best_result->path << std::endl;
        // printVector(refine_levels);
        // std::cout << std::left << std::setw(12) << best_result->prob_vector << std::endl;
    }

private:
    const Result* makeStepFurther(double money_left, uint target_refine, RefineVector prob_state, uint depth, std::string path_str)
    {
        if (money_left < 0)
        {
            return new Result(path_str, prob_state);
        }
        const Result* best_result = nullptr;
        for (auto step_option : this->step_options)
        {
            RefineVector step_prob_state = prob_state * step_option.prob_matrix;
            const Result* next_result = makeStepFurther(money_left - step_option.cost, target_refine, step_prob_state, depth + 1, path_str + " " + std::to_string(depth) + ")" + step_option.name);
            if (best_result == nullptr || next_result->prob_vector[target_refine] > best_result->prob_vector[target_refine])
            {
                delete best_result;
                best_result = next_result;
            }
            else 
            {
                delete next_result;
            }
        }
        return best_result;
    }
};

