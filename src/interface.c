#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "../include/interface.h"
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
            commandData[i] = "\0";
        }
    }

    return commandData;
}

void startInterfaceLoop()
{

    while (1)
    {
        char **commandData = readCommand();

        char *command = commandData[0];

        if (strcasecmp(command, "GET") == 0)
        {
            free(commandData);
        }
        else if (strcasecmp(command, "INSERT") == 0)
        {
            free(commandData);
        }
        else if (strcasecmp(command, "DELETE") == 0)
        {
            free(commandData);
        }
        else if (strcasecmp(command, "RUNDOWN") == 0)
        {
            free(commandData);
        }
        else if (strcasecmp(command, "STOP") == 0)
        {
            printf("Finalizando...\n");
            free(commandData);
            exit(1);
        }
        else
        {
            free(commandData);
            printf("Comando desconhecido. Tente novamente\n");
        }
    }
}
