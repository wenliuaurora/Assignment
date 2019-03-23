#include "sold.h"


int main(int argc, char const * argv[])
{
	/* current is the current parent board*/
/* position is the blank place to store board */
	int targetROW, targetCOL, current = 0, position = 0, row, colum, flag = 0;
	static Board saveboard[NUMBOARDS];

	/* argc user input on command line */
    /* sold 1 2 */
	/* argv[0] = sold */
	/* argv[1] = inputrow */
	/*argv[2]=inputcol*/

	targetROW = atoi(argv[1]);
	targetCOL = atoi(argv[2]);

	if (argc != 3)
	{
		printf("error number");
	}

	/*bulit initial board*/
	saveboard[0] = initialboard();
	position++;

	do {
		for (row = 0; flag == 0 && row < ROW; row++)
		{
			for (colum = 0; flag == 0 && colum < COL; colum++)
			{

				/* just when the tile's colum is the same as targetCOL jump up */
				/*because this thought can reduce the number of board and not influence the possible to get target */
				if (flag == 0 && colum == targetCOL && saveboard[current].board[row][colum] == 1 && saveboard[current].board[row - 1][colum] == 1 && saveboard[current].board[row - 2][colum] == 0)
				{
					saveboard[position] = jumpup(saveboard[current], current, row, colum);
					flag = testtarget(saveboard[position], targetROW, targetCOL, position);
					position++;
					if (position > NUMBOARDS)
						flag = -2;
				}

				/* just when the next tile's colum is less than targetCOl jump right */
				if (flag == 0 && colum + 2 <= targetCOL && saveboard[current].board[row][colum] == 1 && saveboard[current].board[row][colum + 1] == 1 && saveboard[current].board[row][colum + 2] == 0)
				{
					saveboard[position] = jumpright(saveboard[current], current, row, colum);
					flag = testtarget(saveboard[position], targetROW, targetCOL, position);
					position++;
					if (position > NUMBOARDS)
						flag = -2;
				}

				/* just when the next tile's colum is more than targetCOl jump left */
				if (flag == 0 && colum - 2 >= targetCOL && saveboard[current].board[row][colum] == 1 && saveboard[current].board[row][colum - 1] == 1 && saveboard[current].board[row][colum - 2] == 0)
				{
					saveboard[position] = jumpleft(saveboard[current], current, row, colum);
					flag = testtarget(saveboard[position], targetROW, targetCOL, position);
					position++;
					if (position > NUMBOARDS)
						flag = -2;
				}

			}
		}
		if (flag == 0)
			current++;
		if (current + 1 == position && current != 1)
		{
			flag = -1;
			printf("use %d board\n", current);
		}
	} while (flag == 0);

	if (flag == -2)
		printf("not find the answer,the board number is not enough\n");
	if (flag == -1)
		printf("this target is impossible to get\n");
	if (flag > 0)
	{
		printf("use%dboard\n", flag);
		print(saveboard[flag], saveboard);
	}

	testconway(saveboard);
	return 0;
}


Board initialboard()
{
	Board newboard;
	int colum, row;
	for (row = 0; row < ROW; row++)
		for (colum = 0; colum < COL; colum++)
		{
			if (row > 3)
				newboard.board[row][colum] = 1;
			else
				newboard.board[row][colum] = 0;
		}
	newboard.parent = -1;
	return newboard;
}

Board jumpup(Board currentboard, int current, int row, int col)
{
	Board newboard;
	int colum, rows;
	/*copy current board*/
	for (rows = 0; rows < ROW; rows++)
		for (colum = 0; colum < COL; colum++)
			newboard.board[rows][colum] = currentboard.board[rows][colum];

	newboard.board[row - 1][col] = 0;
	newboard.board[row][col] = 0;
	newboard.board[row - 2][col] = 1;
	newboard.parent = current;
	return newboard;
}

Board jumpright(Board currentboard, int current,  int row, int col)
{
	int rows, colum;

	Board newboard;
	for (rows = 0; rows < ROW; rows++)
		for (colum = 0; colum < COL; colum++)
			newboard.board[rows][colum] = currentboard.board[rows][colum];

	newboard.board[row][col + 1] = 0;
	newboard.board[row][col] = 0;
	newboard.board[row][col + 2] = 1;
	newboard.parent = current;
	return newboard;
}

Board jumpleft(Board currentboard, int current,  int row, int col)
{
	Board newboard;
	int colum, rows;
	for (rows = 0; rows < ROW; rows++)
		for (colum = 0; colum < COL; colum++)
			newboard.board[rows][colum] = currentboard.board[rows][colum];

	newboard.board[row][col - 1] = 0;
	newboard.board[row][col] = 0;
	newboard.board[row][col - 2] = 1;
	newboard.parent = current;
	return newboard;
}

/*whether the board achieve our goal*/
int testtarget(Board theboard, int targetROW, int targetCOL, int position)
{
	return (theboard.board[targetROW][targetCOL] == 1 ? position : 0);
}

void print(Board lastboard, Board saveboard[])
{
	int row, colum;
	if (lastboard.parent != -1)
	{

		print(saveboard[lastboard.parent], saveboard);

		for (row = 0; row < ROW; row++)
		{
			for (colum = 0; colum < COL; colum++)
			{
				if (lastboard.board[row][colum] == 0)
					printf(".");
				else
					printf("X");
			}
			printf("\n");
		}
		printf("\n");
	}

	if (lastboard.parent == -1)
	{
		for (row = 0; row < ROW; row++)
		{
			for (colum = 0; colum < COL; colum++)
			{
				if (lastboard.board[row][colum] == 0)
					printf(".");
				else
					printf("X");
			}
			printf("\n");
		}
	}
}



