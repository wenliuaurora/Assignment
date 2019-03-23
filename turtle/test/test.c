#include "neillsdl2.h"
#include "interp.h"
#include <assert.h> 
#include <string.h>

#define FILENAMELEN 10 


int main(){
    Code code;
    Turtle turtle;
    FILE* fp;
    Stack stack;
    char *argv[2];
    int i;
    double d;
    /* malloc the argv */
    argv[1] = (char *) calloc (FILENAMELEN, sizeof(char));
  
    

/*Test InitCode including: 
*1.code.curr should be 0;
*2.there are all 0 in code.vars where store variables'value 
*  and code.varuse where record whether variables have been used;
*3.code.doloop should be 0;
*4.give space to code.words*/

/*TEST test1.txt*/
strcpy(argv[1],"test1.txt");
InitCode(&code,argv[1]);
assert(code.curr==0);
assert(code.totalnum==1);
assert(code.doloopflag==0);
for(i=0;i<ALPHABET;i++){
       assert((int)code.vars[i]==0);
       assert(code.varuse[i]==0);
}
for(i=0;i<=code.totalnum;i++){
       assert(code.words[i]!=NULL);
       assert(code.words+i!=NULL);
}
/*TEST test2.txt*/
strcpy(argv[1],"test2.txt");
InitCode(&code,argv[1]);
assert(code.curr==0);
assert(code.totalnum==14);
assert(code.doloopflag==0);
for(i=0;i<ALPHABET;i++){
       assert((int)code.vars[i]==0);
       assert(code.varuse[i]==0);
}
for(i=0;i<=code.totalnum;i++){
       assert(code.words[i]!=NULL);
       assert(code.words+i!=NULL);
}

/*Test function Count and Checkstrlen*/
   strcpy(argv[1],"test2.txt");
   fp = fopen(argv[1], "r");
   assert(Count(fp)==14);

/*TEST function push and pop STACK 
* push 2 into stack*/
   stack.top=0;
   PushStack(&stack,2);
   assert(stack.top==1);
   assert((int)stack.sta[stack.top-1]==2);
   PopStack(&stack);
   assert(stack.top==0);

/*TEST the "{" and "}"should match*/
   strcpy(argv[1],"test2.txt");
   InitCode(&code,argv[1]);
   assert(CountPunctuation(&code)==1);

/*TEST function InitTurtle*/
   InitTurtle(&turtle);
   assert(turtle.angle-M_PI<MINNUM);
   assert((int)turtle.currposition[0]==INITX);
   assert((int)turtle.prevposition[0]==INITX);
   assert((int)turtle.currposition[1]==INITY);
   assert((int)turtle.prevposition[1]==INITY);

/*TEST Changangle when the angle =2*M_PI it should change to 0*/
   turtle.angle=2*M_PI;
   i=1;
   Changeangle(&turtle,i);
   assert((int)turtle.angle==0);

/*TEST CodeVARNUM if the current string is a capital letter 
*than take its value and return;
*if the current string is a num, than take it and return;
*Test CodeVAR if the current srring is a capital letter,than return True;
*the test3.txt include:
*{
*FD -30
*FD a
*FD B
*}
*so the words[2] is "-30";
*the words[4] is "a"
*the words[6] is "B" */
   strcpy(argv[1],"test5.txt");
   InitCode(&code,argv[1]);
   code.curr=2;
   assert(CodeVARNUM(&code,&d)==1);
   assert((int)d==-30);
   code.curr=4;
   assert(CodeVAR(&code)==0);
   code.curr=6;
   assert(CodeVAR(&code)==1);
   


   return 0;
}