#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/binfile.h"
#define MAXBLOCKSIZE 30 //lembrar de trocar essa porra pelo amor de deus

void writerecord(char* id, char* value, int enable, FILE* f){
    int n = strlen(id)+strlen(value)+1;
    char v=',';
    fwrite(&n,4,1,f);//4 bytes com value de ’n’
    fwrite(&enable,1,1,f);//Esse registro e valido
    fwrite(id,1,strlen(id),f);//Escreve identificador
    fwrite(&v,1,1,f);//Escreve a virgula
    fwrite(value,1,strlen(value),f);//Escreve o valor
}

int fileSize(FILE *fp){
    if(fp == NULL){
        return -1;
    }
    fseek(fp, 0L, SEEK_END);
    int fSize = ftell(fp);
    rewind(fp);

    return fSize;
}


/** Se num for menor que o tamanho máximo do bloco,
     * então o tamanho do bloco será num **/
int newBlockSize(int num){
    if(num < MAXBLOCKSIZE){
        return num;
    }else{
        return MAXBLOCKSIZE;
    }
}

char *getId(unsigned char* block, int posStart, int maxSize){
    // Conta o tamanho do id
    int size = 0;
    for (int i = posStart; size < maxSize; i++, size++){
        char token = (char)((unsigned char)block[i]);
        if(token == ','){
            break;
        }
    }

    char *id = malloc(sizeof(char) * (size + 1));

    for (int i = posStart, c = 0; c < size ; i++, c++){
        char letter = (char)((unsigned char)block[i]);
        id[c] = letter;
    }
    id[size] = '\0' ;

    return id;
}

/**
 * Retorna 0 se todos os registros foram lidos corretamente e
 * não existiu nenhum registro incompleto.
 * Retorna a quantidade de bytes a serem recuados, caso exista
 * um registro incompleto
 **/
int transcribeRecords(unsigned char* block, int blockSize, long fileSeek){ // por enquanto só printa a chave e a posição no arquivo
    int n = 0;
    for (int i = 0; i < blockSize; i += 5+n){
        // primeira checagem de registro incompleto
        // talvez não seja necessária
        // tomar muito cuidado cm essa porra
        if((blockSize - i) < 8){
            return abs(blockSize - i);
        }

        n = (int)((unsigned char)(block[i + 3]) << 24 |
            (unsigned char)(block[i + 2]) << 16 |
            (unsigned char)(block[i + 1]) << 8 |
            (unsigned char)(block[i]));

        // int active = (int)((unsigned char)(block[i + 4])); // IGNORÁVEL

        // Segunda checagem de registro incompleto
        if((blockSize - i - 5 - n) < 0){
            return abs(blockSize - i - 5 - n);
        }

        // posição do registro no arquivo
        unsigned long int pos = fileSeek + i; 

        char *id = getId(block, i + 5, n);

        // Aqui vai inserir a posição e a chave na árvore binária
        printf("%d %d %s\n", n, pos, id);

        free(id); // temporário
    }

    return 0;
    
}

void readFile(FILE *fp){
    if(fp == NULL){
        return;
    }
    
    int fSize = fileSize(fp);
    int blockSize = newBlockSize(fSize);

    unsigned char buffer[blockSize];

    int blocks = 1;

    // Itera até a quantidade de blocos lidos ser 0
    while(1){
        long actualSeek = ftell(fp);
        blocks = fread(buffer, blockSize, 1, fp);

        if(blocks == 0){
            break;
        }

        int backSeek = transcribeRecords(buffer, blockSize, actualSeek);
        fseek(fp, backSeek*(-1) ,SEEK_CUR);

        blockSize = newBlockSize(fSize - ftell(fp));
    }

    
}