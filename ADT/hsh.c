#include"hsh.h"

/* Create empty dic */
dic* dic_init(int size){
    dic* d;
    int i;
    if (size < 0){
        fprintf(stderr, "Wrong Size\n");
        exit(1);
    }
       /*creat new dic*/
    d = (dic*) malloc(sizeof(dic));
    if(d == NULL){
        fprintf(stderr, "Dic creation failed\n");
        exit(1);
    }
    d->hashtable = (hash_array*) malloc(sizeof(hash_array));
    if(d->hashtable == NULL){
        fprintf(stderr, "Creat hashtable failed\n");
        exit(1);
    }
     /*give array a space*/
    d->hashtable->array = (Node**) malloc(HASHTABLELEN*sizeof(Node*));
    if(d->hashtable->array == NULL){
    	fprintf(stderr, "Creat array failed\n");
    }
    for (i = 0; i < HASHTABLELEN; i++){
        d->hashtable->array[i] = NULL;
    }
    d->size = HASHTABLELEN;
    d->wordmaxlen = size;
    return d;
}

/* Add one element into the dic */
void dic_insert(dic* s, char* v){
    int i=0;
    Node* n=s->hashtable->array[Hash(v,s->size)];
    if(v==NULL){
        fprintf(stderr, "Insert wrong word\n");
    }
    if(s==NULL){
        fprintf(stderr, "Give wrong dic address\n");
    }
    /*the length of chain*/
    while(n != NULL){
        n = n->next;
        i++;
    }    
     /*if greater than limitation ,resize the hash table 10 times*/
    if (i >= CHAINLEN){
        hash_insert(s->hashtable,v,s->size);
        hash_resize(s,s->size,RESIZENUM*(s->size));
    }
    else{
        hash_insert(s->hashtable,v,s->size);
    }   
}

/* Returns true if v is in the array, false elsewise */
bool dic_isin(dic* s, char* v){
    return hash_isin(s,v,s->size);
}

void dic_free(dic** s){
    dic* d;
    d=*s;
    hashtable_free(d,d->size);
    free(d->hashtable);
    free(d);
    *s=NULL;
}

Node* create_node(char* v){
    Node* n;
    n=(Node*) malloc(sizeof(Node));
    if (n == NULL){
        fprintf(stderr, "Menmory is not enough\n");
        exit(1);
    }
      /*add a '\0'space*/
    n->word=(char*) malloc((strlen(v)+1)*sizeof(char));
    if (n->word==NULL) {
        fprintf(stderr, "Menmory is not enough\n");
        exit(1);
    }
    strcpy(n->word,v);
    n->next=NULL;
    return n;
}

void hash_insert(hash_array* Hasharray,char* v,int size){
    int hashval;
    if(Hasharray==NULL){
        fprintf(stderr, "rong hasharray address\n");
        return;
    }
    else{
        hashval=Hash(v,size);
        node_insert(&Hasharray->array[hashval],v);    
    }
}

void node_insert(Node** n,char* v){
    while(*n!=NULL){
        n=&(*n)->next;
    }
    *n=create_node(v);
}

/*get data hash value */
int Hash(char* v,int hashtablelen){
    /*hash seed*/
    int hash=531;
    while(*v){
        hash+=((hash<<5)+(*v++))% hashtablelen;
    }
    return(hash % hashtablelen);
}

/*find data in hash table*/
bool hash_isin(dic* d,char* v,int hashtablelen){
    Node* temp=d->hashtable->array[Hash(v,hashtablelen)];
    while(temp){
        if(strcmp(v,temp->word)==0){
            return TRUE;
        }
        temp=temp->next;
    }
    return FALSE;    
}

/*if the chain is larger than 10,resize a hash table*/
void hash_resize(dic* d,int oldlen,int newlen){
    int i;
    Node* node;
    hash_array* newarray;
    newarray = (hash_array*) malloc(sizeof(hash_array));
    if(newarray == NULL){
    	fprintf(stderr, "Creat new harsh table failed\n");
    }
    newarray->array=(Node**)malloc(newlen*sizeof(Node*));
    for(i=0;i<newlen;i++){
        newarray->array[i]=NULL;
    }
    for(i=0;i<d->size;i++){
        node=d->hashtable->array[i];
        while(node){
            hash_insert(newarray,node->word,newlen);
            node=node->next;
        }
    }
    hashtable_free(d,oldlen);
    d->hashtable= newarray; 
    d->size=newlen;
}

void hashtable_free(dic* d, int size){
    int i;
    Node** n;
    Node** temp;
    /*free the hashtable array,and chain*/
    for (i=0;i<size;i++){
    	n=&(d->hashtable->array[i]);
    	while(*n){
    		temp=&((*n)->next);
    		free((*n)->word);
    		free(*n);
    		n=temp;
    	}
    }   
    free(d->hashtable->array);
    d->hashtable->array=NULL;
}
