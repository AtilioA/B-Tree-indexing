#ifndef __BINFILE_H
#define __BINFILE_H

typedef struct record* Record;

typedef struct Block Block;

void writeRecord(char* id, char* value, int enable, FILE* f);

void indexFile(FILE *fp);

Record getRecordOnBlock(Block block, long int posStart);

Record getRecordOnPos(FILE *fp, long int fileIndex);

void recordSoftDelete(FILE *fp, long int fileIndex);

int getRecordState(FILE *fp, long int fileIndex);

long int insertRecord(FILE *fp, char *id, char *value);

#endif

