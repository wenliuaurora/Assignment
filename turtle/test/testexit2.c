#include "neillsdl2.h"
#include "interp.h"
#include <assert.h> 
#include <string.h>

#define FILENAMELEN 10 

int main(){
    Code code;
    char *argv[2]; 
    argv[1] = (char *) calloc (FILENAMELEN, sizeof(char));
/*TEST open file failed*/
    InitCode(&code,argv[1]);

    return 0;
}