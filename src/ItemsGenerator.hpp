#pragma once

#include <random>
#include "Item.hpp"



struct EquipementData
{
    unsigned int id;
    std:: string name;
};

EquipementData equipementPool[] = {
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


class ItemsGenerator
{
private:
    static std::random_device rd;
public:
    static std::unique_ptr<const Item> getRandomEquipementItem()
    {
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<float> distr(0.0, 1.0);
        float rnd = distr(eng);
        int index = static_cast<int>(std::floor(rnd * sizeof(equipementPool)));
        Item* item = new EquipementItem(equipementPool[index].id, equipementPool[index].name);
        return std::make_unique<const Item>(item);
    }

};
