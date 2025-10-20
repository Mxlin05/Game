#include "Item.h"


enum class armorType {
    HELMET,
    CHESTPLATE,
    LEGGINS,
    BOOTS,
    SHIELD,
    RING,
    AMULET,
    NONE
};

class Armor : public Item {
    
    public:
        int ArnmorRating;
        armorType aType;

        //maybe add extra stats for things like rings and shit

        Armor(const std::string &name, int id, int quantity, int ArnmorRating, armorType aType);
        ~Armor();

        int getArmorRating() const;
        armorType getType() const;

        void use() override;
};