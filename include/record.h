#ifndef __ITEM_H
#define __ITEM_H

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