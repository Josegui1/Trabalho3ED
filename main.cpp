#include "Matchmaking.hpp"
#include "Player.hpp"
#include <iostream>
#include <chrono>

// Imprime um array de jogadores com título
void printGroup(Player* group, int n, const std::string& title){
    std::cout << title << std::endl;
    if(group == nullptr || n == 0){
        std::cout << "(nenhum grupo formado)" << std::endl;
    } else {
        for(int i = 0; i < n; i++){
            std::cout << "[" << group[i].getId() << " | "
                      << group[i].getName() << " | "
                      << group[i].getScore() << " | "
                      << group[i].getTimestamp() << "]" << std::endl;
        }
    }
    std::cout << std::endl;
}

// ─────────────────────────────────────────────
// Questão 1-3: insert, remove, construtor/destrutor
// ─────────────────────────────────────────────
void testeInsercaoRemocao(){
    std::cout << "=== Teste: Insercao e Remocao ===" << std::endl;

    // Alocamos no heap porque Player players[MAX_PLAYERS] é muito grande para a pilha
    Matchmaking* mm = new Matchmaking();

    bool r1 = mm->insert(Player(1, "Ana",   1000, 1));
    bool r2 = mm->insert(Player(2, "Bruno", 1100, 2));
    bool r3 = mm->insert(Player(3, "Carla", 1020, 3));

    std::cout << "insersoes (esperado true true true): "
              << r1 << " " << r2 << " " << r3 << std::endl;

    std::cout << "Após insersoes:" << std::endl;
    mm->printWaitingPlayers();

    bool rem1 = mm->removePlayer(2);
    bool rem2 = mm->removePlayer(99); // ID inexistente

    std::cout << "remocoes ID=2 (esperado true): "  << rem1 << std::endl;
    std::cout << "remocoes ID=99 (esperado false): " << rem2 << std::endl;

    std::cout << "Após remocoes:" << std::endl;
    mm->printWaitingPlayers();
    std::cout << std::endl;

    delete mm;
}

// ─────────────────────────────────────────────
// Questão 4: ordenação sem empate
// ─────────────────────────────────────────────
void testeOrdenacao(){
    std::cout << "=== Teste: Ordenacao (Insertion Sort) ===" << std::endl;

    Matchmaking* mm = new Matchmaking();
    mm->insert(Player(1, "Ana",   1000, 1));
    mm->insert(Player(2, "Bruno", 1100, 2));
    mm->insert(Player(3, "Carla", 1020, 3));
    mm->insert(Player(4, "Diego", 1010, 4));

    std::cout << "Antes da ordenacao:" << std::endl;
    mm->printWaitingPlayers();

    mm->sortByScoreInsertion();
    std::cout << "Após sortByScoreInsertion (esperado: Ana, Diego, Carla, Bruno):" << std::endl;
    mm->printWaitingPlayers();
    delete mm;

    std::cout << "=== Teste: Ordenacao (Merge Sort) ===" << std::endl;

    Matchmaking* mm2 = new Matchmaking();
    mm2->insert(Player(1, "Ana",   1000, 1));
    mm2->insert(Player(2, "Bruno", 1100, 2));
    mm2->insert(Player(3, "Carla", 1020, 3));
    mm2->insert(Player(4, "Diego", 1010, 4));

    mm2->sortByScoreMerge();
    std::cout << "Após sortByScoreMerge (esperado: Ana, Diego, Carla, Bruno):" << std::endl;
    mm2->printWaitingPlayers();
    delete mm2;
}

// ─────────────────────────────────────────────
// Questão 4: ordenação com empate de score
// ─────────────────────────────────────────────
void testeOrdenacaoEmpate(){
    std::cout << "=== Teste: Ordenacao com Empate ===" << std::endl;

    Matchmaking* mm = new Matchmaking();
    mm->insert(Player(1, "Ana",   1000, 5));
    mm->insert(Player(2, "Bruno", 900,  2));
    mm->insert(Player(3, "Carla", 1000, 1));
    mm->insert(Player(4, "Diego", 900,  4));

    std::cout << "Antes:" << std::endl;
    mm->printWaitingPlayers();

    mm->sortByScoreMerge();
    std::cout << "Após ordenacao (esperado: Bruno ts=2, Diego ts=4, Carla ts=1, Ana ts=5):" << std::endl;
    mm->printWaitingPlayers();
    delete mm;
}

// ─────────────────────────────────────────────
// Questão 5: formGroup bem-sucedido
// ─────────────────────────────────────────────
void testeFormGroupSucesso(){
    std::cout << "=== Teste: formGroup (sucesso) ===" << std::endl;

    Matchmaking* mm = new Matchmaking();
    mm->insert(Player(1, "Ana",   1000, 1));
    mm->insert(Player(4, "Diego", 1010, 4));
    mm->insert(Player(3, "Carla", 1020, 3));
    mm->insert(Player(2, "Bruno", 1100, 2));
    mm->sortByScoreMerge();

    std::cout << "Fila ordenada:" << std::endl;
    mm->printWaitingPlayers();

    int n = 0;
    // groupSize=3, delta=30: Ana(1000), Diego(1010), Carla(1020) → diff=20 ≤ 30 ✓
    Player* group = mm->formGroup(3, 30, &n);
    printGroup(group, n, "Grupo formado (esperado: Ana, Diego, Carla):");
    delete[] group;

    std::cout << "Fila restante (esperado: Bruno):" << std::endl;
    mm->printWaitingPlayers();
    delete mm;
}

