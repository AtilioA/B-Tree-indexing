// INCOMPLETO

#include <stdio.h>
#include <stdlib.h>
#include "include/record.h"

/*static int N;*/
typedef struct entry Entry;
struct st_node
{
    Entry *entry;
    int size;
};
typedef struct st_node ST_Node;
// typedef struct ST_Node ST_Node;

struct entry
{
    Key key;
    Record item;
    ST_Node *next;
};

ST_Node *createLink(int M)
{
    ST_Node *newLink = malloc(sizeof(ST_Node));

    newLink->entry = malloc(M * (sizeof(Entry)));
    newLink->size = 0;

    return newLink;
}

void freeLink(ST_Node *link)
{
    link->size = 0;
    // free(link->entry);
    // free(link);
}

void STinit(ST_Node **head, int *H, int M)
{
    *head = createLink(M);
    *H = 0;
}

Record searchR(ST_Node *head, Key v, int H)
{
    printf("searchR\n");
    int j = 0;
    if (H == 0)
    {
        printf("\tH == 0\n");
        printf("\tj (%i) < head->size (%i)\n", j, head->size);
        for (j = 0; j < head->size; j++)
        {
            printf("\teq(v, head->entry[j].key)\n");
            if (eq(v, head->entry[j].key))
            {
                printf("\t\tVAPO\n");
                return head->entry[j].item;
            }
        }
    }
    if (H != 0)
    {
        printf("\tH != 0\n");
        for (j = 0; j < head->size; j++)
        {
            printf("\tj < head->size (%i)\n", head->size);
            if ((j + 1 == head->size) || less(v, head->entry[j + 1].key))
            {
                printf("\t\tVAPO\n");
                return searchR(head->entry[j].next, v, H - 1);
            }
        }
    }
    return NULL;
}

ST_Node *split(ST_Node *h, int M)
{
    int j;
    ST_Node *t = createLink(M);
    for (j = 0; j < M / 2; j++)
        t->entry[j] = h->entry[M / 2 + j];
    h->size = M / 2;
    t->size = M / 2;
    return t;
}

ST_Node *insertR(ST_Node *h, Record item, int *H, int M)
{
    int i, j;
    Key v = key(item);
    Entry x;
    ST_Node *t, *u;
    x.key = v;
    x.item = item;

    // printf("INICIALIZEI\n");
    if (*H == 0)
    {
        // printf("H == 0\n");
        for (j = 0; j < h->size; j++)
        {
            // printf("\tFOR\n");
            if (less(v, h->entry[j].key))
            {
                // printf("less(v, h->entry[j].key)\n");

                break;
            }
        }
    }
    if (*H != 0)
        for (j = 0; j < h->size; j++)
            if ((j + 1 == h->size) || less(v, h->entry[j + 1].key))
            {
                t = h->entry[j++].next;
                u = insertR(t, item, H - 1, M);
                if (u == NULL)
                    return NULL;
                x.key = u->entry[0].key;
                x.next = u;
                break;
            }

    for (i = (h->size)++; i > j; i--)
        h->entry[i] = h->entry[i - 1];
    h->entry[j] = x;
    if (h->size < M)
        return NULL;
    else
        return split(h, M);
}

void STinsert(ST_Node *head, Record item, int *H, int M)
{
    ST_Node *t, *u = insertR(head, item, H, M);
    printf("INSERTEI\n");
    if (u == NULL)
    {
        return;
    }

    t = createLink(M);
    t->size = 2;

    t->entry[0].key = head->entry[0].key;
    t->entry[0].next = head;
    t->entry[1].key = u->entry[0].key;
    t->entry[1].next = u;

    head = t;
    (*H)++;
}

void traversal(ST_Node *head)
{
    int i;
    if (head != NULL)
    {
        // printf("PASSEI O HEAD\n");
        for (i = 0; i < head->size; i++)
        {
            // printf("TO NO FOR\n");
            traversal(head->entry->next);
            // printf("PASSEI NA RECURSÃO\n");

            printf("%s ", head->entry[i].item->id);
        }
        traversal(head->entry->next);
    }
}

int main()
{
    int M = 4, H = 0; // M - argv()
    ST_Node *head = NULL;
    STinit(&head, &H, M);
    // printf("%ld\n", head->size);

    Record item1 = RECORDcreate("123", "5");
    Record item2 = RECORDcreate("124", "6");
    Record item3 = RECORDcreate("Ezequiel", "8");
    Record item4 = RECORDcreate("126", "9");
    // RECORDprint(item);

    STinsert(head, item1, &H, M);
    // printf("H = %i\n", H);
    STinsert(head, item2, &H, M);
    // printf("H = %i\n", H);
    STinsert(head, item3, &H, M);
    // printf("H = %i\n", H);
    STinsert(head, item4, &H, M);
    // printf("H = %i\n", H);

    // traversal(head);
    Record searchRecord = searchR(head, "Ezequiel", H);
    RECORDprint(searchRecord);

    // printf("Hello, World!\n");

    // freeLink(head);

    return 0;
}
