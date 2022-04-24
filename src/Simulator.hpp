#include <exception>
#include <memory>
#include <cstring>
#include <iostream>
#include "Inventory.hpp"



class PWEquipementRefineSimulator
{

typedef void (PWEquipementRefineSimulator::*NumInputHandlerPtr)(int num);

private:
    NumInputHandlerPtr next_number_selection_handler = nullptr;

    Inventory inventory;


public:
    void run()
    {
        while (true)
        {
            try
            {
                std::string input_buffer;
                std::getline(std::cin, input_buffer);
                parseInput(input_buffer);
            }
            catch (const std::exception &excp)
            {
                std::cout << "Cought exception!" << std::endl;
            }
        }
    }

private:
    void parseInput(const std::string &input)
    {
        try
        {
            int num = std::stoi(input);
            if (this->next_number_selection_handler != nullptr)
            {
                std::invoke(this->next_number_selection_handler, this, num);
            }

        }
        catch (const std::exception& e) {}
        
        if (input == "l" || input == "list")
        {
            this->displayInventory();
            this->setNextNumberSelectionHandler(&PWEquipementRefineSimulator::selectInventoryItem);
        }
        else if (input == "a" || input == "add")
        {

        }
        else if (input == "s" || input == "select")
        {

        }
        else
        {
            std::cout << "Unrecognized command" << std::endl;
        }
    }

    void displayInventory()
    {
        auto inventory_slots = this->inventory.getInventory();
    }

    void setNextNumberSelectionHandler(NumInputHandlerPtr handler)
    {
        this->next_number_selection_handler = handler;
    }

    void selectInventoryItem(int num)
    {
        std::cout << "Select item #" << num << std::endl;
    }
};
