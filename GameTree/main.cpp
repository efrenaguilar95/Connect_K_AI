#include "gametree.h"
#include <iostream>



void print_board(int** board, int colCount, int rowCount)
{
	int row = rowCount-1;
	while(row >= 0)
	{
		for(int col = 0; col<colCount; col++)
		{
			std::cout<<board[col][row];
		}
		std::cout<<std::endl;
		row -= 1;
	}
}

int check_winner(int ** gameState, int numCols, int numRows, int k)
{
	//1 means Ai won, -1 means human won, 0 means board is filled with no winner
	    bool victory;
	    int c;

	    for (int col = 0; col<numCols; col++){
	    	for (int row = 0; row<numRows; row++){
	    		c = gameState[col][row];
	    		if (c!=0)
	    		{
	    			victory = true;

	    			//check victory right

	    			if(col <= (numCols - (k-1)))
	    			{
	    				for (int x = 0; x < k; x++)
	    				{
	    					if(gameState[col+x][row] != c)
	    					{
	    						victory = false;
	    						break;
	    					}
	    				}
	    			}
	    			else victory = false;

	    			if (victory) return c;

	    			victory = true;

	    			//check victory left

	    			if(col >= k-1)
	    			{
	    				for (int x = 0; x < k; x++){
	    					if(gameState[col-x][row] != c){
	    						victory = false;
	    						break;
	    					}
	    				}
	    			}
	    			else victory = false;

	    			if (victory) return c;

	    			victory = true;

	    			//check victory up

	    			if(row <= (numRows - (k-1)))
	    			{
	    				for (int y = 0; y < k; y++){
	    					if(gameState[col][row+y] != c){
	    						victory = false;
	    						break;
	    					}
	    				}
	    			}

	    			else victory = false;

	    			if (victory) return c;

	    			victory = true;

	    			//check victory down

	    			if(row >= k-1)
	    			{
	    				for (int y = 0; y < k; y++){
	    					if(gameState[col][row-y] != c){
	    						victory = false;
	    						break;
	    					}
	    				}
	    			}
	    			else victory = false;


	    			if (victory) return c;

	    			victory = true;

	    			//check diagonal up right
	    			if((row <= (numRows - (k-1))) && (col <= (numCols - (k-1))))
	    			{
	    				for (int xy = 0; xy < k; xy++){
	    					if(gameState[col+xy][row+xy] != c){
	    						victory = false;
	    						break;
	    					}
	    				}
	    			}
	    			else victory = false;

	    			if (victory) return c;

	    			victory = true;

	    			//check diagonal up left
	    			if((row <= (numRows - (k-1))) && (col >= (k-1)))
	    			{
	    				for (int xy = 0; xy < k; xy++){
	    					if(gameState[col-xy][row+xy] != c){
	    						victory = false;
	    						break;
	    					}
	    				}
	    			}
	    			else victory = false;

	    			if(victory) return c;

	    			victory = true;


	    			//check diagonal down right
	    			if((row >= (k-1)) && (col <= (numCols - (k-1))))
	    			{
	    				for (int xy = 0; xy < k; xy++){
	    					if(gameState[col+xy][row-xy] != c){
	    						victory = false;
	    						break;
	    					}
	    				}
	    			}
	    			else victory = false;

	    			if (victory) return c;

	    			victory = true;

	    			//check diagonal down left
	    			if((row >= (k-1)) && (col >= (k-1)))
	    			{
	    				for (int xy = 0; xy < k; xy++){
	    					if(gameState[col-xy][row-xy] != c){
	    						victory = false;
	    						break;
	    					}
	    				}
	    			}
	    			else victory = false;

	    			if (victory) return c;
	    		}
	    	}

	    }

	    return 0;



}