// ─────────────────────────────────────────────
// Questão 5: formGroup sem sucesso
// ─────────────────────────────────────────────
void testeFormGroupFalha(){
    std::cout << "=== Teste: formGroup (sem sucesso) ===" << std::endl;

    Matchmaking* mm = new Matchmaking();
    mm->insert(Player(1, "Ana",   1000, 1));
    mm->insert(Player(2, "Bruno", 1100, 2));
    mm->insert(Player(3, "Carla", 1300, 3));
    mm->sortByScoreMerge();

    std::cout << "Fila ordenada:" << std::endl;
    mm->printWaitingPlayers();

    int n = 0;
    // delta=30: diferenças são 100 e 200 → nenhuma janela válida
    Player* group = mm->formGroup(3, 30, &n);
    printGroup(group, n, "Grupo formado (esperado: nenhum):");

    std::cout << "Fila apos tentativa falha (deve permanecer igual):" << std::endl;
    mm->printWaitingPlayers();
    delete mm;
}

// ─────────────────────────────────────────────
// Questão 6: getWaitingPlayers
// ─────────────────────────────────────────────
void testeGetWaitingPlayers(){
    std::cout << "=== Teste: getWaitingPlayers ===" << std::endl;

    Matchmaking* mm = new Matchmaking();
    mm->insert(Player(1, "Ana",   1000, 1));
    mm->insert(Player(2, "Bruno", 900,  2));

    int n = 0;
    Player* waiting = mm->getWaitingPlayers(&n);

    std::cout << "Jogadores retornados (n=" << n << "):" << std::endl;
    for(int i = 0; i < n; i++){
        std::cout << "[" << waiting[i].getId() << " | "
                  << waiting[i].getName() << " | "
                  << waiting[i].getScore() << "]" << std::endl;
    }
    delete[] waiting;
    delete mm;

    // Fila vazia
    Matchmaking* mm2 = new Matchmaking();
    Player* empty = mm2->getWaitingPlayers(&n);
    std::cout << "Fila vazia — retorno nullptr: " << (empty == nullptr ? "sim" : "não")
              << ", n=" << n << std::endl;
    std::cout << std::endl;
    delete mm2;
}

// ─────────────────────────────────────────────
// Questão 7: printWaitingPlayers (fila vazia)
// ─────────────────────────────────────────────
void testePrintVazio(){
    std::cout << "=== Teste: printWaitingPlayers (vazio) ===" << std::endl;
    Matchmaking* mm = new Matchmaking();
    mm->printWaitingPlayers();
    std::cout << std::endl;
    delete mm;
}

// ─────────────────────────────────────────────
// Questão 8: Teste de desempenho (insertion sort vs merge sort)
// Entrada em ordem decrescente (pior caso para insertion sort).
// ─────────────────────────────────────────────
void testeDesempenho(){
    std::cout << "=== Teste de Desempenho ===" << std::endl;
    std::cout << "Entrada em ordem decrescente (pior caso para insertion sort)" << std::endl;
    std::cout << std::endl;

    int sizes[] = {1000, 5000, 10000, 50000, 100000};
    int numSizes = 5;

    std::cout << "Tamanho\t\tInsertion Sort\t\tMerge Sort" << std::endl;
    std::cout << "-------\t\t--------------\t\t----------" << std::endl;

    for(int s = 0; s < numSizes; s++){
        int n = sizes[s];

        Matchmaking* mm1 = new Matchmaking();
        Matchmaking* mm2 = new Matchmaking();

        for(int i = 0; i < n; i++){
            Player p(i, "P", n - i, i); // scores decrescentes → pior caso
            mm1->insert(p);
            mm2->insert(p);
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        mm1->sortByScoreInsertion();
        auto t2 = std::chrono::high_resolution_clock::now();
        double ms_insertion = std::chrono::duration<double, std::milli>(t2 - t1).count();

        auto t3 = std::chrono::high_resolution_clock::now();
        mm2->sortByScoreMerge();
        auto t4 = std::chrono::high_resolution_clock::now();
        double ms_merge = std::chrono::duration<double, std::milli>(t4 - t3).count();

        std::cout << n << "\t\t"
                  << ms_insertion << " ms\t\t\t"
                  << ms_merge << " ms" << std::endl;

        delete mm1;
        delete mm2;
    }
    std::cout << std::endl;
}

int main(){
    testeInsercaoRemocao();
    testeOrdenacao();
    testeOrdenacaoEmpate();
    testeFormGroupSucesso();
    testeFormGroupFalha();
    testeGetWaitingPlayers();
    testePrintVazio();
    testeDesempenho();

    return 0;
}