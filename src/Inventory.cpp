#include "Inventory.h"
#include <algorithm>
#include <string>

//PLS FUCKING READ COMMENT
Inventory::Inventory()
{
    //load from a file for player inventory not this right now
    items = std::vector<Item>();
}

Inventory::~Inventory() {}

void Inventory::addItem(const Item &item){
    
    for(auto &i : items){
        if(i.id == item.id){
            i.quantity += item.quantity;
            return;
        }
    }

    //maybe add max inventory size
    items.push_back(item);
    return;

}

//remove based on user input change this later pls
void Inventory::removeItem(int id){
    for(auto &i : items){
        if(i.id == id){
            if(i.quantity > 1){
                i.quantity--;
                return;
            }else{
                // Remove the item from the vector
                for (auto it = items.begin(); it != items.end(); ++it) {
                    if (it->id == i.id) {
                        items.erase(it);
                        break;
                    }
                }
                return;
            }
        }
    }
    return;
}

Item Inventory::getItem(int id){
    for (auto &i : items){
        if(i.id == id){
            return i;
        }
    }
    // Return a default item if not found
    return Item("", itemType::NONE, -1, 0);
}

//will add later
std::string Inventory::listItems() const{
    std::string result = "";
    for (const auto &item : items) {
        result += item.name + " x" + std::to_string(item.quantity) + "\n";
    }
    return result;
}