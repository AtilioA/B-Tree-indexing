#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/b_tree.h"

typedef struct{
    Key key;
    union{
        Link next;
        Item item;
    } ref;
} entry;

struct STnode{
    int M;
    entry *b;
    int m;
    int H;
    int N;
};


Link NEW(int M){
    Link x = malloc(sizeof(struct STnode));
    x->M = M;
    x->b = malloc(sizeof(entry)* M);
    x->m = 0;
    return x;
}

Link STinit(int M){
    Link head = NEW(M);
    head->H = 0;
    head->N = 0;
    return head;
}

int eq(char *a, char *b){
    return (strcmp(a, b) == 0);
}

int less(char *a, char *b){
    return (strcmp(a, b) < 0);
}

Item searchR(Link h, Key v, int H){
    int j;
    if (H == 0)
        for (j = 0; j < h->m; j++){
            if (eq(v, h->b[j].key))
	            return h->b[j].ref.item;
        }
    if (H != 0)
        for (j = 0; j < h->m; j++)
            if ((j+1 == h->m) || less(v, h->b[j+1].key))
	            return searchR(h->b[j].ref.next, v, H-1);
    return NULLitem;
}

Item STsearch(Key v, Link head){
    return searchR(head, v, head->H);
}

Link split(Link h){
    int j;
    Link t = NEW(h->M);

    for (j = 0; j < h->M/2; j++)
        t->b[j] = h->b[h->M/2+j];
    h->m = h->M/2;
    t->m = h->M/2;
    return t;
}

Link insertR(Link h, Item item, int H){
    int i, j;
    Key v = key(item);
    entry x;
    Link t, u;

    x.key = v;
    x.ref.item = item;
    if (H == 0)
        for (j = 0; j < h->m; j++)
            if (less(v, h->b[j].key))
	            break;
    if (H != 0)
        for (j = 0; j < h->m; j++)
            if ((j+1 == h->m) || less(v, h->b[j+1].key)){
	            t = h->b[j++].ref.next;
	            u = insertR(t, item, H-1);
	            if (u == NULL)
	                return NULL;
	            x.key = u->b[0].key;
	            x.ref.next = u;
	            break;
	        }
    for (i = (h->m)++; i > j; i--)
        h->b[i] = h->b[i-1];
    h->b[j] = x;
    if (h->m < h->M)
        return NULL;
    else
        return split(h);
}

Link STinsert(Item item, Link head){
    Link t, u = insertR(head, item, head->H);

    if (u == NULL)
        return head;
    t = NEW(head->M);
    t->m = 2;
    t->H = head->H;
    t->b[0].key = head->b[0].key;
    t->b[0].ref.next = head;
    t->b[1].key = u->b[0].key;
    t->b[1].ref.next = u;
    t->H++;
    return t;
}


void freeR(Link head, int H){
    if (H == 0){
        for(int i = 0; i < head->m; i++){
            ITEMfree(head->b[i].ref.item);
        }
        free(head->b);
        free(head);
    }else{
        for(int i = 0; i < head->m; i++){
            freeR(head->b[i].ref.next, H - 1);
        }
        free(head->b);
        free(head);
    }
}

void runR(Link head, int H, void (*callItem)(Item, void*, void*), void* callArg1, void* callArg2){
    if (H == 0){
        for(int i = 0; i < head->m; i++){
            callItem(head->b[i].ref.item, callArg1, callArg2);
        }
    }else{
        for(int i = 0; i < head->m; i++){
            runR(head->b[i].ref.next, H - 1, callItem, callArg1, callArg2);
        }
    }
}

void freeST(Link head){
    freeR(head, head->H);
}

void runST(Link head, void (*callItem)(Item, void*, void*), void* callArg1, void* callArg2){
    runR(head, head->H, callItem, callArg1, callArg2);
}


// int main()
// {
//     int M = 4;
//     Link head = STinit(M);
//     printf("%ld\n", head->m);

//     Item item1 = ITEMcreate("BLABLA", 1);
//     Item item2 = ITEMcreate("bolinha", 546);
//     Item item3 = ITEMcreate("giropasd", 54665);
//     Item item4 = ITEMcreate("desgraca", 100);
//     Item item5 = ITEMcreate("pexie", 250);

//     head = STinsert(item1, head);
//     printf("H = %i\n", head->H);
//     head = STinsert(item2, head);
//     printf("H = %i\n", head->H);
//     head = STinsert(item3, head);
//     printf("H = %i\n", head->H);
//     head = STinsert(item4, head);
//     printf("H = %i\n", head->H);
//     head = STinsert(item5, head);
//     printf("H = %i\n", head->H);

//     // Item result = STsearch("giropasd", head);
//     // ITEMprint(result);

//     // runR(head, head->H, ITEMprint, NULL, NULL);

//     // freeST(head);

//     // STinsert(&head, item1, &H, M);
//     // STinsert(&head, item2, &H, M);
//     // printf("H = %i\n", H);
//     // STinsert(&head, item3, &H, M);
//     // printf("H = %i\n", H);
//     // STinsert(&head, item4, &H, M);
//     // printf("H = %i\n", H);
//     // STinsert(&head, item5, &H, M);
//     // printf("H = %i\n", H);
//     // // STinsert(&head, item6, &H, M);
//     // // printf("H = %i\n", H);
//     // // STinsert(&head, item7, &H, M);
//     // // printf("H = %i\n", H);
//     // // STinsert(&head, item8, &H, M);
//     // // printf("H = %i\n", H);

//     // // traversal(head);
//     // Item result = searchR(head, "giropasd", H);
//     // ITEMprint(result);

//     // // freeLink(head);

//     return 0;
// }
