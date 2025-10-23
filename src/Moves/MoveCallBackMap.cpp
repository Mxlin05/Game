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
            std::cout << "move attack power: " << damage << std::endl;

            if (Player* pUser = dynamic_cast<Player*>(&user)) {
                if(m.damageType == "physical"){
                    damage = damage + pUser -> stats.physAttack;
                    std::cout << " user phys attack power: " << user.stats.physAttack << std::endl;
                    std::cout << "phys attack power: " << damage << std::endl;
                }else{
                    damage = damage + pUser -> stats.magicAttack;
                    std::cout << " user phys magic power: " << user.stats.magicAttack << std::endl;
                    std::cout << "magic attack power: " << damage << std::endl;

                }
            }
                // Attempt to downcast user to Enemy
            else if (Enemy* eUser = dynamic_cast<Enemy*>(&user)) {
                if(m.damageType == "physical"){
                    damage = damage + eUser -> stats.physAttack;
                    std::cout << " user phys attack power: " << user.stats.physAttack << std::endl;
                    std::cout << "phys attack power: " << damage << std::endl;
                }else{
                    damage = damage + eUser -> stats.magicAttack;
                    std::cout << " user phys magic power: " << user.stats.magicAttack << std::endl;
                    std::cout << "magic attack power: " << damage << std::endl;

                }
            }

            std::cout << "used Cut" << std::endl;
            std::cout << "damage typr" << m.damageType << std::endl;
            target.takeDamage(damage, m.damageType); 
        };


        m.useMove = moveCallbacks[m.name];

    }

    //if m == damage, if m == effect like heal, and physical magic split

}