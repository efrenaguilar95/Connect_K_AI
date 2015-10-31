#include "gametree.h"
#include <iostream>



void print_board(int** board, int colCount, int rowCount)
{
	int row = rowCount-1;
	while(row >= 0)
	{
		for(int col = 0; col<colCount; col++)
		{
			std::cout<<board[row][col];
		}
		std::cout<<std::endl;
		row -= 1;
	}
}

int checkvictory(int** gameState, int numCols, int numRows, int col, int row) {
	//1 means Ai won, -1 means human won, 0 means board is filled with no winner; is no victory yet 2

    bool victory;
    int c;

	c = gameState[row][col];

	std::cout << "c is "<<c << std::endl;


		victory = true;

		//check off bound

		//check row right

		for (int x = 0; x < 4; x++){
			if(col+x > numCols){
				victory = false;
				break;
			}

			if(gameState[col+x][row] != c){
				victory = false;
				break;
			}
		}

		if (victory) return c;

		//check row right left
		for (int x = 0; x < 4; x++){
			if(col-x < 0){
				victory = false;
				break;
			}

			if(gameState[col-x][row] != c){
				victory = false;
				break;
			}
		}

		if (victory) return c;

		//check col right
		for (int y = 0; y < 4; y++){
			if(row+y > numRows){
				victory = false;
				break;
			}

			if(gameState[col][row+y] != c){
				victory = false;
				break;
			}
		}

		if (victory) return c;

		//check col left
		for (int y = 0; y < 4; y++){
			if(row-y < 0){
				victory = false;
				break;
			}
			if(gameState[col][row-y] != c){
				victory = false;
				break;
			}
		}

		if (victory) return c;

		//check diagonal up right
		for (int xy = 0; xy < 4; xy++){
			if(col+xy > numCols or row+xy > numRows){
				victory = false;
				break;
			}
			if(gameState[col+xy][row+xy] != c){
				victory = false;
				break;
			}
		}

		if (victory) return c;

		//check diagonal up left
		for (int xy = 0; xy < 4; xy++){
			if(col+xy > numCols or row-xy < 0){
				victory = false;
				break;
			}
			if(gameState[col+xy][row-xy] != c){
				victory = false;
				break;
			}
		}

		//check diagonal down right
		for (int xy = 0; xy < 4; xy++){
			if(col-xy < 0 or row+xy > numRows){
				victory = false;
				break;
			}
			if(gameState[col-xy][row+xy] != c){
				victory = false;
				break;
			}
		}
		if (victory) return c;

		//check diagonal down left
		for (int xy = 0; xy < 4; xy++){
			if(col-xy < 0 or row-xy < 0){
				victory = false;
				break;
			}
			if(gameState[col-xy][row-xy] != c){
				victory = false;
				break;
			}
		}
		if (victory) return c;


    for (int cl = 0; cl<numCols; cl++){
    	for (int rw = 0; rw<numRows; rw++){
    		std::cout<< gameState[cl][rw] << std::endl;
    		if(gameState[cl][rw] == 0) return 2;
    	}

    }
    std::cout << "ending"<< std::endl;

    return 0;


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
			board[row][col] = 0;
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
		board[row][col] = current_player;
		print_board(board, colCount, rowCount);
		int v = checkvictory(board, colCount, rowCount, col, row);
		std::cout << ";" << v << ";"<<std::endl;
		if (v!=2) break;



	}

}



