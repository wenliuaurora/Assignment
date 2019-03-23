#include "neillsdl2.h"
#include "interp.h"
#include <assert.h> 
#include <string.h>

#define FILENAMELEN 10 

int main(){
    Code code;
    char *argv[2]; 
    SDL_Simplewin sw;
    Turtle turtle;
    Stack stack;
    int i,j;
    argv[1] = (char *) calloc (FILENAMELEN, sizeof(char));

 /*TEST the numbers of "{" and "}" should be same
 *and the first should be "{",the last should be "}"*/
    strcpy(argv[1],"test1.txt");
    InitCode(&code,argv[1]);
    assert(CountPunctuation(&code)==0);

    strcpy(argv[1],"test4.txt");
    InitCode(&code,argv[1]);
    assert(CountPunctuation(&code)==0);
    
/*TEST usevar if the variable has been used ,it will show warning on screen*/
    code.varuse[2]=1;
    i=2;
    UseVAR(&code,i);

/*TEST the error in Code_DO
*the test3.txt include:
*{
*DO a fROM b tO 0.0.1
*SET a : 2 b ? 
*SET A := ;
* /
*}
*/
    strcpy(argv[1],"test6.txt");
    InitCode(&code,argv[1]);
    code.curr=code.curr+2;
    Code_DO(&code,&sw,&turtle);

/*TEST Code_SET it will show warning */ 
    code.curr=9;
    Code_SET(&code);

/*TEST Code_POLISH,it will show warning*/
    code.curr=16;
    Code_POLISH(&code,&stack);

/*TEST Doloop the the value of variable is larger than endloop */
    i=2;
    j=3;
    code.vars[i]=5;
    Doloop(&code,&sw,i,j,&turtle);
    assert(code.doloopflag==1); 
/*TEST Code_OP  no number in satck*/
    stack.top=1;
    Code_OP(&code,&stack);
/*TEST Code_OP*/
    stack.sta[0]=3;
    stack.sta[1]=0;
    code.curr=17;
    stack.top=2;
    Code_OP(&code,&stack);

    return 0;
}