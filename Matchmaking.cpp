#include "Matchmaking.hpp"
#include <iostream>

//O(1)
Matchmaking::Matchmaking(){
    size = 0;
}

// ?
Matchmaking::~Matchmaking(){
}

// O(1)
bool Matchmaking::insert(Player player){
    if(size==MAX_PLAYERS){
        return false;
    }

    players[size] = player;
    size++;

    return true;
}
// O(n)
bool Matchmaking::removePlayer(int id){
    for (int i = 0; i < size; i++){

        if(players[i].getId() == id){
            for (int j = i; j < size-1; j++){
                players[j] = players[j+1];
            }

            size--;
            return true;
        }
    }
    return false;
}