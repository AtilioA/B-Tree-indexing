/*
 * This code is from "Algorithms in C, Third Edition,"
 * by Robert Sedgewick, Addison Wesley Longman, 1998.
 * (with some small alterations...)
 */
#include <stdio.h>
#include <stdlib.h>
#include "item.h"

void STinit();
int STcount();
void STinsert(Item);
Item STsearch(Key);
void STshow_all();

Item STselect(int);

/*
 * Rotinas para experimentos para arvores - nao fazem parte da 
 * implementacao de Tabelas de Simbolos.  Elas servem para nos
 * mostrar como 'e a arvore etc.  
 * (Implementadas em apenas alguns casos.)
 */

// void BSTbalance();
// void BSTquickprint();