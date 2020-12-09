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

    freeST(head);

    return EXIT_SUCCESS;
}
