// #ifndef __BTREE_H
// #define __BTREE_H
// #include <stdio.h>
// #include <stdlib.h>
// #include "record.h"

// typedef struct entry Entry;
// typedef struct st_node ST_Node;

// void STinit(ST_Node **head, int *H, int M);
// void STinsert(ST_Node **head, Item item, int *H, int M);
// Item searchR(ST_Node *head, Key v, int H);

// #endif
#ifndef _BTREE_H
#define _BTREE_H

#include "record.h"

typedef struct STnode* Link;

/*Cria um nova B-tree*/
Link STinit(int M);

/*Insere item na B-tree*/
Link STinsert(Item item, Link head);

/*Procura um item na B-tree*/
Item STsearch(Key key, Link head);

/*Libera a B-tree*/
void freeST(Link head);

/*Percorre a B-tree e aplica callItem nos itens*/
void runST(Link head, void (*callItem)(Item, void*, void*), void* callArg1, void* callArg2);

int eq(char *a, char *b);
int less(char *a, char *b);

Item searchR(Link h, Key v, int H);
Link split(Link h);
Link insertR(Link h, Item item, int H);

#endif