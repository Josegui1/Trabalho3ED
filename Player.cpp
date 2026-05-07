#include "Player.hpp"

// O(1)
Player::Player(){
    id = 0;
    name = "";
    score = 0;
    timestamp = 0;
}

// O(1)
Player::Player(int id, std::string name, int score, int timestamp){
    this->id = id;
    this->name = name;
    this->score = score;
    this->timestamp = timestamp;
}

// O(1)
Player::~Player(){
}

// O(1)
int Player::getId(){
    return id;
}

// O(1)
std::string Player::getName(){
    return name;
}

// O(1)
int Player::getScore(){
    return score;
}

// O(1)
int Player::getTimestamp(){
    return timestamp;
}