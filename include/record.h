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

Record RECORDcreate(char *id, char *value);

void RECORDfree(Record);

void RECORDprint(Record x);

void RECORDprintToFile(Record x, FILE *fp);

typedef char *Key;
struct index
{
    Key id;
    int active;
    long int fileIndex;
};
typedef struct index *Item;

Item ITEMcreate(char *id, long pos, int active);

void ITEMfree(Item);

void ITEMprint(Item x);

#define NULLitem NULL
#define key(A) (A->id)

#endif
