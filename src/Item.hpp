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
    RefineEssence() {}
public:
    RefineEssence(EssenceType type)
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
    EquipementItem() {}
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

struct EquipementData
{
    unsigned int id;
    std:: string name;
};

EquipementData qipementPool[] = {
    { 1000, "Dragon daggers" },
    { 1001, "Shadow Legend" },
    { 1002, "Rampager Thorn" },
    { 1003, "Doomfate Daggers" },
    { 1004, "Phantom Twilight" },
    { 1005, "Swiftwind Chest" },
    { 1006, "Decaying Snow Vest" },
    { 1007, "Armor of Millenary Bless" },
    { 1008, "Armor of Charger's Pride" },
    { 1009, "Abyssal Armor" },
    { 1010, "Zombie Warrior Leggings" },
    { 1011, "Dark Shinguards of Hades" },
    { 1012, "Lunar Chaser Shins" },
    { 1013, "Demonhunter Breeches" },
    { 1014, "Catastrophe Leggings" },
    { 1015, "Sorrowfree Light Boots" },
    { 1016, "Lion Heart Boots" },
    { 1017, "Damnation Boots" },
    { 1018, "Sun Destroyer Boots" },
    { 1019, "Ashura Boots of Courage" },
    { 1020, "Helm of Grand Elimination" },
    { 1021, "Counterstream Heavy Helm" },
    { 1022, "Helmet of Pirate" },
    { 1023, "Lunar Helm" },
    { 1024, "Ashura Helm of Courage" },
    { 1025, "Duke Light Wristguards" },
    { 1026, "Swiftwind Bracers" },
    { 1027, "Skywalker Bracers" },
    { 1028, "Underworld Floe" },
    { 1029, "Demonhunter Vambraces" },
    { 1030, "Cloak of Blaze" },
    { 1031, "Foghide Blade Cloak" },
    { 1032, "Matchless Wings" },
    { 1033, "Moonshade Cape" },
    { 1034, "Phoenix Plume" },
    { 1035, "Royal Ring" },
    { 1036, "Poltergeist Ring" },
    { 1037, "Thunderclap Ring" },
    { 1038, "Matchless Ring" },
    { 1039, "Sign of Frost" },
    { 1040, "Shady Blade" },
    { 1041, "Bloodtooth Blade" },
    { 1042, "Dragonblade" },
    { 1043, "Chrono Breaker" },
    { 1044, "Brahma's Lash" },
    { 1045, "Raging Lion Claws" },
    { 1046, "Heraldry Axes" },
    { 1047, "Calamity Axes of Blood" },
    { 1048, "Master's Axe" },
    { 1049, "Dragonhunt" },
    { 1050, "Warsong Axes" }
};