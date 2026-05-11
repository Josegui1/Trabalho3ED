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

// O(1)
bool Matchmaking::comesBefore(Player a, Player b){
    if(a.getScore() < b.getScore()){
        return true;
    }
    if(a.getScore() > b.getScore()){
        return false;
    }
    return a.getTimestamp() < b.getTimestamp();
}

// O(1)
bool Matchmaking::comesBeforeOrEqual(Player a, Player b){
    if(a.getScore() < b.getScore()){
        return true;
    }
    if(a.getScore() > b.getScore()){
        return false;
    }
    return a.getTimestamp() <= b.getTimestamp();
}

// O(n²)
void Matchmaking::sortByScoreInsertion(){
    for (int i = 1; i < size; i++){
        Player key = players[i];
        int j = i - 1;

        while(j >= 0 && comesBefore(key, players[j])){
            players[j+1] = players[j];
            j--;
        }
        players[j+1] = key;
    }
}

// O(nlog(n)), mas ceja que possui um custo adicional de ordem O(n) por conta da cópia
void Matchmaking::sortByScoreMerge(){
    if (size<=1){
        return;
    }

    Player* sorted = mergeSort(players, size);
    for(int i = 0; i < size; i++){
        players[i] = sorted[i];
    }

    delete[] sorted;
}

// O(nlog(n))
Player* Matchmaking::mergeSort(Player arr[], int n){
    if (n==1){
        Player* single = new Player[1];
        single[0] = arr[0];
        return single;
    }

    int mid = n/2;
    Player* left = mergeSort(arr, mid);
    Player* right = mergeSort(arr + mid, n - mid);

    Player* sorted = merge(left, mid, right, n-mid);  
    delete[] left;
    delete[] right;

    return sorted;
}

// O(n+m)
Player* Matchmaking::merge(Player arr1[], int n, Player arr2[], int m){
    Player* mArr = new Player[n+m];
    int i = 0;
    int j = 0;

    while(i < n && j < m){
        if(comesBeforeOrEqual(arr1[i], arr2[j])){
            mArr[i+j] = arr1[i];
            i++;
        }
        else{
            mArr[i+j] = arr2[j];
            j++;
        }
    }

    while(i < n){
        mArr[i+j] = arr1[i];
        i++;
    }

    while(j < m){
        mArr[i+j] = arr2[j];
        j++;
    }

    return mArr;
}

// O(n)
void Matchmaking::printWaitingPlayers(){
    if(size==0){
        std::cout << "(empty)" << std::endl;
        return;
    }

    for (int i = 0; i < size; i++){
        std::cout << "[" << players[i].getId() << "|" << players[i].getName() << "|" << players[i].getScore() << "|" << players[i].getTimestamp()<< "]" << std::endl;
    }
}

Player* Matchmaking::formGroup(int groupSize, int delta, int* n){
    // verifica se tem jogadores suficientes
    if(size < groupSize){
        *n = 0;
        return nullptr;
    }
        // anda pelo intervalo dos jogadores 
    for(int i = 0; i <= size - groupSize; i++){

        int menorScore = players[i].getScore();
        int maiorScore = players[i + groupSize - 1].getScore();

        // verifica se os jogadores podem jogar juntos
        if(maiorScore - menorScore <= delta){
            *n = groupSize;
            Player* grupo = new Player[groupSize];

            //copia os jogadores pra Um novo array dinamico
            for (int j = 0; j < groupSize; j++){
                grupo[j] = grupo[i + j];
            }
            // remove os jogares selecionados da fila
            for (int k = i + groupSize; k < size; k++){
                players[k - groupSize] = players[k];
            }

            size -= groupSize;
            return grupo;

        }
    }
    // se nao achou um grupo valido
    *n = 0;
    return nullptr;
}



