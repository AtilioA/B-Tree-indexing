#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/record.h"

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