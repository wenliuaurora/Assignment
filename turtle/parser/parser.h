#define ISSAME(A, B) (strcmp(A, B) == 0)
#define CURRENTWORDS code->words[code->curr]
#define PLUSCURR code->curr=code->curr+1
#define MAXSTRLEN 20
#define MAXCODENUM 1000 
#define TRUE 1
#define FALSE 0

typedef int bool;
typedef struct Code {
	char **words;
	int totalnum;
	int curr;
	int doloopflag;
} Code;

void InitCode(Code *code, char *filename);
int Count(FILE *fp);
void Checkstrlenth(char s[]);
void FreeArray(Code *code);
void ParserMain(Code *code);
bool CountPunctuation(Code *code);
void CheckCode(Code* code);
void Code_FD(Code *code);
void Code_LT(Code *code);
void Code_RT(Code *code);
bool CodeVARNUM(Code *code);
bool CodeVAR(Code *code);
void Code_DO(Code *code);
void Code_SET(Code *code);
void Code_POLISH(Code *code);
bool Code_OP(Code *code);

