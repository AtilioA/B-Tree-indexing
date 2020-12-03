#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "../include/utils.h"
#include "../include/interface.h"
#include "../include/b_tree.h"
#include "../include/binfile.h"
#include "../include/record.h"

int main(int argc, char **argv)
{
    // if(argc != 2){
    // 	fprintf(stderr, "Quantidade de argumentos invalido\n");
    // 	exit(1);
    // }
    // int k = atoi(argv[1]);
    // // FILE* binFile = fopen(argv[1], "rw");

    // while (1){
    //     /* code */
    // }

    // BTreeNode *root = initTree();

    // int val, ch;

    // insert(&root, 8);
    // insert(&root, 9);
    // insert(&root, 10);
    // insert(&root, 11);
    // insert(&root, 15);
    // insert(&root, 16);
    // insert(&root, 17);
    // insert(&root, 18);
    // insert(&root, 20);
    // insert(&root, 23);

    // traversal(root);

    // printf("\n");
    // search(11, &ch, root);
    // printf("\n");

    // startInterfaceLoop();

    // FILE *write_ptr = fopen("input/basic", "wb");

    // writerecord("ed2", "facil",1, write_ptr);

    // writerecord("paa", "deboa",1, write_ptr);

    // writerecord("tc", "suave",0, write_ptr);

    // writerecord("cd", "jafoi",1, write_ptr);

    // fclose(write_ptr);

    // FILE *fp = fopen("input/basic", "r+b");

    // recordSoftDelete(fp, 0);

    // enableRecord(fp, 14);

    // // insertRecord(fp, "teste", "bolinha");

    // fclose(fp);

    int M = 8, H = 0;
    ST_Node *head = NULL;
    STinit(&head, &H, M);

    Record item1 = RECORDcreate((char *)"123", (char *)"5");
    Record item2 = RECORDcreate((char *)"124", (char *)"6");
    Record item3 = RECORDcreate((char *)"Ezequiel", (char *)"8");
    Record item4 = RECORDcreate((char *)"Ezequiel Sch", (char *)"80");

    STinsert(&head, item1, &H, M);
    printf("H = %i\n", H);
    STinsert(&head, item2, &H, M);
    printf("H = %i\n", H);
    STinsert(&head, item3, &H, M);
    printf("H = %i\n", H);
    STinsert(&head, item4, &H, M);
    printf("H = %i\n", H);

    printf("\nPesquisa por Ezequiel Sch:\n");
    Record searchRecord = searchR(head, (char *)"Ezequiel Sch", H);
    RECORDprint(searchRecord);
    printf("\n");
    // traversal(head);

    FILE *fp = fopen("input/basic", "rb");

    indexFile(fp);

    Record x = NULL;

    x = getRecordOnPos(fp, 41);
    RECORDprint(x);
    RECORDfree(x);
    x = getRecordOnPos(fp, 0);
    RECORDprint(x);
    RECORDfree(x);
    x = getRecordOnPos(fp, 14);
    RECORDprint(x);
    RECORDfree(x);
    x = getRecordOnPos(fp, 28);
    RECORDprint(x);
    RECORDfree(x);
    // x = getRecordOnPos(fp, 54);
    // RECORDprint(x);
    // RECORDfree(x);

    fclose(fp);

    return EXIT_SUCCESS;
}
