#pragma once

#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <iterator>

unsigned int TIENKANG_STONE_ID = 1;
unsigned int TISHA_STONE_ID = 2;
unsigned int CHIENKUN_STONE_ID = 3;

class Item
{
public:
    unsigned int	id;		
    std::string     name;
    float           price;
    unsigned int    max_pile = 1;

    Item() {}
    Item(unsigned int id, std::string name, float price, unsigned int max_pile)
        : id(id), name(name), price(price), max_pile(max_pile) {}

    virtual std::string toString() const {
        return this->name;
    }
};


// REFINE_TICKET_ESSENCE in PW sources
class RefineEssence : public Item
{
public:
    enum EssenceType
    {
        TienkangStone,
        TishaStone,
        ChienkunStone
    };
private:
    EssenceType     type;
public:
	float			ext_reserved_prob;			// 提高失败后只降一级的概率 // Увеличивает вероятность понижения в должности только на один уровень после неудачи.
	float			ext_succeed_prob;			// 提高精炼成功的概率 // Увеличивает вероятность успеха переработки
	unsigned int	fail_reserve_level;			// 是否失败不降精炼等级 // Провалиться ли без снижения уровня переработки
	float			fail_ext_succeed_prob[12];	// 在精炼失败不降等级时的成功概率调整 // Корректировка вероятности успеха при неудачной переработке без понижения рейтинга

private:
    RefineEssence() : Item() {}
public:
    RefineEssence(EssenceType type) : Item()
    {
        this->price = 1.0;
        this->max_pile = 1000;
        this->type = type;

        switch (type)
        {
            case EssenceType::TienkangStone:
            {
                this->id = TIENKANG_STONE_ID;
                this->name = "Tienkang Stone";
                this->ext_reserved_prob = 0.0;
                this->ext_succeed_prob = 0.15;
                this->fail_reserve_level = 0;
                float src[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
                std::copy(std::begin(src), std::end(src), std::begin(this->fail_ext_succeed_prob));
                break;
            }
            case EssenceType::TishaStone:
            {
                this->id = TISHA_STONE_ID;
                this->name = "Tisha Stone";
                this->ext_reserved_prob = 1.0;
                this->ext_succeed_prob = 0.035;
                this->fail_reserve_level = 0;
                float src[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
                std::copy(std::begin(src), std::end(src), std::begin(this->fail_ext_succeed_prob));
                break;
            }
            case EssenceType::ChienkunStone:
            {
                this->id = CHIENKUN_STONE_ID;
                this->name = "Chienkun Stone";
                this->ext_reserved_prob = 0.0;
                this->ext_succeed_prob = 0.0;
                this->fail_reserve_level = 1;
                float src[] = {1.0000000, 0.2500000, 0.1000000, 0.0400000, 0.0166670, 0.0076920, 0.0046510, 0.0024690, 0.0013330, 0.0007300, 0.0003960, 0.0002150};
                std::copy(std::begin(src), std::end(src), std::begin(this->fail_ext_succeed_prob));
                break;
            }
        }
    }
};

class EquipementItem : public Item
{
public:
    unsigned int refine_level = 0;

private:
    EquipementItem() : Item() {}
public:
    EquipementItem(unsigned int id, std::string name)
        : Item(id, name, 0, 1) {}

    virtual std::string toString() const override
    {
        std::ostringstream oss;
        oss << this->name;
        if (this->refine_level > 0)
        {
            oss << " +" << this->refine_level;
        }
        return oss.str();
    }
};
