#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/record.h"
#include "../include/binfile.h"

void ITEMfree(Item x){
    if(x != NULL){
        if(x->id != NULL){
            free(x->id);
            x->id = NULL;
        }
        free(x);
        x = NULL;
    }
}

Record RECORDcreate(char *id, char *value){
    Record new = malloc(sizeof(struct record));
    new->id = id;
    new->value = value;
    return new;
}

void RECORDfree(Record x){
    if(x != NULL){
        if(x->id != NULL){
            free(x->id);
            x->id = NULL;
        }
        if(x->value != NULL){
            free(x->value);
            x->value = NULL;
        }
        free(x);
        x = NULL;
    }
}

void RECORDprint(Record x){
    if(x != NULL){
        printf("%s: %s\n", x->id, x->value);
    }
}

void RECORDprintToFile(Record x, FILE *fp){
    if((x != NULL) && (fp != NULL)){
        fprintf(fp, "%s: %s\n", x->id, x->value);
    }
}