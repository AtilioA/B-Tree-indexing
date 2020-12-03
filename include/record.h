#ifndef __RECORD_H
#define __RECORD_H

#include <string.h>

struct record
{
    char *id;
    char *value;
};

typedef struct record *Record;

Record RECORDcreate(char *id, char *value);

void RECORDfree(Record);

Record RECORDget(FILE *fp, long int fileIndex);

void RECORDprint(Record x);

void RECORDprintToFile(Record x, FILE *fp);

typedef char *Key;
struct index
{
    Key id;
    long int fileIndex;
};
typedef struct index *Item;

int ITEMscan(Key *);

void ITEMshow(Item);

void ITEMfree(Item);

#define NULLitem NULL
#define key(A) (A->id)
#define num(A) (A->fileIndex)

#define eq(A, B) (strcmp(A, B) == 0)
#define less(A, B) (strcmp(A, B) < 0)

#endif
