#include "hash.h"
#include "board.h"
#include "fatal.h"
#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

// Função para procurar palavras no tabuleiro
void searchWords(const char board[BOARD_SIZE][BOARD_SIZE], int visited[BOARD_SIZE][BOARD_SIZE], LinHashTable WordTable, LinHashTable PrefixTable, char* key, Position currentPosition, Position positions[], int wordLength, int* solutionCount, Position* firstPosition) {
    int newRow, newCol;
    int directions[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

    visited[currentPosition.row][currentPosition.col] = 1;
    positions[wordLength - 1] = currentPosition;

    // Verifica se a palavra é encontrada na tabela de hash WordTable ou PrefixTable
    if (Find(key, PrefixTable) || Find(key, WordTable)) {
        // Se a palavra for encontrada na tabela H
        if (Find(key, WordTable)) {
            // Verifica se a palavra tem tamanho maior que 2
            if (strlen(key) > 2) {
                printf("%s ", key);
                // Imprime as posições das letras da palavra no tabuleiro
                for (int i = 1; i <= wordLength; i++) {
                    if (i == wordLength)
                        printf("%c:(%d,%d)", board[positions[i-1].row][positions[i-1].col], positions[i-1].row, positions[i-1].col);
                    else
                        printf("%c:(%d,%d)-> ", board[positions[i-1].row][positions[i-1].col], positions[i-1].row, positions[i-1].col);
                }
                printf("\n");
                (*solutionCount)++;
                // Atualiza a primeira posição se for a primeira solução encontrada
                if (*solutionCount == 1) {
                    *firstPosition = positions[0];
                }
            }
        }

        // Explora as posições vizinhas recursivamente
        for (int i = 0; i < 8; i++) {
            newRow = currentPosition.row + directions[i][0];
            newCol = currentPosition.col + directions[i][1];

            // Verifica se a nova posição é válida e não foi visitada
            if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE && !visited[newRow][newCol]) {
                Position newPosition;
                newPosition.row = newRow;
                newPosition.col = newCol;

                key[wordLength] = board[newRow][newCol];
                key[wordLength + 1] = '\0';

                // Chamada recursiva para explorar a nova posição
                searchWords(board, visited, WordTable, PrefixTable, key, newPosition, positions, wordLength + 1, solutionCount, firstPosition);
            }
        }
    }

    visited[currentPosition.row][currentPosition.col] = 0;

    // Verifica se encontrou uma solução e atualiza a primeira posição
    if (*solutionCount == 1) {
        *firstPosition = positions[0];
    }
}

// Função para imprimir o tabuleiro
void printBoard(const char board[BOARD_SIZE][BOARD_SIZE]) {
    printf("******************\n");
    printf("*   B O G G L E  *\n");
    printf("******************\n");
    printf("*     0  1  2  3 *\n");
    for (int row = 0; row < BOARD_SIZE; row++) {
        printf("* %d   ", row);
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (col == 3)
                printf("%c *", board[row][col]);
            else
                printf("%c  ", board[row][col]);
        }
        printf("\n");
    }
    printf("******************\n");
}

// Função para carregar o tabuleiro a partir de um arquivo
void loadBoardFromFile(const char* filename, char board[BOARD_SIZE][BOARD_SIZE]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        exit(1);
    }

    char line[100];
    int row = 0;
    while (fgets(line, sizeof(line), file) != NULL && row < BOARD_SIZE) {
        char* token = strtok(line, " ");
        int col = 0;
        while (token != NULL && col < BOARD_SIZE) {
            board[row][col] = token[0];
            col++;
            token = strtok(NULL, " ");
        }
        row++;
    }

    fclose(file);
}