#include "Move.h"

std::vector<Move> loadMovesFromCSV(const std::string& filename){
    std::vector<Move> moves;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file: " << filename << std::endl;
        return moves;  //we r fucked
    }
    
    std::getline(file, line);

    while (std::getline(file, line)) {

        std::cout << "Reaches starting to read file" << std::endl;
        std::stringstream ss(line);
        std::string item;
        Move m;

        std::getline(ss, item, ','); m.id = std::stoi(item);

        std::getline(ss, m.name, ',');
        std::getline(ss, item, ','); m.power = std::stoi(item);
        std::getline(ss, item, ','); m.mpCost = std::stoi(item);
        std::getline(ss, m.damageType, ',');
        std::getline(ss, m.effect, ',');


        moves.push_back(m);
    }
    return moves;
}