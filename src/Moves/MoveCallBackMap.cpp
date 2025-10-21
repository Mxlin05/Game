#include "MoveCallBackMap.h"

using MoveCallback = std::function<void(GameObject&, GameObject&)>;

std::unordered_map<std::string, MoveCallback> moveCallbacks;


//need to make this select enemy
void initializeMoveCallbacks(std::vector<Move>& moves) {
    for (auto& m : moves) {
        std::cout << "Making move callbacks" << std::endl;
        std::cout << "Move name: " << m.name << std::endl;
        moveCallbacks[m.name] = [m](GameObject& user, GameObject& target) {
            int damage = m.power; 
            
            if(m.damageType == "physical"){
                damage = damage + user.stats.physAttack;
                std::cout << "phys attack power: " << damage << std::endl;
            }else{
                damage = damage + user.stats.magicAttack;
                std::cout << "magic attack power: " << damage << std::endl;

            }

            std::cout << "used Cut" << std::endl;
            std::cout << "damage typr" << m.damageType << std::endl;
            target.takeDamage(damage, m.damageType); 
        };


        m.useMove = moveCallbacks[m.name];

    }

    //if m == damage, if m == effect like heal, and physical magic split

}