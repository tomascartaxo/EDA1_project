#include "hash.h"
#include "estruturas.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função auxiliar para encontrar o próximo número primo
static int NextPrime(int N) {
    int i, j;
    bool isPrime;
    if (N <= 2)
        return 2;
    if (N % 2 == 0)
        i = N + 1;
    else
        i = N;
    while (true) {
        isPrime = true;
        for (j = 3; j * j <= i; j += 2) {
            if (i % j == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime)
            return i;
        i += 2;
    }
}

// Função de hash simples
Index Hash(const char* Key, int TableSize) {
    unsigned int hv = 0;
    while (*Key != '\0')
        hv = (hv << 5) + *Key++;
    return hv % TableSize;
}

// Função para inicializar a tabela de hash linear
LinHashTable InitializeTable(int TableSize) {
    LinHashTable H;
    int i;

    if (TableSize < MinTableSize) {
        printf("Table size too small\n");
        return NULL;
    }

    H = malloc(sizeof(struct HashTbl));
    if (H == NULL) {
        printf("Out of space!!!\n");
        return NULL;
    }

    H->TableSize = NextPrime(TableSize);
    H->Ocupados = 0;

    H->TheCells = malloc(sizeof(Cell) * H->TableSize);
    if (H->TheCells == NULL) {
        printf("Out of space!!!\n");
        free(H);
        return NULL;
    }

    for (i = 0; i < H->TableSize; i++) {
        H->TheCells[i].Info = Empty;
        H->TheCells[i].Element = NULL;
    }
    return H;
}

// Função para encontrar a posição de uma chave na tabela de hash
Index ProcPos(const char* Key, LinHashTable H) {
    Index P = Hash(Key, H->TableSize);
    while (H->TheCells[P].Info != Empty && strcmp(H->TheCells[P].Element, Key) != 0) {
        P = (P + 1) % H->TableSize;
    }
    return P;
}

// Função para verificar se uma chave está presente na tabela de hash
int Find(const char* Key, LinHashTable H) {
    Index P = ProcPos(Key, H);
    if (H->TheCells[P].Info == Legitimate)
        return 1;   
    else
        return 0;
}

// Função para inserir uma chave na tabela de hash
void Insert(const char* Key, LinHashTable H) {
    Index P = ProcPos(Key, H);
    if (H->TheCells[P].Info != Legitimate){
        H->TheCells[P].Info = Legitimate;   
        size_t sz = strlen(Key);                           
        char* new = (char*)calloc(sz + 1, sizeof(char));    
        strcpy(new,Key);                                    
        H->TheCells[P].Element = new;                       
        H->Ocupados++;           
    }
}

// Função para adicionar palavras a partir de um ficheiro na tabela de hash
LinHashTable Add_WordTable(LinHashTable H, const char* ficheiro, int* wordCount) {
    char word[50]="";
    FILE* f = fopen(ficheiro, "r");
    while(fscanf(f, " %s", word) != EOF){   
        Insert(word, H);
        (*wordCount)++;
    }   
    fclose(f);
    return H;
}

// Função para adicionar prefixos a partir de um ficheiro na tabela de hash
LinHashTable Add_PrefixTable(LinHashTable H, const char* ficheiro, int* prefixCount) {
    char word[50];
    int length = 0;
    char word_p[50] = "";
    FILE* f = fopen(ficheiro, "r");
    while (fscanf(f, "%s", word) != EOF) {
        length = strlen(word);
        for (int i = 0; i < length-1; i++){
            strncat(word_p, &word[i], 1);
            Insert(word_p, H);
            (*prefixCount)++;
        }
        strcpy(word_p,"");
    }
    fclose(f);
    return H;
}

// Função para liberar a memória alocada pela tabela de hash
void DestroyTable(LinHashTable H) {
    for (int i = 0; i < H->TableSize; i++)
        free(H->TheCells[i].Element);
    free(H->TheCells);
    free(H);
}
