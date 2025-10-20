#include "Item.h"


enum class weaponType {
    SWORD,
    BOW,
    SPEAR,
    AXE,
    STAFF,
    DAGGER,
    MACE,
    NONE
};

class Weapon : public Item {
    
    public:
        int damage;
        weaponType wType;

        Weapon(const std::string &name, int id, int quantity, int damage, weaponType wType);
        ~Weapon();

        int getDamage() const;
        weaponType getType() const;

        void use() override;
};