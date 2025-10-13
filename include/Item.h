#pragma once
#include "glm/glm.hpp"
#include <string>

enum class itemType {
    WEAPON,
    ARMOR,
    CONSUMABLE,
    QUEST,
    KEY,
    MISC,
    NONE
};

class Item {

    public:
        std::string name;
        itemType type;
        int id;
        int quantity;


        Item(const std::string &name, itemType type, int id, int quantity);
        ~Item();

        std::string getName() const;
        itemType getType() const;
        int getId() const;
        int getQuantity() const;
        virtual void use();
        
        // Equality operator for std::find
        bool operator==(const Item& other) const {
            return id == other.id;
        }
};