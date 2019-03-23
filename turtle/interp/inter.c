#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <float.h>
#include "neillsdl2.h"
#include "inter.h"

int main(int argc, char* argv[]){
    Code code;
    Turtle turtle;
    SDL_Simplewin sw;
    if (argc != 2) {
		fprintf(stderr, "Need file address.\n");
		exit(1);
	}
    InitCode(&code,argv[1]);
    InitTurtle(&turtle);
    Neill_SDL_Init(&sw);
    InterpreterMain(&code,&sw,&turtle);
    while (!sw.finished) {
		Neill_SDL_Events(&sw);
        }
    SDL_Delay(DISPLAYDELAY);
    FreeArray(&code);
    atexit(SDL_Quit);
    return 0;
}

void InitCode(Code* code, char* file){
	int i;
	FILE* fp;
	code->curr = 0;
    for(i=0;i<ALPHABET;i++){
        code->vars[i]=0.0;
		code->varuse[i]=0;
    }
	if ((fp = fopen(file, "r")) == NULL) {
		fprintf(stderr, "Error in opening file.\n");
		exit(1);
	}
	/* Count the code number */
	code->totalnum = Count(fp);
    /*Give space for code*/
	code->words = (char **)malloc((code->totalnum + 1) * sizeof(char *));
	for (i = 0; i <= code->totalnum; i++) {
		code->words[i] = (char* )calloc(MAXSTRLEN, sizeof(char));
	}
	code->doloopflag=0;
	/* Copy all code to array */
	i = 0;
	while (fscanf(fp, "%s", code->words[i++]) == 1&&i<MAXCODENUM);    
	if (fclose(fp) != 0) {
		fprintf(stderr, "Error in closing file.\n");
		FreeArray(code);
        exit(1);
	}
}
int Count(FILE* fp){
	int count = 0;
	char s[MAXSTRLEN + 1];
	/* Count the lenth of string */
	while (fscanf(fp, "%s", s) == 1) {
		Checkstrlenth(s);
		count++;
	}
	rewind(fp);
	return count;
}

void Checkstrlenth(char s[]){
	if (strlen(s) > MAXSTRLEN) {
			fprintf(stderr, "The string is more than Maxstringlen\n");
			exit(1);
			}
}

void FreeArray(Code* code){
    int i;
    for(i = 0; i <= code->totalnum ; i++) {
        free(code->words[i]);
    }
    free(code->words);
}

void PushStack(Stack* stack, double value)
{
	if (stack->top > MAXSTACKSIZE) {
			fprintf(stderr, "Stack,too many values\n");
	}
	/* Add the given value to the the top of the stack */
	stack->sta[stack->top] = value;
	stack->top=stack->top+1;
}

double PopStack(Stack* stack)
{
	stack->top--;
	/* Exit the program if the stack has 'underflowed' */
	if (stack->top < 0) {
			fprintf(stderr, "Stack,there is no value to pop\n");
	}
	/* Return the value from the top of the stack */
	return stack->sta[stack->top];
}

void InterpreterMain(Code* code,SDL_Simplewin* sw,Turtle* turtle){
/*First check the number of "{" and"}"*/
	if(!CountPunctuation(code)){
        fprintf(stderr, "CODE,The number of punctuation is wrong.\n");
    }
	PLUSCURR;
	CheckCode(code,sw,turtle);
}

bool CountPunctuation(Code* code){
   int i, bracket1=0,bracket2=0;
   if(!ISSAME(code->words[0],"{")){
	   fprintf(stderr, "CODE,The first word should be {.\n"); 
       return FALSE;
   }
    for(i=0;i<code->totalnum;i++){
        if(ISSAME(code->words[i],"{")){
            bracket1++;
        }
        if(ISSAME(code->words[i],"}")){
            bracket2++;
        }
    }
	if(ISSAME(code->words[code->totalnum-1],"}")){
		if(bracket1==bracket2){
			 return TRUE;
		}
    }
	else fprintf(stderr, "CODE,The last word should be }.\n"); 
	return FALSE;  
}

void InitTurtle(Turtle* turtle){
    turtle->angle=M_PI;
    turtle->currposition[0]=INITX;
    turtle->currposition[1]=INITY;
    turtle->prevposition[0]=INITX;
    turtle->prevposition[1]=INITY;
}
void CheckCode(Code* code,SDL_Simplewin* sw,Turtle* turtle){
    Neill_SDL_Events(sw);
    if (sw->finished) {
		atexit(SDL_Quit);
		exit(0);
        } 
	if (ISSAME(CURRENTWORDS, "}")&&code->doloopflag==1) {
		return;
		}
	if (ISSAME(CURRENTWORDS, "FD")) {
        Code_FD(code,sw,turtle);
	}
	else if (ISSAME(CURRENTWORDS, "LT")) {
		Code_LT(code,turtle);
	}
	else if (ISSAME(CURRENTWORDS, "RT")) {
		Code_RT(code,turtle);
	}
	else if (ISSAME(CURRENTWORDS, "DO")) {
		Code_DO(code,sw,turtle);
	}
	else if (ISSAME(CURRENTWORDS, "SET")) {
        Code_SET(code);
	}
	if(code->curr<code->totalnum){
		PLUSCURR;
        CheckCode(code,sw,turtle);
	}
}

