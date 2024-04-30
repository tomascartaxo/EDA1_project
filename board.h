#include "estruturas.h"
#include "hash.h"

void loadBoardFromFile(const char* filename, char board[BOARD_SIZE][BOARD_SIZE]);
void printBoard(const char board[BOARD_SIZE][BOARD_SIZE]);
void searchWords(const char board[BOARD_SIZE][BOARD_SIZE], int visited[BOARD_SIZE][BOARD_SIZE], LinHashTable WordTable, LinHashTable PrefixTable, char* key, Position currentPosition, Position positions[], int wordLength, int* solutionCount, Position* firstPosition);
