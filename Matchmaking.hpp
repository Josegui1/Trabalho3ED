#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include "Player.hpp"

const int MAX_PLAYERS = 100000;

class Matchmaking{
    private:
        Player players[MAX_PLAYERS];
        int size;

        // Algumas funções auxiliares que usaremos
        bool comesBefore(Player a, Player b);
        bool comesBeforeOrEqual(Player a, Player b);
        Player* merge(Player arr1[], int n, Player arr2[], int m);
        Player* mergeSort(Player arr[], int size);

    public:
        Matchmaking();
        ~Matchmaking();

        bool insert(Player player);
        bool removePlayer(int id);

        // Como pedido no markdown do trabalho, manteremos sortByScoreInsertion() com esta assinatura, mas internamente
        // chamaremos a função mergeSort() que fará a ordenação conforme fora ensinada em aula
        void sortByScoreInsertion();
        void sortByScoreMerge();

        Player* formGroup(int groupSize, int delta, int* n);
        Player* getWaitingPlayers(int* n);

        void printWaitingPlayers();

};

#endif 