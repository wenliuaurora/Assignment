#ifndef __BST_H__
#define __BST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

struct node
{
   struct node* left;
   struct node* right;
   char *word;
};
typedef struct node Node;

struct Dictionary
{
    Node* root;
    int size;
};

typedef struct Dictionary dic;

typedef int bool;

/* Create empty dic */
dic* dic_init(int size);

/* Add one element into the dic */
void dic_insert(dic* s, char* v);

/* Returns true if v is in the array, false elsewise */
bool dic_isin(dic* s, char* v);

/* Finish up */
/* Clears all space used, and roots pointer to NULL */
void dic_free(dic** s);


Node* CreatNode(int len,char* w);
Node* Insertroot(Node* root,char*w,int len);
bool issame(Node* root,char* w);
void Node_free(Node* root);

#endif
