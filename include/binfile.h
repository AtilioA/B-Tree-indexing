#include "b_tree.h"
#ifndef __BINFILE_H
#define __BINFILE_H

typedef struct record* Record;

typedef struct Block Block;

// Escreve um registro no arquivo
void writeRecord(char* id, char* value, int enable, FILE* f);

// Varre o arquivo e insere a posição e o id de cada registro na árvore de busca
void indexFile(FILE *fp, Link *head);

/**
 * Retorna o primeiro registro de um bloco
 * a partir de uma posição inicial
 **/
Record getRecordOnBlock(Block block, long int posStart);

/**
 * Retorna o primeiro registro a partir da posição desejada no arquivo
 **/
Record getRecordOnPos(FILE *fp, long int fileIndex);

// Dado a posição do registro no arquivo, desativa o registro
// Essa função precisa que o fp seja aberto em modo "r+b"
void recordSoftDelete(FILE *fp, long int fileIndex);

// Dado a posição no arquivo, retorna o estado do registro
int getRecordState(FILE *fp, long int fileIndex);

// Dado id e valor, insere um novo registro no final do arquivo
long int insertRecord(FILE *fp, char *id, char *value);

/**
 * Procura o registro no arquivo baseado na posição dada no 
 * Item, depois escreve o registro em um arquivo de texto
 */
void outputRecordFromItem(Item x, FILE *fp, FILE *out);

#endif

