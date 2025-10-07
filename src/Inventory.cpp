#include "Inventory.h"
#include <algorithm>

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
                items.erase(std::remove(items.begin(), items.end(), i), items.end());
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
}

//will add later
std::string Inventory::listItems() const{

}