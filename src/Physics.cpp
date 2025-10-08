#include "Physics.h"
#include <iostream>

//aabb functions
AABB::AABB(size_t id, glm::vec2 min, glm::vec2 max){
    this->id = id;
    this->min = min;
    this->max = max;
}

AABB::~AABB(){
}

glm::vec2 AABB::getMin() const{
    return min;
}

glm::vec2 AABB::getMax() const{
    return max;
}

void AABB::setMin(glm::vec2 min){
    this->min = min;
}

void AABB::setMax(glm::vec2 max){
    this->max = max;
}

bool AABB::operator==(const AABB& other) const{
    return min == other.min && max == other.max;
}


//physics functions 
//Create AABB
std::vector<AABB> Physics::aabbs;

AABB Physics::createAABB(glm::vec2 position, glm::vec2 size){
    return AABB(aabbs.size(), position, position + size);
}

//Check for AABB overlaps
bool Physics::aabbOverlap(AABB a, AABB b){
    glm::vec2 a_min = a.getMin();
    glm::vec2 a_max = a.getMax();
    glm::vec2 b_min = b.getMin();
    glm::vec2 b_max = b.getMax();

    //std::cout << "a_min.x: " << a_min.x << " a_max.x: " << a_max.x << " b_min.x: " << b_min.x << " b_max.x: " << b_max.x << std::endl;
    //std::cout << "a_min.y: " << a_min.y << " a_max.y: " << a_max.y << " b_min.y: " << b_min.y << " b_max.y: " << b_max.y << std::endl;
    return (a_min.x < b_max.x && a_max.x > b_min.x && a_min.y < b_max.y && a_max.y > b_min.y);
}

glm::vec2 Physics::aabbResolve(AABB a, AABB b){
    glm::vec2 a_min = a.getMin();
    glm::vec2 a_max = a.getMax();
    glm::vec2 b_min = b.getMin();
    glm::vec2 b_max = b.getMax();
    
    float left_overlap = a_max.x - b_min.x;
    float right_overlap = b_max.x - a_min.x;
    float top_overlap = b_max.y - a_min.y;
    float bottom_overlap = a_max.y - b_min.y;

    float min_overlap_x = (std::abs(left_overlap) < std::abs(right_overlap)) ? left_overlap : right_overlap; 
    float min_overlap_y = (std::abs(top_overlap) < std::abs(bottom_overlap)) ? top_overlap : bottom_overlap;
    //should only push one axis at a time
    if (std::abs(min_overlap_x) < std::abs(min_overlap_y)){
        return glm::vec2(min_overlap_x, 0.0f);
    } else {
        return glm::vec2(0.0f, min_overlap_y);
    }
}

void Physics::addAABB(AABB aabb){
    aabbs.push_back(aabb);
}

void Physics::removeAABB(AABB aabb){
    aabbs.erase(std::remove(aabbs.begin(), aabbs.end(), aabb), aabbs.end());
}

void Physics::clearAABBs(){
    aabbs.clear();
}

void Physics::updateAABB(size_t id, glm::vec2 position, glm::vec2 size){
    AABB* aabb = getAABB_byID_ptr(id);
    if (aabb == nullptr){
        return;
    }
    aabb->setMin(position);
    aabb->setMax(position + size);
}

size_t Physics::getAABBCount(){
    return aabbs.size();
}

AABB Physics::getAABB_byID(size_t ID){
    for (size_t i = 0; i < aabbs.size(); i++){
        if (aabbs[i].id == ID){
            return aabbs[i];
        }
    }
    return AABB(0, glm::vec2(0,0), glm::vec2(0,0));
}

AABB* Physics::getAABB_byID_ptr(size_t ID){
    for (size_t i = 0; i < aabbs.size(); i++){
        if (aabbs[i].id == ID){
            return &aabbs[i];
        }
    }
    return nullptr;
}