#include "AIShell.h"
#include <iostream>


AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->deadline=0;
	this->numRows=numRows;
	this->numCols=numCols;
	this->gravityOn=gravityOn;
	this->gameState=gameState;
	this->lastMove=lastMove;
	this->gameTree=new GameTree<int **>;
	makeTree(gameTree);
}


AIShell::~AIShell()
{
	
	//delete the gameState variable.
	for (int i =0; i<numCols; i++){
		delete [] gameState[i];
	}
	delete [] gameState;

}

Move AIShell::makeMove(){
	//this part should be filled in by the student to implement the AI
	//Example of a move could be: Move move(1, 2); //this will make a move at col 1, row 2

	if (lastMove.col == -1 && lastMove.row == -1)
	{
		Move m(numCols/2, numRows/2);
		return m;
	}
	
	//this will move to the left-most column possible.
	for (int col = 0; col<numCols; col++){
		for (int row = 0; row<numRows; row++){
			if (gameState[col][row] == NO_PIECE){
				Move m(col, row);
				return m;
			}
		}
	}
	Move m(0, 0);
	return m;
	 
}

void AIShell::makeTree(GameTree<int**>* node){

	generatestates(node);
	if(node->first_child == NULL) //|| depth_level > max || time >= time_limit)
		return;
	GameTree<int **>* child = node->first_child;
	makeTree(child);
	while(child->next_sibling != NULL)
	{
		child = child->next_sibling;
		makeTree(child);
	}



	//start at root node
	//generate its children
	//get first child
	//recurse
	//go to sibling
	//recurse



}

GameTree<int **>* AIShell::generatestates(GameTree<int **>* node){


	//find the first empty slot aka index value = 0
	//place the desired players number into slot 1,-1)
	for (int col = 0; col<numCols; col++){
		for (int row =0; row<numRows; row++)
		{
			if(node->value[col][row] == 0)
			{
				int** copy = copyboard(node->value);
				copy[col][row] = 1;
				GameTree<int **> n = GameTree<int **>(copy);
				node->addChild(n);


			}
		}
	}

}

int ** AIShell::copyboard(int ** board){

	int **copy = NULL;
	copy = new int*[numCols];
	for (int i =0; i<numCols; i++){
		copy[i] = new int[numRows];
	}

	for (int col = 0; col<numCols; col++){
			for (int row =0; row<numRows; row++)
			{
				copy[col][row] = board[col][row];
				}
			}
	return copy;
}
