#pragma once
#include <vector>
#include "Item.h"
#include <string>

class Inventory {

    public:
        std::vector<Item> items;
        Inventory();
        ~Inventory();

        void addItem(const Item &item);
        void removeItem(int id);
        Item getItem(int id);
        std::string listItems() const;

        //load from file?
};