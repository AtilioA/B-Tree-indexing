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

    fclose(fp);

    // fp = fopen("input/basic", "r+b");

    // softDelete(fp, 14);

    // fclose(fp);

    return EXIT_SUCCESS;
}
