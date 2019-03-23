#include"bst.h"

/* Create empty dic */
dic* dic_init(int size){
    dic* d;
    d=(dic*)malloc(sizeof(dic));
    if(d ==NULL){
      fprintf(stderr, "Creation Of dic Failed\n");
      exit(1);
    }
    d->root=NULL;
    d->size=size;
    return d;
   
}

/* Add one element into the dic */
void dic_insert(dic* s, char* v){
    /*because it is a string the length of string need add one(\0)*/
    int len=strlen(v)+1;
    if(s==NULL){
       fprintf(stderr, "Insert Failed\n");
        return;
    }
    if(len>s->size){
        fprintf(stderr, "Failed,The Word Is Too Long\n");
    }
    else {
    s->root=Insertroot(s->root,v,len);
    }
}

Node* Insertroot(Node* root,char* w,int len){
    if(w==NULL){
        fprintf(stderr, "Insert No Word\n");
        return NULL;
    }    
    /*If it is not exist, than creat one*/
    if(root==NULL){
        root= CreatNode(len,w);
        return root;
    }    
    /* Smaller word put left */
    else if(strcmp(w, root->word) <0){
        root->left=Insertroot(root->left,w,len);
    }
    /* Larger word put right */
    else if(strcmp(w, root->word) > 0){
        root->right=Insertroot(root->right,w,len);
    }
    return root;
}

/*creat a node and put data in*/
Node* CreatNode(int len,char* w){
    Node* root;
    root=(Node*)malloc(sizeof(Node));
    if(root==NULL){
        fprintf(stderr, "Btree Creation Failed\n");
        return NULL;
    }
    root->left=NULL;
    root->right=NULL;
    root->word=(char*)malloc(len*sizeof(char));
    strcpy(root->word,w);
    return root;
}

/* Returns true if v is in the array, false elsewise */
bool dic_isin(dic* s, char* v){
     if(s == NULL || v == NULL){
        return FALSE;
    }
    return issame(s->root, v);
}


/* Search in root*/
bool issame(Node* root,char* w){
    /* Not found the root */
    if(root == NULL){
        return FALSE;
    }
    /* Find the same word */
    if(strcmp(root->word, w) == 0){
        return TRUE;
    }
    /* If the the word is larger than node */
    /* It should find in right child */
    if(strcmp(w, root->word) < 0){
        return issame(root->left, w);
    }
    /* Shorter,find it in left child */
    if(strcmp(w, root->word) > 0){
        return issame(root->right, w);
    }
    return FALSE;
}
/* Finish up */
/* Clears all space used, and roots pointer to NULL */
void dic_free(dic** s){
    dic* d;
    if(s == NULL){
        return;
    }
    d=*s;
    Node_free(d->root);    
    free(d);
    *s = NULL;
}

void Node_free(Node* root){
    if(root == NULL){
        return;
    }
    if(root->left == NULL && root->right == NULL){
        free(root->word);
        free(root);
        root = NULL;
        return;
    }
    if(root->left != NULL){
        Node_free(root->left);
    }
    if(root->right != NULL){
        Node_free(root->right);
    }
    /*free the first node*/
    free(root->word);
    free(root);
}



