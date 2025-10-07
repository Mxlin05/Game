#include "Armor.h"

Armor::Armor(const std::string &name, int id, int quantity, int ArnmorRating, armorType aType)
    : Item(name, itemType::ARMOR, id, quantity), ArnmorRating(ArnmorRating), aType(aType) {
}

Armor::~Armor() {}

int Armor::getArmorRating() const {
    return ArnmorRating;
}

armorType Armor::getType() const {
    return aType;
}

void Armor::use(){
    //add logic
}