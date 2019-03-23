#include "neillsdl2.h"
#include "interp.h"
#include <assert.h> 
#include <string.h>

#define FILENAMELEN 10 

int main(){
    FILE* fp;
    char *argv[2]; 
    argv[1] = (char *) calloc (FILENAMELEN, sizeof(char));

 /*TEST the number in test3.txt is larger than MAXSTRLEN*/
    strcpy(argv[1],"test3.txt");
    fp = fopen(argv[1], "r");
    assert(Count(fp)==4);

    return 0;
}