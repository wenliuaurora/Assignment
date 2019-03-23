#include "sold.h"
void testconway(Board saveboard[])
{
	int row,colum,testjumpup=0,testjumpright=0,testjumpleft=0;
	Board testboard0,testboard1,testboard2,save0,save1,save2;
	
	/*copy the initial board*/
	for (row = 0; row < ROW; row++)
		for (colum = 0; colum < COL; colum++)
		{
			testboard0.board[row][colum] = 0 ;
			testboard1.board[row][colum] = 0;
			testboard2.board[row][colum] = 0;
		}
	/*built board the first colum to  
	         hope change
	   0     1
	   1 ->  0
	   1     0    */
	testboard0.board[1][0] = 1;
	testboard0.board[2][0] = 1;
	testboard0.parent = 0;

	/*built board the first row like
	 hope change
	  1 1 0-> 0 0 1    */
	testboard1.board[0][0] = 1;
	testboard1.board[0][1] = 1;
	testboard1.parent = 0;

	/*built board the first row like
	 hope change
	  0 1 1-> 1 0 0    */
	testboard2.board[0][1] = 1;
	testboard2.board[0][2] = 1;
	testboard2.parent = 0;

	save0 = jumpup(testboard0, 0, 2, 0);
	save1 = jumpright(testboard1, 0, 0, 0);
	save2 = jumpleft(testboard2, 0, 0, 2);
for (row = 0; row < ROW; row++)
	for (colum = 0; colum < COL; colum++)
	{
		/*test jump up*/
		if (row == 0 && colum == 0)
			if (save0.board[0][0] != 1)
				testjumpup = 1;
		if (row != 0 && colum != 0)
			if (save0.board[row][colum] != 0)
				testjumpup = 1;

		/*test jump right*/
		if (row == 0 && colum == 2)
			if (save1.board[0][2] != 1)
				testjumpright = 1;
		if (row != 0 && colum != 2)
			if (save1.board[row][colum] != 0)
				testjumpright = 1;

		/*test jump left*/
		if (row == 0 && colum == 0)
			if (save2.board[0][0] != 1)
				testjumpleft = 1;
		if (row != 0 && colum != 0)
			if (save2.board[row][colum] != 0)
				testjumpleft = 1;


	}
	
	/*test whether the initial board success*/
	assert(saveboard[0].board[0][3] == 0);
	assert(saveboard[0].board[4][2] == 1);
	
	/* test testtarget */
	assert(testtarget(saveboard[0], 0, 0, 3) == 0);
	assert(testtarget(saveboard[0], 4, 3, 1) == 1);

	/*test jump result ,use flag to test */
	assert(testjumpup == 0);
	assert(testjumpright == 0);
	assert(testjumpleft == 0);
}
