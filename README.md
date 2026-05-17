# Trabalho 3 — Sistema de Matchmaking

Trabalho da disciplina de Estruturas de Dados.

---

## Descrição do projeto

O sistema implementa um **matchmaking** para jogadores que buscam partidas online. Jogadores são armazenados em uma fila de espera e agrupados com base na proximidade de seus scores (nível de habilidade).

Cada jogador possui quatro atributos:

- **id** — identificador único
- **nome** — nome do jogador
- **score** — nível de habilidade
- **timestamp** — ordem de chegada na fila

A ideia central é ordenar os jogadores por score para então buscar grupos válidos com eficiência. Um grupo é válido quando a diferença entre o maior e o menor score do grupo não ultrapassa um valor máximo (`delta`).

---

## Organização dos arquivos

| Arquivo | Descrição |
|---|---|
| `Player.hpp` | Declaração da classe `Player` |
| `Player.cpp` | Implementação da classe `Player` (getters, construtores) |
| `Matchmaking.hpp` | Declaração da classe `Matchmaking` e da constante `MAX_PLAYERS` |
| `Matchmaking.cpp` | Implementação da classe `Matchmaking` (inserção, remoção, ordenação, formação de grupos) |
| `main.cpp` | Casos de teste funcionais e teste de desempenho |

---

## Compilação

No diretório do projeto, execute:

```bash
g++ main.cpp Matchmaking.cpp Player.cpp -o matchmaking
```


---

## Execução

```bash
./matchmaking
```

---

## Testes implementados no `main.cpp`

O `main.cpp` executa os seguintes casos de teste em sequência:

| Função | O que testa |
|---|---|
| `testeInsercaoRemocao()` | Inserção de jogadores e remoção por ID (incluindo ID inexistente) |
| `testeOrdenacao()` | Ordenação por score sem empates — insertion sort e merge sort |
| `testeOrdenacaoEmpate()` | Ordenação com scores iguais (desempate por timestamp) |
| `testeFormGroupSucesso()` | Formação de grupo válido com delta suficiente e remoção dos jogadores da fila |
| `testeFormGroupFalha()` | Tentativa de formação de grupo quando nenhuma janela satisfaz o delta |
| `testeGetWaitingPlayers()` | Cópia dos jogadores em espera (fila com jogadores e fila vazia) |
| `testePrintVazio()` | Exibição da fila quando não há jogadores |
| `testeDesempenho()` | Comparação de tempo entre insertion sort e merge sort para n = 1.000 até 100.000 |

> **Atenção:** todos os objetos `Matchmaking` são alocados no heap (`new`/`delete`) para evitar estouro de pilha, já que o array interno comporta até 100.000 jogadores.
