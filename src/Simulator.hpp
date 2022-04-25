#pragma once

#include <exception>
#include <memory>
#include <map>
#include <cstring>
#include <iostream>
#include <iomanip>
#include "Inventory.hpp"
#include "ItemsGenerator.hpp"



class PWEquipementRefineSimulator
{

typedef void (PWEquipementRefineSimulator::*NumInputHandlerPtr)(int num);

private:
    NumInputHandlerPtr next_number_selection_handler = nullptr;

    Inventory inventory;


public:
    void run()
    {
        std::cout << " > Welcome to the PW Refine Simulator ©" << std::endl
            << " > You need to fill your inventory with items and stones and then proceed with rifinement!" << std::endl
            << " > Use \"h\" or \"help\" command to view the list of available commands." << std::endl
            << " > Good luck!" << std::endl;
        while (true)
        {
            try
            {
                std::cout << std::endl << "Enter the command: > ";
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

        this->setNextNumberSelectionHandler(nullptr);
        
        if (input == "h" || input == "help")
        {
            this->displayHelp();
        }
        else if (input == "l" || input == "list")
        {
            this->displayInventory();
            this->setNextNumberSelectionHandler(&PWEquipementRefineSimulator::selectInventoryItem);
        }
        else if (input == "a" || input == "add")
        {
            this->displayAvailableItems();
            this->setNextNumberSelectionHandler(&PWEquipementRefineSimulator::selectAvailableItem);
        }
        else
        {
            std::cout << "Unrecognized command" << std::endl;
        }
    }

    void setNextNumberSelectionHandler(NumInputHandlerPtr handler)
    {
        this->next_number_selection_handler = handler;
    }

    void displayHelp()
    {
        std::cout << "   List of available commands:" << std::endl
            << "    - " << std::setw(10) << std::left << "help (h)" << "- show what you are reading right now:)" << std::endl
            << "    - " << std::setw(10) << std::left << "list (l)" << "- show your inventory. After that you can select an item from the inventory to operate with it" << std::endl
            << "    - " << std::setw(10) << std::left << "add (a)" << "- show list of items you can add to the inventory. After that you will be able to take an item from the list" << std::endl
            << "    - " << std::setw(10) << std::left << "" << "- " << std::endl
            << "    - " << std::setw(10) << std::left << "" << "- " << std::endl;
    }

    void displayInventory()
    {
        auto inventory_slots = this->inventory.getInventory();

        if (inventory_slots.empty())
        {
            std::cout << " > Inventory is empty" << std::endl;
        }
        size_t i = 1;
        for (auto slot : inventory_slots)
        {
            std::cout << "  " << i << ") " << slot.get().toString();
            i++;
        }
    }

    void selectInventoryItem(int num)
    {
        std::cout << "Select item #" << num << std::endl;
    }

    void displayAvailableItems()
    {
        std::cout << "  List of available items:" << std::endl
            << "    1)  Random equipement item" << std::endl
            << "    2)  Tienkang Stone x1000" << std::endl
            << "    3)  Tisha Stone x1000" << std::endl
            << "    4)  Chienkun Stone x1000" << std::endl
            << " > Which item do you want to add to the inventory?" << std::endl;
    }

    void selectAvailableItem(int num)
    {
        switch (num)
        {
        case 1:
        {
            std::shared_ptr<const Item> eq_item = std::move(ItemsGenerator::getRandomEquipementItem());
            std::stack<std::shared_ptr<const Item>> stack;
            stack.push(eq_item);
            this->inventory.addItems(stack);
            break;
        }
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            std::cout << " Unknown option" << std::endl;
        }
    }
};
