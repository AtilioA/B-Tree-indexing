#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/binfile.h"
#include "../include/record.h"
#define MAXBLOCKSIZE 30 //lembrar de trocar essa porra pelo amor de deus

struct Block
{
    unsigned char *bytes;
    int size;
};

typedef struct Block Block;

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
    int previousSeek = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int fSize = ftell(fp);
    fseek(fp, previousSeek, SEEK_SET);
    // rewind(fp);

    return fSize;
}


/** Se num for menor que o tamanho máximo do bloco,
     * então o tamanho do bloco será num **/
long int newBlockSize(long int num){
    if(num < MAXBLOCKSIZE){
        return num;
    }else{
        return MAXBLOCKSIZE;
    }
}

char *getId(Block block, int posStart, int maxSize){
    // Conta o tamanho do id
    int size = 0;
    for (int i = posStart; size < maxSize; i++, size++){
        char token = (char)((unsigned char)block.bytes[i]);
        if(token == ','){
            break;
        }
    }

    char *id = malloc(sizeof(char) * (size + 1));

    for (int i = posStart, c = 0; c < size ; i++, c++){
        char letter = (char)((unsigned char)block.bytes[i]);
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
int transcribeRecords(Block block, long fileSeek){ // por enquanto só printa a chave e a posição no arquivo
    int n = 0;
    for (int i = 0; i < block.size; i += 5+n){
        // primeira checagem de registro incompleto
        // talvez não seja necessária
        // tomar muito cuidado cm essa porra
        if((block.size - i) < 8){
            return abs(block.size - i);
        }

        n = (int)((unsigned char)(block.bytes[i + 3]) << 24 |
            (unsigned char)(block.bytes[i + 2]) << 16 |
            (unsigned char)(block.bytes[i + 1]) << 8 |
            (unsigned char)(block.bytes[i]));

        // int active = (int)((unsigned char)(block.bytes[i + 4])); // IGNORÁVEL

        // Segunda checagem de registro incompleto
        if((block.size - i - 5 - n) < 0){
            return abs(block.size - i - 5 - n);
        }

        Item recordIdx = malloc(sizeof(struct index));

        // posição do registro no arquivo
        recordIdx->fileIndex = fileSeek + i;

        recordIdx->id = getId(block, i + 5, n);

        // Aqui vai inserir a posição e a chave na árvore binária
        printf("%d %ld %s\n", n, recordIdx->fileIndex, recordIdx->id);

        ITEMfree(recordIdx); // temporário
    }

    return 0;
    
}

Block readBlock(FILE *fp){
    if(fp == NULL){
        return;
    }
    
    long int fSize = fileSize(fp);
    long int blockSize = newBlockSize(fSize - ftell(fp));

    unsigned char *buffer = malloc(sizeof(unsigned char) * blockSize);
    Block obj;
    obj.bytes = NULL;
    
    int blocks = fread(buffer, blockSize, 1, fp);

    if(blocks == 1){
        obj.bytes = buffer;
        obj.size = blockSize;
    }else{
        free(buffer);
    }

    return obj;

}

// Essa função varre o arquivo e insere a posição e o id 
// de cada registro na árvore de busca
void indexFile(FILE *fp){
    if(fp == NULL){
        return;
    }

    // Itera até a quantidade de blocos lidos ser 0
    while(1){
        long actualSeek = ftell(fp);
        Block block = readBlock(fp);

        if(block.bytes == NULL){
            break;
        }

        int backSeek = transcribeRecords(block, actualSeek);
        free(block.bytes);
        fseek(fp, backSeek*(-1) ,SEEK_CUR);

    }

}

Block readBlockOnPos(FILE *fp, long int pos){
    if(fp == NULL){
        return;
    }

    fseek(fp, pos, SEEK_SET);    

    return readBlock(fp);

}