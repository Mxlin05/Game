#include "Player.h"
#include "Physics.h"
#include "Global.h"
#include "UIManager.h"

Player::Player(std::string name, Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation)
    : GameObject(sprite, position, size, rotation), name(name), velocity(10.0f, 10.0f), speed(50.0f) {
    registerObjectType("player");
    updateHealth(100);
    updatePhysicalArmor(10);
    updateMagicArmor(10);
    updateBattleSpeed(10);
    updatePhysicalAttack(10);
    updateMagicAttack(10);

}

Player::~Player() {
    Physics::removeAABB(Physics::getAABB_byID(aabbID));
}

void Player::draw(int windowWidth, int windowHeight) const {
    GameObject::draw(windowWidth, windowHeight);
}

void Player::update(const glm::vec2 &move){
    //if player aabb collides iwth any of the aabbs in the array, don't change the position
    glm::vec2 old = position;
    position += move * speed;
    //update the aabb
    //check the updated aabb for collisions
    //no collisions, move on, else resolve the collision
    updateAABB();

    //std::cout << "number of items: " << Physics::getAABBCount() << std::endl;

    for (size_t i = 0; i < Physics::getAABBCount(); i++){
        if (aabbID == Physics::aabbs[i].id){
            //std::cout << "skipping self" << std::endl;
            continue;   
        }
        if (Physics::aabbOverlap(Physics::getAABB_byID(aabbID), Physics::getAABB_byID(i))){
            // Check collision type BEFORE reverting position
            AABB collidingAABB = Physics::getAABB_byID(i);
            auto it = enemyType.find(collidingAABB);
            
            position = old;
            updateAABB();
            
            if (it != enemyType.end()) {
                if (it->second == "enemy") {
                    std::cout << "Player collided with enemy!" << std::endl;
                    // Switch to battle screen
                    g_uiManager.setCurrScreen("Battle");
                    // std::cout << "Attempted to switch to Battle screen" << std::endl;
                }
                else if (it->second == "npc") {
                    std::cout << "Player collided with NPC!" << std::endl;
                    // Add your NPC interaction logic here
                }
                else {
                    std::cout << "Player collided with: " << it->second << std::endl;
                }
            }
            else {
                std::cout << "Player collided with unknown object" << std::endl;
            }
            
            //std::cout << "collision detected" << std::endl;
            
            break;
        }
    }
    //no collisions, move on
}

void Player::updateAABB(){
    if (aabbID >= 0){
        Physics::updateAABB(aabbID, position, size);
    }
}

glm::vec2 Player::getPosition() const {
    //std::cout << "Player position: (" << position.x << ", " << position.y << ")\n";
    return position;
}

void Player::setPosition(const glm::vec2& position){
    this->position = position;
}

void Player::updateHealth(int h){
    stats.health = h;
}

void Player::updatePhysicalArmor(int a){
    stats.armor = a;
}

void Player::updateMagicArmor(int a){
    stats.magicArmor = a;
}

void Player::updateBattleSpeed(int b){
    stats.battleSpeed = b;
}

void Player::updatePhysicalAttack(int a){
    std::cout << " user phys attack power: " << a << std::endl;
    stats.physAttack = a;
    std::cout << " user phys attack power: " << stats.physAttack << std::endl;

}

void Player::updateMagicAttack(int a){
    stats.magicAttack = a;
}

void Player::learnMove(const Move& move) {
    Moves.push_back(move);
}

void Player::useMove(int index){

}

void Player::initMoves(){
    initializeMoveCallbacks(Moves);
}


//WE CAN CHANGE HOW WE DECIDE ON STATS LATER
void Player::takeDamage(int damage, std::string type) {

    int damageTaken = 0; 
    if(type == "physical"){
        damageTaken = damage - stats.armor;
        std::cout << "phys damage: " << damageTaken << std::endl;
    }else if(type == "magic"){
        damageTaken = damage - stats.magicArmor;
        std::cout << "magic damage: " << damageTaken << std::endl;
    }else{
        std::cout << "NEITHER DAMAGE TYPE, WE FUCKED UP" << std::endl;
    }
    
    stats.health = stats.health - damageTaken;
    std::cout << "Player health: " << stats.health << std::endl;
    return;

}

void Player::buffStat(std::vector<int> s) {
    // TODO
}

void Player::debuffStat(std::vector<int> s) {
    // TODO
}

void Player::heal(int amount) {
    // TODO
}

