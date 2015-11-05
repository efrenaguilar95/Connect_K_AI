#include "AIShell.h"
#include <iostream>
#include <vector>



AIShell::AIShell(int numCols, int numRows, bool gravityOn, int** gameState, Move lastMove)
{
	this->deadline=0;
	this->numRows=numRows;
	this->numCols=numCols;
	this->gravityOn=gravityOn;
	this->gameState=gameState;
	this->lastMove=lastMove;
	this->gameTree=new GameTree<int **>;
	this->boardCopy = copyboard(this->gameState);
	this->depth_limit = 3;

	//makeTree(gameTree);
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
	/*
	for (int col = 0; col<numCols; col++){
		for (int row = 0; row<numRows; row++){
			if (gameState[col][row] == NO_PIECE){
				Move m(col, row);
				return m;
			}
		}
	}*/
	AiMove bestMove = getBestMove(boardCopy, 1, 0);
	std::cout<<bestMove.x<<bestMove.y<<std::endl;
	Move m = Move(bestMove.x, bestMove.y);
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

int AIShell::getScore(int col, int row, int player)
{
	//std::cout<<col<<row<<std::endl;
	int val = 0;
	int counter = 0;
	int verticalCount;
	int horizontalCount;
	int lrDiagCount;
	int rlDiagCount;
	if(gravityOn)
		{
			//Check underneath where the piece was just placed
			if(row != 0)
			{
				for (int y = 1; y >= 0; y++)
				{
					if(boardCopy[col][row-y] != player)
						break;
					counter++;
				}
			}
			if(counter == k)
				return 100 * player;

			verticalCount = counter;
			counter = 0;

			//Check if the row has a winner

			//Start by checking left
			if(col != 0)
			{
				for(int x = col-1; x >= 0; x--)
				{
					if(counter == (k-1) || boardCopy[x][row] != player)
						break;
					counter++;
				}
			}
			if(counter == (k-1))
				return 100 * player;
			//Then check right
			if(col != numCols-1)
			{
				for(int x = col+1; x < numCols; x++)
				{
					if(counter == (k-1) || boardCopy[x][row] != player)
						break;
					counter++;
				}
			}
			if(counter == (k-1))
				return 100 * player;
			horizontalCount = counter;
			counter = 0;

			//Check left right diagonal(/)

			//Start by checking bottom left
			if(row != 0 && col != 0)
			{
				int x,y;
				for(x = col-1, y = row-1; x >= 0 && y >= 0; x--, y--)
				{
					if(counter == (k-1) || boardCopy[x][y] != player)
						break;
					counter++;
				}
			}
			if(counter == (k-1))
				return 100 * player;

			//Then check top right
			if(row != (numRows-1) && col != (numCols-1))
			{
				int x,y;
				for(x = col+1, y = row+1; x < numCols && y < numRows; x++, y++)
				{
					if(counter == (k-1) || boardCopy[x][y] != player)
						break;
					counter++;
				}
			}
			lrDiagCount = counter;
			if(counter == (k-1))
				return 100 * player;
			counter = 0;

			//Lastly, check right left diagonal (\)

			//Start by checking bottom right
			if(row != 0 && col != (numCols-1))
			{
				int x,y;
				for(x = col+1, y = row-1; x < numCols && y>=0; x++, y--)
				{
					if(counter == (k-1) || boardCopy[x][y] != player)
						break;
					counter++;
				}
			}
			if(counter == (k-1))
				return 100 * player;

			//Then check top left
			if(row != (numRows-1) && col!= 0)
			{
				int x,y;
				for(x = col-1, y = row+1; x >= 0 && y < numRows; x--, y++)
				{
					if(counter == (k-1) || boardCopy[x][y] != player)
						break;
					counter++;
				}
			}

			rlDiagCount = counter;
			if(counter == (k-1))
				return 100 * player;

			return (verticalCount + horizontalCount + lrDiagCount + rlDiagCount) * player;



		}
}

AiMove AIShell::getBestMove(int** board, int player, int depth, int x, int y) {

    // Base case, check for end state
    if (depth == depth_limit) {
    	AiMove move = AiMove(getScore(x,y,player)); /// getting score of the currentstate
    	std::cout<<move.score;
    	move.x = x;
    	move.y = y;
    	return move;

    }

    std::vector<AiMove> moves;

    // Do the recursive function calls and construct the moves vector
    for (int x = 0; x < numCols; x++) {
        for (int y = 0; y < numRows; y++) {
        	//std::cout<<"Col:"<<x<<std::endl;
        	//std::cout<<"Row:"<<y<<std::endl;
        	//std::cout<<"Val:"<<board[x][y]<<std::endl;
            if (board[x][y] == 0) {
                AiMove move;
                move.x = x;
                move.y = y;
                board[x][y] = player;
                if (player == 1) {
                    move.score = getBestMove(board, -1, depth+1,x,y).score;
                } else {
                    move.score = getBestMove(board, 1, depth+1,x,y).score;
                }
                moves.push_back(move);
                board[x][y] = 0;
            }
        }
    }

    // Pick the best move for the current player
    int bestMove = 0;
    if (player == 1) {
        int bestScore = -1000000;
        for (int i = 0; i < moves.size(); i++) {
            if (moves[i].score > bestScore) {
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    } else {
        int bestScore = 1000000;
        for (int i = 0; i < moves.size(); i++) {
            if (moves[i].score < bestScore) {
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    }
    // Return the best move
    return moves[bestMove];
}
