#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"parser.h"
#include<ctype.h>

int main(int argc, char* argv[]){
	Code code;
	/* Exit if no file address */
	if (argc != 2) {
		fprintf(stderr, "Need file address.\n");
		exit(1);
	}
    /* Creat the code array, then run the parser */
    InitCode(&code, argv[1]);
    ParserMain(&code);
    /* Free allocated memory before coderam end */
    FreeArray(&code);
    
    return 0;
}

void InitCode(Code* code, char* file){
	int i;
	FILE* fp;
	code->curr = 0;
	if ((fp = fopen(file, "r")) == NULL) {
		fprintf(stderr, "Error in opening file.\n");
		exit(1);
	}
	/* Count the code number */
	code->totalnum = Count(fp);
    /*Give space for code*/
	code->words = (char **)malloc((code->totalnum + 1) * sizeof(char *));
	for (i = 0; i <=code->totalnum; i++) {
		code->words[i] = (char *)calloc(MAXSTRLEN, sizeof(char));
	}
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
    
    /* Free all individual token strings */
    for(i = 0; i < code->totalnum + 1; i++) {
        free(code->words[i]);
    }
    /* Free the token pointer array */
    free(code->words);
}


void ParserMain(Code* code){
/*First check the number of "{" and"}"*/
	if(!CountPunctuation(code)){
        fprintf(stderr, "CODE,The number of punctuation is wrong.\n");
    }
	PLUSCURR;
	CheckCode(code);
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

void CheckCode(Code* code){
    if (ISSAME(CURRENTWORDS, "}")&&code->doloopflag==1) {
		return;
		}
	if (ISSAME(CURRENTWORDS, "FD")) {
        Code_FD(code);
	}
	else if (ISSAME(CURRENTWORDS, "LT")) {
		Code_LT(code);
	}
	else if (ISSAME(CURRENTWORDS, "RT")) {
		Code_RT(code);
	}
	else if (ISSAME(CURRENTWORDS, "DO")) {
		Code_DO(code);
	}
	else if (ISSAME(CURRENTWORDS, "SET")) {
        Code_SET(code);
	}
	if (ISSAME(CURRENTWORDS, "}")) {
		return;
	}
	/* continues recursively until the end of the array */
	if(code->curr<code->totalnum){
		PLUSCURR;
        CheckCode(code);
	}
}

void Code_FD(Code* code)
{
	PLUSCURR;
	/* Check if the next token is a valid VAR/NUM */
	if(!CodeVARNUM(code)){
	fprintf(stderr, "CODE,should be var or num after LD.\n");
	}
	return;
}

void Code_LT(Code* code)
{
	PLUSCURR;
	/* Check if the next token is a valid VAR/NUM */
	if(!CodeVARNUM(code)){
	fprintf(stderr, "CODE,should be var or num after LT.\n");
	}
	return;
}

void Code_RT(Code* code)
{
	PLUSCURR;
	/* Check if the next token is a valid VAR/NUM */
	if(!CodeVARNUM(code)){
	fprintf(stderr, "CODE,should be var or num after RT.\n");
	}
	return;
}

bool CodeVARNUM(Code* code)
{
	int pnum=0;
	unsigned int i=0;
	/* If the token is a single Uppercase letter, the token is valid */
	if (CodeVAR(code)) {
		return TRUE;
		}
	/* Else if the token is a number, the token is valid */
	else{
		 if(CURRENTWORDS[0]=='.'){
			 pnum++;
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
	  return TRUE;
	}
	/* If token is neither variable or number, exit the Code */
	fprintf(stderr, "CODE,The variable or number is wrong.\n");
	return FALSE;
}
}

bool CodeVAR(Code* code)
{
	/* If the token is a single Uppercase letter token is a valid VAR */
	if (CURRENTWORDS[0]>='A'&&CURRENTWORDS[0]<='Z'&&CURRENTWORDS[1]=='\0') {
		return TRUE;
	}/* If not, return a 0 to indicate the token is not a variable */
		return FALSE;
}

void Code_DO(Code* code)
{
	int returnflag;
	/* If looping variable token is invalid, then parsing has failed */
	PLUSCURR;
	if (CodeVAR(code)==FALSE) {
		fprintf(stderr, "CODE,The variable which after the DO instruction is wrong.\n");
	    returnflag=1;
	}
	/* Parse 'FROM' token */
	PLUSCURR;
	if(!ISSAME(CURRENTWORDS,"FROM")){
		fprintf(stderr, "CODE,should be FROM in DO instruction.\n");
		returnflag=1;
	}
	/* Parse loop start value token */
	PLUSCURR;
	if(!CodeVARNUM(code)){
		fprintf(stderr, "CODE,should be VARNUM after the FROM instruction.\n");
		returnflag=1;
	}	
	/* Parse 'TO' token */
	PLUSCURR;
	if(!ISSAME(CURRENTWORDS,"TO")){
		fprintf(stderr, "CODE,should be TO in DO instruction.\n");
		returnflag=1;
	}
	/* Parse loop end value token */
	PLUSCURR;
	if(!CodeVARNUM(code)){
		fprintf(stderr, "CODE,should be VARNUM after the TO instruction.\n");
		returnflag=1;
	}
	PLUSCURR;
	if(!ISSAME(CURRENTWORDS,"{")){
		fprintf(stderr, "CODE,should be { in the DO instruction.\n");
		returnflag=1;
	}
	/* Begin to parse the instruction list that follows the DO loop */
    if(returnflag==1)
	{
		return;
	}
	code->doloopflag=1;
	PLUSCURR;
    CheckCode(code);
	code->doloopflag=0;
}

void Code_SET(Code* code)
{
	int returnflag=0;
	/* Parse token for variable to be set */
	PLUSCURR;
	if (CodeVAR(code) == FALSE) {
		fprintf(stderr, "CODE,should be VARNUM after the SET instruction.\n");
		returnflag=1;
	}
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
	Code_POLISH(code);
	return;
}
void Code_POLISH(Code* code)
{
	/* Check if the token is a valid operator */
	if (ISSAME(CURRENTWORDS, ";")) {
		return;
	}
	else if (Code_OP(code)){
		return;
	}
	/* Check if the token is a variable/number */
	else if(CodeVARNUM(code)){
		return;
	}
	/* Continue parsing the Polish expression */
		PLUSCURR;
		Code_POLISH(code);
}

bool Code_OP(Code* code){
	if(CURRENTWORDS[0]=='+'||CURRENTWORDS[0]=='-'||CURRENTWORDS[0]=='*'||CURRENTWORDS[0]=='/'){
		return TRUE;
	}
	return FALSE;
}