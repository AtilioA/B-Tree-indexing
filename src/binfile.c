#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <strings.h>
#include"../include/binfile.h"

void writerecord(char* identificador, char* valor, int ativo, FILE* f){
    int n = strlen(identificador)+strlen(valor)+1;
    char v=',';
    fwrite(&n,4,1,f);//4 bytes com valor de ’n’
    fwrite(&ativo,1,1,f);//Esse registro e valido
    fwrite(identificador,1,strlen(identificador),f);//Escreve identificador
    fwrite(&v,1,1,f);//Escreve a virgula
    fwrite(valor,1,strlen(valor),f);//Escreve o valor
}
