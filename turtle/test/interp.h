#define ISSAME(A, B) (strcmp(A, B) == 0)
#define CURRENTWORDS code->words[code->curr]
#define PLUSCURR code->curr=code->curr+1
#define MAXSTRLEN 20
#define MAXCODENUM 1000 
#define TRUE 1
#define FALSE 0
#define MAXSTACKSIZE 100
#define ALPHABET 26
#define DEGREETORAD 2*M_PI/360
#define MINNUM 0.0001


#define INITX WWIDTH/2
#define INITY WHEIGHT/2
#define DISPLAYDELAY 2000

typedef int bool;
typedef struct code{
    char** words;
	int totalnum;
	int curr;
    double vars[ALPHABET];
    int varuse[ALPHABET];
    int doloopflag;
}Code;
typedef struct turtle{
    double currposition[2];
    double prevposition[2];
    double angle;
}Turtle;

typedef struct stack{
    double sta[MAXSTACKSIZE];
    int top;
}Stack;

void InitCode(Code* code, char* file);
int Count(FILE* fp);
void Checkstrlenth(char s[]);
void FreeArray(Code* code);
void PushStack(Stack* stack, double value);
double PopStack(Stack* stack);
void InterpreterMain(Code* code,SDL_Simplewin* sw,Turtle* turtle);
bool CountPunctuation(Code* code);
void InitTurtle(Turtle* turtle);
void CheckCode(Code* code,SDL_Simplewin* sw,Turtle* turtle);
void Drawline(Turtle* turtle, SDL_Simplewin* sw);
void Code_FD(Code* code,SDL_Simplewin* sw,Turtle* turtle);
void Code_LT(Code* code,Turtle* turtle);
void Code_RT(Code* code,Turtle* turtle);
void Changeangle(Turtle* turtle,int value);
bool CodeVARNUM(Code* code,double* numorvar);
bool CodeVAR(Code* code);
void UseVAR(Code* code,int varposition);
void Code_DO(Code* code,SDL_Simplewin* sw,Turtle* turtle);
void Doloop(Code* code,SDL_Simplewin* sw,int varposition,int endloop,Turtle* turtle);
void Code_SET(Code* code);
void Code_POLISH(Code* code,Stack* stack);
bool Code_OP(Code* code,Stack* stack);
bool ISOP(Code* code);