// INCOMPLETO

#include <stdio.h>
#include <stdlib.h>
#include "../include/record.h"
#include "../include/b_tree.h"

/*static int N;*/
struct st_node
{
    Entry *entry;
    int size;
};
// typedef struct ST_Node ST_Node;

struct entry
{
    Item item;
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

Item searchR(ST_Node *head, Key v, int H)
{
    // printf("searchR\n");
    int j = 0;
    if (H == 0)
    {
        // printf("\tH == 0\n");
        // printf("\tj (%i) < head->size (%i)\n", j, head->size);
        for (j = 0; j < head->size; j++)
        {
            // printf("\teq(v, head->entry[j].key)\n");
            if (eq(v, head->entry[j].item->id))
            {
                // printf("\t\tVAPO\n");
                return head->entry[j].item;
            }
        }
    }
    if (H != 0)
    {
        // printf("\tH != 0\n");
        for (j = 0; j < head->size; j++)
        {
            // printf("\tj < head->size (%i)\n", head->size);
            if ((j + 1 == head->size) || less(v, head->entry[j + 1].item->id))
            {
                // printf("\t\tVAPO\n");
                return searchR(head->entry[j].next, v, H - 1);
            }
        }
    }
    return NULL;
}

ST_Node *split(ST_Node **h, int M)
{
    printf("Splittando...\n");
    int j = 0;
    ST_Node *newSplitNode = createLink(M);

    for (j = 0; j < M / 2; j++)
    {
        printf("Split: %s\n", (*h)->entry[M / (2 + j)].item->id);
        newSplitNode->entry[j] = (*h)->entry[M / (2 + j)];
    }

    (*h)->size = M / 2;
    newSplitNode->size = M / 2;

    return newSplitNode;
}

ST_Node *insertR(ST_Node **head, Item item, int *H, int M)
{
    int i, j;
    Key v = key(item);
    Entry x;
    x.item = item;
    // x.item = v
    ST_Node *t, *u;
    // x.item->id = v;

    // printf("INICIALIZEI\n");
    if (*H == 0)
    {
        // printf("H == 0\n");
        for (j = 0; j < (*head)->size; j++)
        {
            // printf("\tFOR\n");
            if (less(v, (*head)->entry[j].item->id))
            {
                // printf("less(v, head->entry[j].key)\n")
                break;
            }
        }
    }
    if (*H != 0)
        for (j = 0; j < (*head)->size; j++){
            if((*head)->entry[j + 1].item != NULL){
                if ((j + 1 == (*head)->size) || less(v, (*head)->entry[j + 1].item->id))
                {
                    t = (*head)->entry[j++].next;
                    u = insertR(&t, item, H - 1, M);
                    if (u == NULL)
                        return NULL;
                    x.item->id = u->entry[0].item->id;
                    x.next = u;
                    break;
                }
            }
        }

    for (i = ((*head)->size)++; i > j; i--)
        (*head)->entry[i] = (*head)->entry[i - 1];
    (*head)->entry[j] = x;
    if ((*head)->size < M)
    {
        // printf("(*head)->size < M\n");
        return NULL;
    }
    else
    {
        return split(head, M);
    }
}

void STinsert(ST_Node **head, Item item, int *H, int M)
{
    ST_Node *t, *u = insertR(head, item, H, M);
    printf("INSERTEI??\n");
    if (u == NULL)
    {
        return;
    }

    t = createLink(M);
    t->size = 2;

    t->entry[0].item = (*head)->entry[0].item;
    t->entry[0].next = (*head);
    t->entry[1].item = u->entry[0].item;
    t->entry[1].next = u;

    (*head) = t;
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

    Item item1 = ITEMcreate("BLABLA", 1);
    Item item2 = ITEMcreate("bolinha", 546);
    Item item3 = ITEMcreate("giropasd", 54665);
    Item item4 = ITEMcreate("desgraca", 100);
    Item item5 = ITEMcreate("pexie", 250);

    STinsert(&head, item1, &H, M);
    printf("H = %i\n", H);
    STinsert(&head, item2, &H, M);
    printf("H = %i\n", H);
    STinsert(&head, item3, &H, M);
    printf("H = %i\n", H);
    STinsert(&head, item4, &H, M);
    printf("H = %i\n", H);
    STinsert(&head, item5, &H, M);
    printf("H = %i\n", H);
    // STinsert(&head, item6, &H, M);
    // printf("H = %i\n", H);
    // STinsert(&head, item7, &H, M);
    // printf("H = %i\n", H);
    // STinsert(&head, item8, &H, M);
    // printf("H = %i\n", H);

    traversal(head);
    // Item result = searchR(head, "Ezequiel Sch", H);
    // RECORDprint(searchRecord);

    // freeLink(head);

    return 0;
}
