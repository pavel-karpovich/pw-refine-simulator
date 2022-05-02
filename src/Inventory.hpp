#pragma once

#include <exception>
#include <functional>
#include <vector>
#include <stack>
#include <optional>
#include "Item.hpp"
#include "StepException.hpp"


class Slot
{
private:
    uint item_id = 0;
    std::stack<std::shared_ptr<const Item>> items;

public:
    bool addItem(std::shared_ptr<const Item> item)
    {
        if (this->isEmpty())
        {
            this->item_id = item->id;
        }
        if (!this->isFull())
        {
            this->items.push(std::move(item));
            return true;
        }
        return false;
    }

    const std::optional<std::shared_ptr<const Item>> removeItem()
    {
        if (this->isEmpty())
        {
            return std::nullopt;
        }
        auto item = this->items.top();
        this->items.pop();
        if (this->isEmpty())
        {
            this->item_id = 0;
        }
        return std::optional<std::shared_ptr<const Item>>{std::move(item)};
    }

    const std::optional<std::shared_ptr<const Item>> topItem() const
    {
        if (this->isEmpty())
        {
            return std::nullopt;
        }
        return std::optional<std::shared_ptr<const Item>>{this->items.top()};
    }

    bool isEmpty() const
    {
        return this->items.size() == 0;
    }

    bool isFull() const
    {
        if (this->isEmpty())
        {
            return false;
        }
        return this->items.size() == this->items.top()->max_pile;
    }

    uint getItemId() const
    {
        return this->item_id;
    }

    std::string toString() const
    {
        if (this->isEmpty())
        {
            return "Empty";
        }
        std::ostringstream oss;
        oss << this->topItem().value()->toString();
        if (this->items.size() > 1)
        {
            oss << " x" << this->items.size();
        }
        return oss.str();
    }
};

class Inventory
{
private:
    ulong spent_gold = 0;
    Slot slots[64];
    
public:

    std::vector<std::reference_wrapper<const Slot>> getInventory() const
    {
        std::vector<std::reference_wrapper<const Slot>> non_empty_slots;
        for (size_t i = 0; i < sizeof(this->slots); ++i)
        {
            if (!this->slots[i].isEmpty())
            {
                non_empty_slots.push_back(std::cref(this->slots[i]));
            }
        }
        return non_empty_slots;
    }

    void addItems(std::stack<std::shared_ptr<const Item>>& items)
    {
        if (items.size() == 0)
        {
            throw StepException(1, "Internal error: no items @1");
        }
        do
        {
            int slot_index = this->findSlotForItem(items);
            if (slot_index == -1)
            {
                throw StepException(0, "Inventory is full");
            }
            this->fillSlot(slot_index, items);
        }
        while (!items.empty());
    }

    void removeItemById(uint item_id)
    {
        int slot_index = this->findSlotByItemId(item_id);
        if (slot_index == -1)
        {
            throw StepException(1, "Internal error: item not found @1");
        }
        auto removed_item = this->slots[slot_index].removeItem();
        if (removed_item.has_value())
        {
            this->spent_gold += removed_item.value()->price;
        }
    }

    void removeItem(std::shared_ptr<const Item> item)
    {
        int slot_index = this->findSlot(item);
        if (slot_index == -1)
        {
            throw StepException(1, "Internal error: item not found @2");
        }
        auto removed_item = this->slots[slot_index].removeItem();
        if (removed_item.has_value())
        {
            this->spent_gold += removed_item.value()->price;
        }
    }

private:
    int findSlotByItemId(uint item_id)
    {
        for (size_t i = 0; i < sizeof(this->slots); ++i)
        {
            if (this->slots[i].getItemId() == item_id)
            {
                return i;
            }
        }
        return -1;
    }

    // It will search by ref only in top items for each slot
    int findSlot(std::shared_ptr<const Item> item)
    {
        for (size_t i = 0; i < sizeof(this->slots); ++i)
        {
            auto top_item = this->slots[i].topItem().value();
            if (top_item == item)
            {
                return i;
            }
        }
        return -1;
    }

    int findSlotForItem(std::stack<std::shared_ptr<const Item>>& items)
    {
        int first_free_slot_index = -1;
        for (size_t i = 0; i < sizeof(this->slots); ++i)
        {
            if (this->slots[i].isEmpty() && first_free_slot_index == -1)
            {
                first_free_slot_index = i;
            }
            if (
                this->slots[i].getItemId() == items.top()->id &&
                !this->slots[i].isEmpty() && !this->slots[i].isFull()
            ) {
                return i;
            }
        }
        return first_free_slot_index;
    }

    void fillSlot(uint slot_index, std::stack<std::shared_ptr<const Item>>& items)
    {
        if (!this->slots[slot_index].isEmpty() && this->slots[slot_index].getItemId() != items.top()->id)
        {
            throw StepException(1, "Internal error: wrong slot @1");
        }
        while (!this->slots[slot_index].isFull() && !items.empty())
        {
            auto item = items.top();
            items.pop();
            this->slots[slot_index].addItem(std::move(item));
        }
    }
};