void Drawline(Turtle* turtle, SDL_Simplewin* sw){
	Neill_SDL_SetDrawColour(sw, 255, 255, 255);
	SDL_RenderDrawLine(sw->renderer, (int)turtle->prevposition[0], (int)turtle->prevposition[1], (int)turtle->currposition[0], (int)turtle->currposition[1]);
    SDL_RenderPresent(sw->renderer);
	Neill_SDL_UpdateScreen(sw);
    Neill_SDL_Events(sw);
}

void Code_FD(Code* code,SDL_Simplewin* sw,Turtle* turtle){
	double value;
	PLUSCURR;
	/* Check if the next token is a valid VAR/NUM */
	if(!CodeVARNUM(code,&value)){
	fprintf(stderr, "CODE,should be var or num after LD.\n");
	}
	turtle->prevposition[0]=turtle->currposition[0];
	turtle->prevposition[1]=turtle->currposition[1];
	turtle->currposition[0]=turtle->currposition[0]+(value*cos(turtle->angle));
    turtle->currposition[1]=turtle->currposition[1]+(value*sin(turtle->angle));
	Drawline(turtle,sw);
	return;
}

void Code_LT(Code* code,Turtle* turtle)
{
	double value; 
	PLUSCURR;
	/* Check if the next token is a valid VAR/NUM */
	if(!CodeVARNUM(code,&value)){
	fprintf(stderr, "CODE,should be var or num after LT.\n");
	}
	Changeangle(turtle,-value);
	return;
}

void Code_RT(Code* code,Turtle* turtle){
	double value; 
	PLUSCURR;
	/* Check if the next token is a valid VAR/NUM */
	if(!CodeVARNUM(code,&value)){
	fprintf(stderr, "CODE,should be var or num after RT.\n");
	}
	Changeangle(turtle,value);
	return;
}

void Changeangle(Turtle* turtle,int value){
    turtle->angle=turtle->angle+DEGREETORAD*value;
	while(turtle->angle>=2*M_PI){
      turtle->angle=turtle->angle-(2*M_PI);
	  }
    while(turtle->angle<(0.0)){
      turtle->angle=turtle->angle+(2*M_PI);
}
}

/*if the current string is a capital letter 
*than take its value and return*/
bool CodeVARNUM(Code* code,double* numorvar)
{
	int varposition,pnum=0;
	unsigned int  i=0;
	if (CodeVAR(code)) {
		varposition=CURRENTWORDS[0]-'A';
		*numorvar=code->vars[varposition];
		return TRUE;
		}
	else{
		 if(CURRENTWORDS[0]=='.'){
			 pnum++;
			 }
			 if(CURRENTWORDS[0]!='-'&&(isdigit((int)CURRENTWORDS[0])==0)&&CURRENTWORDS[0]!='.'){
			 return FALSE;
			 }
			 for(i=1; i<=strlen(CURRENTWORDS); i++){
				 if(CURRENTWORDS[i]!='.'&&(isdigit((int)CURRENTWORDS[i])==0)&&CURRENTWORDS[i]!='\0'){
					 return FALSE;
					 }
					 if(CURRENTWORDS[i]=='.'){
						 pnum++;
						 }
						 }
						 if((pnum!=0)&&(pnum!=1)){
							 return FALSE;
							 }
	  *numorvar=atof(CURRENTWORDS);
	  return TRUE;
	  }
	fprintf(stderr, "CODE,The variable or number is wrong.\n");
	return FALSE;
}

/*Make sure the variable is valid and not in use*/
bool CodeVAR(Code* code)
{
	/* If the token is a single Uppercase letter token is a valid VAR */
	if (CURRENTWORDS[0]>='A'&&CURRENTWORDS[0]<='Z'&&CURRENTWORDS[1]=='\0') {
		return TRUE;
	}/* If not, return FALSE to indicate the token is not a variable */
		return FALSE;
}

void UseVAR(Code* code,int varposition){

		if (code->varuse[varposition]==1) {
		fprintf(stderr, "CODE,The variable has been used.\n");
		}
		else
			code->varuse[varposition]=1;
}

