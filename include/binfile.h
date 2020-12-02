#ifndef __BINFILE_H
#define __BINFILE_H

void writerecord(char* id, char* value, int enable, FILE* f);

void indexFile(FILE *fp);

#endif

