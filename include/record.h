#ifndef __ITEM_H
#define __ITEM_H
#include <stdio.h>
#include <string.h>

typedef char *Key;
struct index
{
    Key word;
    int occ; 
};
typedef struct index *Item;

int ITEMscan(Key *);
void ITEMshow(Item);

#define NULLitem NULL
#define key(A) (A->word)
#define num(A) (A->occ)

#define eq(A, B) (strcmp(A, B) == 0)
#define less(A, B) (strcmp(A, B) < 0)

#endif