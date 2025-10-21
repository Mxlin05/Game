#include "MoveCallBackMap.h"

using MoveCallback = std::function<void(Player&, GameObject&)>;

std::unordered_map<std::string, MoveCallback> moveCallbacks;

void initializeMoveCallbacks(std::vector<Move>& moves) {
    for (auto& m : moves) {
        std::cout << "Making move callbacks" << std::endl;
        std::cout << "Move name: " << m.name << std::endl;
        moveCallbacks[m.name] = [m](Player& user, GameObject& target) {
            int damage = m.power; 
            std::cout << "used Cut" << std::endl;
            //target.takeDamage(damage); --> need to deal with this
        };


        m.useMove = moveCallbacks[m.name];

    }

    //if m == damage, if m == effect like heal, and physical magic split

}