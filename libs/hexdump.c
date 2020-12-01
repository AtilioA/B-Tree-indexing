#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    FILE *fp;
    int c, i, max;

    if(argc <= 1){
        printf("lhe falta argu-mentos\n");
        exit(1);
    }

    fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        fprintf(stderr, "cannot open input file\n");
        return 1;
    }
    for (i = 0; (c = getc(fp)) != EOF; i++) {
        printf("%02x", c);
        putchar(' ');   // group bytes in pairs
    }
    putchar('\n');

    fclose(fp);
    return 0;
}
