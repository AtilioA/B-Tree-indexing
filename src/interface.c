#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <strings.h>
#include "../include/interface.h"
#include "../include/binfile.h"
#include "../include/record.h"
#include "../include/b_tree.h"
#define MAXSTRSIZE 5000

void removeNewLine(char *str)
{

    int last = strlen(str) - 1;

    if (str[last] == '\n')
    {
        str[last] = '\0';
    }
}

char **readCommand()
{
    char buffer[MAXSTRSIZE];
    fgets(buffer, MAXSTRSIZE, stdin);

    char **commandData = malloc(sizeof(char *) * 3);

    for (int i = 0; i < 3; i++)
    {
        char *tokBuffer = NULL;
        if (i == 0)
        {
            tokBuffer = strtok(buffer, " ");
        }
        else
        {
            tokBuffer = strtok(NULL, " ");
        }
        if (tokBuffer != NULL)
        {
            removeNewLine(tokBuffer);
            commandData[i] = tokBuffer;
        }
        else
        {
            commandData[i] = (char *)("\0");
        }
    }

    return commandData;
}

void startInterfaceLoop(char *filePath, Link *head)
{

    while (1)
    {
        char **commandData = readCommand();

        char *command = commandData[0];

        if (strcasecmp(command, "GET") == 0)
        {
            char *id = commandData[1];
            if(strcmp(id, "") != 0){

                Item newIndex = STsearch(id, *head);

                if((newIndex != NULL) && (ITEMisActive(newIndex))){
                    FILE *fp = fopen(filePath, "rb");
                    Record x = getRecordOnPos(fp, newIndex->fileIndex);
                    RECORDprint(x);
                    RECORDfree(x);
                    fclose(fp);
                }
            }
            free(commandData);
        }
        else if (strcasecmp(command, "INSERT") == 0)
        {
            char *id = commandData[1];
            char *value = commandData[2];
            if(strcmp(id, "") != 0 && strcmp(value, "") != 0){
                FILE *fp = fopen(filePath, "r+b");

                Item newIndex = STsearch(id, *head);

                // se não existir 
                if(newIndex == NULL){
                    newIndex = malloc(sizeof(struct index)); 
                    newIndex->fileIndex = insertRecord(fp, id, value); // insere no final do arquivo e adiciona o indice
                    newIndex->id = malloc(sizeof(char) * strlen(id) + 1); 
                    newIndex->active = 1;
                    strcpy(newIndex->id, id);
                    *head = STinsert(newIndex, *head);
                }else{
                    if(newIndex->active){
                        recordSoftDelete(fp, newIndex->fileIndex);
                    }else{
                        newIndex->active = 1;
                    }
                    newIndex->fileIndex = insertRecord(fp, id, value);   
                }
                
                fclose(fp);
            }
            free(commandData);
        }
        else if (strcasecmp(command, "DELETE") == 0)
        {
            char *id = commandData[1];
            if(strcmp(id, "") != 0){

                Item newIndex = STsearch(id, *head);

                if((newIndex != NULL) && (newIndex->active)){
                    FILE *fp = fopen(filePath, "r+b");
                    recordSoftDelete(fp, newIndex->fileIndex);
                    newIndex->active = 0;
                    fclose(fp);
                }

            }
            free(commandData);
        }
        else if (strcasecmp(command, "RUNDOWN") == 0)
        {
            if(strcmp(commandData[1], "") != 0){
                FILE *fIn = fopen(filePath, "r+b");
                FILE *fOut = fopen(commandData[1], "w");
                runST(*head, outputRecordFromItem, fIn,fOut);
                fclose(fIn);
                fclose(fOut);
            }else{
                printf("Falta 1 argumento no comando RUNDOWN\n");
            }
            free(commandData);
        }
        else if (strcasecmp(command, "STOP") == 0)
        {
            printf("Finalizando...\n");
            free(commandData);
            return;
        }
        else
        {
            free(commandData);
            printf("Comando desconhecido. Tente novamente\n");
        }
    }
}
