#ifndef __BINFILE_H
#define __BINFILE_H

typedef struct record* Record;

typedef struct Block Block;

void writerecord(char* id, char* value, int enable, FILE* f);

void indexFile(FILE *fp);

Record getRecordOnBlock(Block block, long int posStart);

Record getRecordOnPos(FILE *fp, long int fileIndex);

void recordSoftDelete(FILE *fp, long int fileIndex);

void enableRecord(FILE *fp, long int fileIndex);

#endif

