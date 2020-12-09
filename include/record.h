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

Record RECORDget(FILE *fp, long int fileIndex);

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

int ITEMscan(Key *);

void ITEMshow(Item);

void ITEMfree(Item);

void ITEMprint(Item x);

long int ITEMgetPos(Item x);

int ITEMisActive(Item x);

#define NULLitem NULL
#define key(A) (A->id)
#define num(A) (A->fileIndex)

#endif
