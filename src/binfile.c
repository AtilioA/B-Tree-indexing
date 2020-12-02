#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/binfile.h"
#define MAXBLOCKSIZE 10

void writerecord(char* id, char* value, int enable, FILE* f){
    int n = strlen(id)+strlen(value)+1;
    char v=',';
    fwrite(&n,4,1,f);//4 bytes com value de ’n’
    fwrite(&enable,1,1,f);//Esse registro e valido
    fwrite(id,1,strlen(id),f);//Escreve identificador
    fwrite(&v,1,1,f);//Escreve a virgula
    fwrite(value,1,strlen(value),f);//Escreve o valor
}

void readFile(FILE *fp){
    if(fp == NULL){
        return;
    }
    
    fseek(fp, 0L, SEEK_END);
    int fSize = ftell(fp);
    rewind(fp);

    int readCnt = 1;

    int blockSize = MAXBLOCKSIZE;

    if(fSize < MAXBLOCKSIZE){
        blockSize = fSize;
    }else{
        readCnt = (int)(fSize/MAXBLOCKSIZE);
        if(fSize%MAXBLOCKSIZE != 0){
            readCnt++;
        }
        
    }

    unsigned char buffer[fSize];

    fread(buffer, blockSize, readCnt, fp);
    
}