#pragma once
#include <string>
#include <functional>
// #include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>


class Player;
class GameObject;

struct Move {
    int id;
    std::string name;
    int power;
    int mpCost;
    std::string damageType;
    std::string effect;

    std::function<void(GameObject&, GameObject&)> useMove;
};



// void from_json(const json& j, Move& m) {
//     j.at("id").get_to(m.id);
//     j.at("name").get_to(m.name);
//     j.at("power").get_to(m.power);
//     j.at("mpCost").get_to(m.mpCost);
//     j.at("damageType").get_to(m.damageType);
//     j.at("effect").get_to(m.effect);

// }


// std::vector<Move> loadMoves(const std::string& filePath) {
//     std::ifstream file(filePath);
//     json data;
//     file >> data;

//     std::vector<Move> moves = data.get<std::vector<Move>>();
//     return moves;
// }

#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<Move> loadMovesFromCSV(const std::string& filename); 