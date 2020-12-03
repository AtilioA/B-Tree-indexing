#ifndef __BTREE_H
#define __BTREE_H
#include <stdio.h>
#include <stdlib.h>
#include "record.h"

typedef struct entry Entry;
typedef struct st_node ST_Node;

void STinit(ST_Node **head, int *H, int M);
void STinsert(ST_Node **head, Record item, int *H, int M);
Record searchR(ST_Node *head, Key v, int H);

#endif