void Code_DO(Code* code,SDL_Simplewin* sw,Turtle* turtle)
{
	int varposition,returnflag=0;
	double numorvar,endloop=0;
	/* If looping variable token is invalid, then parsing has failed */
	PLUSCURR;
	if (CodeVAR(code)==FALSE) {
		fprintf(stderr, "CODE,The variable which after the DO instruction is wrong.\n");
	    returnflag=1;
	}
	varposition=CURRENTWORDS[0]-'A';
	UseVAR(code,varposition);
	PLUSCURR;
	if(!ISSAME(CURRENTWORDS,"FROM")){
		fprintf(stderr, "CODE,should be FROM in DO instruction.\n");
		returnflag=1;
	}
	PLUSCURR;
	if(!CodeVARNUM(code,&numorvar)){
		fprintf(stderr, "CODE,should be VARNUM after the FROM instruction.\n");
		returnflag=1;
	}	
	else 
	{
		code->vars[varposition]=numorvar;
		}
	PLUSCURR;
	if(!ISSAME(CURRENTWORDS,"TO")){
		fprintf(stderr, "CODE,should be TO in DO instruction.\n");
		returnflag=1;
	}
	/* Parse loop end value token */
	PLUSCURR;
	if(CodeVARNUM(code,&endloop)==0){
		fprintf(stderr, "CODE,should be VARNUM after the TO instruction.\n");
		returnflag=1;
	}
	/* Begin to parse the instruction list that follows the DO loop */
    PLUSCURR;
	if(!ISSAME(CURRENTWORDS,"{")){
		fprintf(stderr, "CODE,should be { in the DO instruction.\n");
		returnflag=1;
	}
	if(returnflag==1)
	{
		return;
	}
	Doloop(code,sw,varposition,(int)endloop,turtle);
	code->doloopflag=0;
    code->varuse[varposition]=0;
}

void Doloop(Code* code,SDL_Simplewin* sw,int varposition,int endloop,Turtle* turtle){
	int begin=0;
	code->doloopflag=1;
	if(code->vars[varposition]>endloop){
		fprintf(stderr, "CODE,wrong number in DO loop.\n");
		return;
	}
	PLUSCURR;
	begin=code->curr;
	while(code->vars[varposition]<=endloop){
		code->curr=begin;
		code->vars[varposition]=code->vars[varposition]+1;
		CheckCode(code,sw,turtle);
	}
	return;
}
void Code_SET(Code* code)
{
	int varposition,returnflag=0;
	Stack stack;
	stack.top=0;
	/* Parse token for variable to be set */
	PLUSCURR;
	if (CodeVAR(code) == FALSE) {
		fprintf(stderr, "CODE,should be VARNUM after the SET instruction.\n");
		returnflag=1;
	}
	varposition=CURRENTWORDS[0]-'A';
		UseVAR(code,varposition);
	/* Parse ':=' token */
	PLUSCURR;
	if(!ISSAME(CURRENTWORDS,":=")){
		fprintf(stderr, "CODE,should be ':=' in SET instruction.\n");
		returnflag=1;
	}
    if(returnflag==1){
		return;
	}
	/* Calculate the polish expression */
	PLUSCURR;
	Code_POLISH(code,&stack);
	code->vars[varposition]=PopStack(&stack);
	code->varuse[varposition]=0;
	return;
}

void Code_POLISH(Code* code,Stack* stack)
{
	double value=0;
	if (ISSAME(CURRENTWORDS, ";")) {
		if(stack->top!=1){
			fprintf(stderr, "CODE,no value in stack ,polish failed.\n");
		}
		return;
	}
	else if (ISOP(code)){
		Code_OP(code,stack);
	}
	/* Check if the token is a variable/number */
	else if(CodeVARNUM(code,&value)){
		PushStack(stack,value);
	}
	/* Continue parsing the Polish expression */
		PLUSCURR;
		Code_POLISH(code,stack);
	
}

bool Code_OP(Code* code,Stack* stack){
	double stackvalue1=0,stackvalue2=0;
	if(stack->top<2){
		fprintf(stderr, "CODE,there is less than 2 numbers in stack,polish failed.\n");
		return FALSE;
	}
	stackvalue1=PopStack(stack);
	stackvalue2=PopStack(stack);
	if(ISSAME(CURRENTWORDS,"+")){
		PushStack(stack,stackvalue1+stackvalue2);
		return TRUE;
	}
	else if(ISSAME(CURRENTWORDS,"-")){
		PushStack(stack,stackvalue1-stackvalue2);
		return TRUE;
	}
	else if(ISSAME(CURRENTWORDS,"*")){
		PushStack(stack,stackvalue1*stackvalue2);
		return TRUE;
	}
	else if(ISSAME(CURRENTWORDS,"/")){
		if(stackvalue1<MINNUM){
			fprintf(stderr, "CODE,can not divided by 0,polish failed.\n");
			return FALSE;
		}
		else PushStack(stack,stackvalue2/stackvalue1);
		return TRUE;
	}
	
	return FALSE;
}
bool ISOP(Code* code){
if(CURRENTWORDS[0]=='+'||CURRENTWORDS[0]=='-'||CURRENTWORDS[0]=='*'||CURRENTWORDS[0]=='/'){
		return TRUE;
	}
	return FALSE;
}