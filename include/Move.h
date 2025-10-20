#pragma once
#include <string>
#include <functional>
#include "GameObject.h"


class Player;

struct Move {
    int id;
    std::string name;
    int power;
    int mpCost;
    std::string damageType;
    std::string effect;

    std::function<void(Player&, GameObject&)> useMove;
};


