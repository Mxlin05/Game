#include "Item.h"

Item::Item(const std::string &name, itemType type, int id, int quantity)
    : name(name), type(type), id(id), quantity(quantity)
    {

    }

Item::~Item() {}

std::string Item::getName() const {
    return name;
}

itemType Item::getType() const {
    return type;
}

int Item::getId() const {
    return id;
}

int Item::getQuantity() const {
    return quantity;
}

void Item::use(){
    
}