//This is assuming that gravity is on AI = 1; Player = -1; NP = 0;
int check_winner2(int** gameState, int row, int col, int numCols, int numRows, int k, bool gravity, int player)
{
	int val = 0;
	int counter = 0;
	int verticalCount;
	int horizontalCount;
	int lrDiagCount;
	int rlDiagCount;
	if(gravity)
	{
		//Check underneath where the piece was just placed
		if(row >= k-1)
		{
			for (int y = 0; y < k; y++)
			{
				if(gameState[col][row-y] != player)
					break;
				counter++;
			}
		}
		if(counter == k)
			return 10;

		verticalCount = counter;
		counter = 0;

		//Check if the row has a winner

		//Start by checking left
		if(col != 0)
		{
			for(int x = col-1; x >= 0; x--)
			{
				if(counter == (k-1) || gameState[x][row] != player)
					break;
				counter++;
			}
		}
		if(counter == (k-1))
			return 10;
		//Then check right
		if(col != numCols-1)
		{
			for(int x = col+1; x < numCols; x++)
			{
				if(counter == (k-1) || gameState[x][row] != player)
					break;
				counter++;
			}
		}
		if(counter == (k-1))
			return 10;
		horizontalCount = counter;
		counter = 0;

		//Check left right diagonal(/)

		//Start by checking bottom left
		if(row != 0 && col != 0)
		{
			int x,y;
			for(x = col-1, y = row-1; x >= 0 && y >= 0; x--, y--)
			{
				if(counter == (k-1) || gameState[x][y] != player)
					break;
				counter++;
			}
		}
		if(counter == (k-1))
			return 10;

		//Then check top right
		if(row != (numRows-1) && col != (numCols-1))
		{
			int x,y;
			for(x = col+1, y = row+1; x < numCols && y < numRows; x++, y++)
			{
				if(counter == (k-1) || gameState[x][y] != player)
					break;
				counter++;
			}
		}
		lrDiagCount = counter;
		if(counter == (k-1))
			return 10;
		counter = 0;

		//Lastly, check right left diagonal (\)

		//Start by checking bottom right
		if(row != 0 && col != (numCols-1))
		{
			int x,y;
			for(x = col+1, y = row-1; x < numCols, y>=0; x++, y--)
			{
				if(counter == (k-1) || gameState[x][y] != player)
					break;
				counter++;
			}
		}
		if(counter == (k-1))
			return 10;

		//Then check top left
		if(row != (numRows-1) && col!= 0)
		{
			int x,y;
			for(x = col-1, y = row+1; x >= 0 && y < numRows; x--, y++)
			{
				if(counter == (k-1) || gameState[x][y] != player)
					break;
				counter++;
			}
		}

		rlDiagCount = counter;
		if(counter == (k-1))
			return 10;
		return 0;



	}
}



int main()
{
	//Original GameTree testing code
	/*
	//Random comment
	GameTree<int> gTree(10);
	//gTree.print_value();
	GameTree<int> gTree2(8);
	//GameTree<int>* g2 = &gTree2;
	gTree.addChild(gTree2);
	//gTree.first_child->print_value();
	GameTree<int> gTree3(7);
	GameTree<int> gTree4(14);
	GameTree<int> gTree5(25);
	gTree.first_child->addSibling(gTree3);
	gTree.first_child->addChild(gTree4);
	gTree.first_child->next_sibling->addChild(gTree5);
	//std::cout << gTree.first_child->next_sibling->value<< std::endl;
	GameTree<int> gTree6(11);
	GameTree<int> gTree7(18);
	gTree.first_child->addSibling(gTree6);
	gTree.first_child->addChild(gTree7);
	gTree.dfs();
	std::cout<< "end" << std::endl;

	GameTree<int>* k = &gTree;
	*/

	int colCount = 9;
	int rowCount = 7;


	int** board = NULL;
	board = new int*[colCount];
	for(int i = 0; i<colCount; i++)
	{
		board[i] = new int[rowCount];
	}

	for(int col = 0; col<colCount; col++)
	{
		for(int row = 0; row<rowCount; row++)
		{
			board[col][row] = 0;
		}
	}
	print_board(board, colCount, rowCount);
	std::cout<<std::endl;
	//board[3][2] = 1;
	print_board(board, colCount, rowCount);

	int current_player = 1;
	while(true) //Once you get isWinner function working this should say while isWinner = false
	{
		current_player *= -1;
		std::cout<<current_player<<"'s turn"<<std::endl;
		std::cout<<"What row would you like to place piece? (Bottom row is zero) : "<<std::endl;
		int row, col;
		std::cin>> row;
		std::cout<<std::endl;
		std::cout<<"What column would you like to place piece? (First column is zero) : "<<std::endl;
		std::cin>> col;
		std::cout<<std::endl;
		board[col][row] = current_player;
		print_board(board, colCount, rowCount);
		//int winner = check_winner(board, colCount, rowCount, 4);
		int winner = check_winner2(board, row, col, colCount, rowCount, 4, true, current_player);
		if(winner == 10)
			std::cout<<current_player<<" wins!"<<std::endl;


	}

}



