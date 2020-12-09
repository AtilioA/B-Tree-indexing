#ifndef __RECORD_H
#define __RECORD_H

#include <string.h>
#include <stdio.h>

struct record
{
    char *id;
    char *value;
};

typedef struct record *Record;

typedef char *Key;
struct index
{
    Key id;
    int active;
    long int fileIndex;
};
typedef struct index *Item;

// Cria um Record
Record RECORDcreate(char *id, char *value);

// Libera um Record
void RECORDfree(Record);

// Imprime um Record
void RECORDprint(Record x);

// Escreve um Record num arquivo
void RECORDprintToFile(Record x, FILE *fp);

// Cria um Item sobre um registro no arquivo, dada a posição e se está ativo ou não
Item ITEMcreate(char *id, long pos, int active);

// Libera um item da memória
void ITEMfree(Item);

// Imprime um item
void ITEMprint(Item x);

#define NULLitem NULL
#define key(A) (A->id)

#endif
