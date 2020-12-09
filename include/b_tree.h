#ifndef _BTREE_H
#define _BTREE_H

#include "record.h"

typedef struct STnode *Link;

// Cria um nova árvore B
Link STinit(int M);

// Insere um item na árvore B
Link STinsert(Item item, Link head);

// Procura um item na árvore B
Item STsearch(Key key, Link head);

// Libera a árvore B
void freeST(Link head);

// Percorre a árvore B e aplica callItem nos itens
void runST(Link head, void (*callItem)(Item, void *, void *), void *callArg1, void *callArg2);

int eq(char *a, char *b);
int less(char *a, char *b);

// Procura por uma Key v numa árvore h (usada por STsearch)
Item searchR(Link h, Key v, int H);
// Divide um nó árvore h
Link split(Link h);
// Insere um Item item numa árvore h (usada por STinsert)
Link insertR(Link h, Item item, int H);

#endif
