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