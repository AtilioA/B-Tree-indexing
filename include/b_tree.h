#ifndef __B_TREE_H
#define __B_TREE_H

typedef struct b_tree_node BTreeNode;

// Cria raiz
struct b_tree_node *initTree();
// Cria um nó
BTreeNode *createNode(BTreeNode *root, int val, BTreeNode *child);
// Insere um nó
void insertNode(int val, int pos, BTreeNode *node, BTreeNode *child);
// Divide um nó
void splitNode(int val, int *pval, int pos, BTreeNode *node, BTreeNode *child, BTreeNode **newNode);
// Insere um valor
void insert(BTreeNode *root, int val);
// Procura um nó
void search(int val, int *pos, BTreeNode *myNode);
// Percorre nós
void traversal(BTreeNode *myNode);
// Põe um valor
int setValue(int val, int *pval, BTreeNode *node, BTreeNode **child);

#endif
