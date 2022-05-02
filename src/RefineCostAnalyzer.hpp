#pragma once

#include <string>
#include <algorithm>
#include <Eigen/Dense>
#include "markovChain.hpp"


struct Step
{
    std::string name;
    ulong cost;
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

struct RefineLevelResult
{
    std::string name = "";
    ulong cost = 0;
};


void prettyFormatNumber(std::stringstream& ss, ulong n) {
    if (n < 1000)
    {
        ss << n;
    }
    else
    {
        prettyFormatNumber(ss, n / 1000);
        ss << " " << std::setw(3) << std::setfill('0') << (n % 1000);
    }
}


class RefineCostAnalyzer
{
private:
    Step step_options[4];
    std::vector<Result> results;

public:
    RefineCostAnalyzer(ulong mirazh_cost, ulong stone_cost)
        : step_options({
            {"mirazh", mirazh_cost, mirazh_matrix()},
            {"nebeska", mirazh_cost + stone_cost, nebeska_matrix()},
            {"podzemka", mirazh_cost + stone_cost, podzemka_matrix()},
            {"mirozdanka", mirazh_cost + stone_cost, mirozdanka_matrix()}
        }) {
            std::cout << stone_cost;
        }

    
    void analyzeCost(uint target_refine, ulong money)
    {
        
        RefineVector initial_prob_state;
        initial_prob_state << 1.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0;
        for (Step& step_option : this->step_options)
        {
            step_option.prob_matrix.row(target_refine) *= 0;
            step_option.prob_matrix(target_refine, target_refine) = 1.0;
        }
        std::cout << this->step_options[0].prob_matrix << std::endl << std::endl;
        std::cout << "Analyze best way to rifine +" << target_refine << " with money: " << money << std::endl;
        const Result* best_result = this->makeStepFurther(money, target_refine, initial_prob_state, 1, "");
        std::cout << "Best path to refine +" << target_refine << " is found:" << std::endl;
        std::cout << best_result->path << std::endl;
        printVector(refine_levels);
        std::cout << std::left << std::setw(12) << best_result->prob_vector << std::endl;
        delete best_result;
    }

    void analyzeUltimate()
    {
        const double precision = 0.2;
        const double required_probability = 1.0 - precision;

        const size_t levels = this->step_options[0].prob_matrix.rows() - 1;
        RefineLevelResult results[levels];

        for (size_t curr_refine_level = 0; curr_refine_level < levels; ++curr_refine_level)
        {
            for (auto step_option : this->step_options)
            {
                size_t failure_refine_level = 0;
                double failure_probability = 0.0;
                auto refine_row = step_option.prob_matrix.row(curr_refine_level);
                for (size_t i = 0; i < static_cast<size_t>(refine_row.size()); ++i)
                {
                    double i_value = refine_row.coeff(i);
                    if (i_value != 0)
                    {
                        failure_refine_level = i;
                        failure_probability = i_value;
                        break;
                    }
                }
                double success_probability = refine_row.coeff(curr_refine_level + 1);
                
                ulong cost = curr_refine_level == 0 ? 0 : results[curr_refine_level - 1].cost;
                double success_prob_total = success_probability;
                double failure_prob_left = failure_probability;
                cost += step_option.cost;
                
                while (success_prob_total < required_probability)
                {
                    if (results[curr_refine_level].cost != 0 && cost >= results[curr_refine_level].cost)
                    {
                        break;
                    }
                    if (curr_refine_level != 0)
                    {
                        cost += results[curr_refine_level - 1].cost;
                        if (failure_refine_level != 0)
                        {
                            cost -= results[failure_refine_level - 1].cost;
                        }
                    }
                    success_prob_total += failure_prob_left * success_probability;
                    failure_prob_left *= failure_probability;
                    cost += step_option.cost;
                }
                if (cost < results[curr_refine_level].cost || results[curr_refine_level].cost == 0)
                {
                    results[curr_refine_level].cost = cost;
                    results[curr_refine_level].name = step_option.name;
                }
            }
            std::stringstream ss;
            prettyFormatNumber(ss, results[curr_refine_level].cost);
            std::string pretty_cost = ss.str();
            std::cout << "  The best way to refine +" << curr_refine_level + 1 << " from +" << curr_refine_level <<" is using \"" << results[curr_refine_level].name << "\"." << std::endl
                << "    The total price is " << std::fixed << std::setprecision(0) << pretty_cost << std::endl;
        }
    }

private:
    Result* makeStepFurther(ulong money_left, uint target_refine, RefineVector prob_state, uint depth, std::string path_str)
    {
        Result* best_result = nullptr;
        bool current_step_was_checked = false;
        for (Step& step_option : this->step_options)
        {
            Result* next_result = nullptr;
            if (step_option.cost > money_left)
            {
                if (!current_step_was_checked)
                {
                    current_step_was_checked = true;
                    next_result = new Result(path_str, prob_state);
                }
            }
            else
            {
                RefineVector step_prob_state = prob_state * step_option.prob_matrix;
                next_result = makeStepFurther(money_left - step_option.cost, target_refine, step_prob_state, depth + 1, path_str + " " + std::to_string(depth) + ")" + step_option.name);
            }
            if (next_result != nullptr)
            {
                std::cout << " Found result: " << next_result->prob_vector[target_refine] << " path: " << next_result->path << std::endl;
                std::cout << " Probability vector: " << next_result->prob_vector << std::endl << std::endl;
            }
            if (best_result == nullptr || (next_result != nullptr && next_result->prob_vector[target_refine] > best_result->prob_vector[target_refine]))
            {
                if (best_result != nullptr)
                {
                    delete best_result;
                }
                best_result = next_result;
            }
            else if (next_result != nullptr)
            {
                delete next_result;
            }
        }
        return best_result;
    }
};
