#ifndef hsh_h
#define hsh_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTABLELEN 16
#define FALSE 0
#define TRUE 1
#define CHAINLEN 10
#define RESIZENUM 10


struct node {
    char* word;
    struct node* next;
};

typedef struct node Node;

struct Hash_array {
	Node** array;
};

typedef struct Hash_array hash_array;

struct Dictionary {
    hash_array* hashtable;
    int wordmaxlen;
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

/* Finish up */ /* Clears all space used, and sets pointer to NULL */
void dic_free(dic** s);

/*creat a new node*/
Node* Node_init(char* v);

/*insert a data to hashtable*/
void hash_insert(hash_array* Hasharray,char* v,int size);

/*insert a data to node*/
void node_insert(Node** n,char* v);

int Hash(char* v,int hashtablelen);

bool hash_isin(dic* d,char* v,int hashtablelen);

void hash_resize(dic* d,int oldlen,int newlen);

void hashtable_free(dic* d, int size);


#endif 
