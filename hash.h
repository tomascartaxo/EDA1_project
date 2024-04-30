#include <stdbool.h>
typedef const char* ElementType;
#define MinTableSize (10)
#ifndef _HashLin_H
#define _HashLin_H

typedef unsigned int Index;
typedef Index Position2;

struct HashTbl;
typedef struct HashTbl *LinHashTable;
enum KindOfEntry { Legitimate, Empty, Deleted };

struct HashEntry {
    char* Element;
    enum KindOfEntry Info;
};

typedef struct HashEntry Cell;

struct HashTbl {
    int Ocupados;
    int TableSize;
    Cell* TheCells;
};

LinHashTable InitializeTable( int TableSize );
Position2 ProcPos( ElementType Key, LinHashTable H );
int Find(ElementType Key, LinHashTable H );
void Insert( ElementType Key, LinHashTable H );
LinHashTable Add_WordTable(LinHashTable H, const char* ficheiro, int* wordCount);
LinHashTable Add_PrefixTable(LinHashTable H, const char* ficheiro, int* prefixCount);
void DestroyTable( LinHashTable H );
#endif  