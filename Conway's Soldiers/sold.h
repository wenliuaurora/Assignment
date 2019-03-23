#include<stdio.h>
#include<assert.h>
#include <stdlib.h>

#define ROW 8
#define COL 7
#define NUMBOARDS 100000
struct board {
	int parent;
	int board[ROW][COL];
};
typedef struct board Board;

Board initialboard(void);
Board  jumpup(Board currentboard, int current,int row, int col);
Board  jumpright(Board currentboard, int current, int row, int col);
Board  jumpleft(Board currentboard, int current,  int row, int col);
int testtarget(Board newboard, int targetROW, int targetCOL, int position);
void print(Board lastboard, Board saveboard[]);
void testconway(Board saveboard[]);

