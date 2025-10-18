#include "Weapon.h"

Weapon::Weapon(const std::string &name, int id, int quantity, int damage, weaponType wType)
    : Item(name, itemType::WEAPON, id, quantity), damage(damage), wType(wType) {
}

Weapon::~Weapon() {}

int Weapon::getDamage() const {
    return damage;
}

weaponType Weapon::getType() const {
    return wType;
}

void Weapon::use(){
    //add logic
}