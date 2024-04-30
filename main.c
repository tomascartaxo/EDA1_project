#include "hash.h"
#include "board.h"
#include "fatal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_1 116239
#define SIZE_2 5346994
#define BOARD_SIZE 4

int main (){
    LinHashTable WordTable = InitializeTable(SIZE_1); // Inicializa a tabela de palavras

    int wordCount = 0; // Contador de palavras
    WordTable = Add_WordTable(WordTable, "corncob_caps_2023.txt", &wordCount); // Adiciona palavras à tabela

    LinHashTable PrefixTable=InitializeTable(SIZE_2); // Inicializa a tabela de prefixos

    int prefixCount = 0; // Contador de prefixos
    PrefixTable = Add_PrefixTable(PrefixTable, "corncob_caps_2023.txt", &prefixCount); // Adiciona prefixos à tabela

    int opcao;
    printf("Que tabuleiro quer utilizar (1 a 3)?\n");
    scanf("%d", &opcao); // Solicita ao utilizador para escolher um tabuleiro

    char board[BOARD_SIZE][BOARD_SIZE]; // Matriz para armazenar o tabuleiro

    switch (opcao) {
    case 1:
        loadBoardFromFile("boggle0.txt", board); // Carrega o tabuleiro a partir de um ficheiro
        break;
    case 2:
        loadBoardFromFile("boggle1.txt", board); 
        break;
    case 3:
        loadBoardFromFile("boggle2.txt", board); 
        break;
    default:
        printf("Opção inválida.\n");
        exit(1);
        break;
    }

    int visited[BOARD_SIZE][BOARD_SIZE] = {0}; // Matriz para rastrear as posições visitadas no tabuleiro

    printBoard(board); // Imprime o tabuleiro

    printf("\n");

    Position positions[BOARD_SIZE * BOARD_SIZE]; // Array para armazenar as posições das palavras encontradas
    int solutionCount = 0; // Contador de soluções
    Position firstPosition; 

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            Position currentPosition;
            currentPosition.row = row;
            currentPosition.col = col;

            char currentWord[50] = "";
            currentWord[0] = board[row][col];
            currentWord[1] = '\0';

            searchWords(board, visited, WordTable, PrefixTable, currentWord, currentPosition, positions, 1, &solutionCount, &firstPosition); 
        }
    }

    printf("\nLidas %d palavras do dicionário\n", wordCount); 
    printf("Encontrados %d prefixos distintos\n", prefixCount);
    printf("Foram encontradas %d soluções\n", solutionCount); 

    DestroyTable(WordTable); // Libera a memória alocada pela tabela de palavras
    DestroyTable(PrefixTable); // Libera a memória alocada pela tabela de prefixos

    return 0;
}