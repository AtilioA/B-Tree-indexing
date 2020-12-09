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
    if(argc != 3){
    	fprintf(stderr, "Quantidade de argumentos invalido\n");
    	exit(1);
    }

    int M = atoi(argv[1]);
    char *binPath = argv[2];

    Link head = STinit(M);

    FILE *fp = fopen(binPath, "rb");

    indexFile(fp, &head);

    fclose(fp);

    startInterfaceLoop(binPath, &head);

    // FILE *out = fopen("output", "w");

    // runST(head, outputRecordFromItem, fp, out);

    // fclose(out);

    freeST(head);

    // Record x = NULL;

    // x = getRecordOnPos(fp, 41);
    // RECORDprint(x);
    // RECORDfree(x);
    // x = getRecordOnPos(fp, 0);
    // RECORDprint(x);
    // RECORDfree(x);
    // x = getRecordOnPos(fp, 14);
    // RECORDprint(x);
    // RECORDfree(x);
    // x = getRecordOnPos(fp, 28);
    // RECORDprint(x);
    // RECORDfree(x);
    // // x = getRecordOnPos(fp, 54);
    // // RECORDprint(x);
    // RECORDfree(x);


    return EXIT_SUCCESS;
}
