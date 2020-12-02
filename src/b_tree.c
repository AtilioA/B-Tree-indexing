// INCOMPLETO

#include <stdio.h>
#include <stdlib.h>
#include "../include/record.h"

typedef struct st_node ST_Node;
typedef struct entry Entry;
struct ST_Node
{
    Entry *b;
    int m;
};
typedef struct ST_Node *link;

struct entry
{
    Key key;
    Item item;
    link next;
};

static link head;
static int H, N;

link createLink()
{
    link x = malloc(sizeof *x);
    x->m = 0;
    return x;
}

void STinit(int maxN)
{
    head = createLink();
    H = 0;
    N = 0;
}

Item searchR(link h, Key v, int H)
{
    int j;
    if (H == 0)
        for (j = 0; j < h->m; j++)
            if (eq(v, h->b[j].key))
                return h->b[j].item;
    if (H != 0)
        for (j = 0; j < h->m; j++)
            if ((j + 1 == h->m) || less(v, h->b[j + 1].key))
                return searchR(h->b[j].next, v, H - 1);
    return NULL;
}

// Item STsearch(Key v)
// {
//     return searchR(head, v, H);
// }

link split(link h, int M)
{
    int j;
    link t = createLink();
    for (j = 0; j < M / 2; j++)
        t->b[j] = h->b[M/2+j];
    h->m = M/2; t->m = M/2; 
    return t;
}

link insertR(link h, Item item, int H, int M)
{
    int i, j;
    Key v = key(item);
    Entry x;
    link t, u;
    x.key = v;
    x.item = item;

    if (H == 0)
        for (j = 0; j < h->m; j++)
            if (less(v, h->b[j].key))
                break;
    if (H != 0)
        for (j = 0; j < h->m; j++)
            if ((j + 1 == h->m) || less(v, h->b[j + 1].key))
            {
                t = h->b[j++].next;
                u = insertR(t, item, H - 1, M);
                if (u == NULL)
                    return NULL;
                x.key = u->b[0].key;
                x.next = u;
                break;
            }

    for (i = (h->m)++; i > j; i--)
        h->b[i] = h->b[i - 1];
    h->b[j] = x;
    if (h->m < M)
        return NULL;
    else
        return split(h, M);
}

void STinsert(link head, Item item, int H, int M)
{
    link t, u = insertR(head, item, H, M);
    if (u == NULL)
        return;
    t = createLink();
    t->m = 2;
    t->b[0].key = head->b[0].key;
    t->b[0].next = head;
    t->b[1].key = u->b[0].key;
    t->b[1].next = u;
    head = t;
    H++;
}