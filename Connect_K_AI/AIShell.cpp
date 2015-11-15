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
	//this->gameTree=new GameTree<int **>;
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
	std::cout<<"BM: "<<bestMove.x<<bestMove.y<<std::endl;
	Move m = Move(bestMove.x, bestMove.y);
	return m;
	 
}

//void AIShell::makeTree(GameTree<int**>* node){
//
//	generatestates(node);
//	if(node->first_child == NULL) //|| depth_level > max || time >= time_limit)
//		return;
//	GameTree<int **>* child = node->first_child;
//	makeTree(child);
//	while(child->next_sibling != NULL)
//	{
//		child = child->next_sibling;
//		makeTree(child);
//	}
//
//
//
//	//start at root node
//	//generate its children
//	//get first child
//	//recurse
//	//go to sibling
//	//recurse
//
//
//
//}

//GameTree<int **>* AIShell::generatestates(GameTree<int **>* node){
//
//
//	//find the first empty slot aka index value = 0
//	//place the desired players number into slot 1,-1)
//	for (int col = 0; col<numCols; col++){
//		for (int row =0; row<numRows; row++)
//		{
//			if(node->value[col][row] == 0)
//			{
//				int** copy = copyboard(node->value);
//				copy[col][row] = 1;
//				GameTree<int **> n = GameTree<int **>(copy);
//				node->addChild(n);
//
//
//			}
//		}
//	}
//
//}

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
	int playerCount = 0;
	int opponentCount = 0;
	int verticalCount;
	int horizontalCount;
	int lrDiagCount;
	int rlDiagCount;

	bool isPlayerPiece = false;
	if(true)
		{

			//Check underneath where the piece was just placed
			if(row != 0)
			{
				if(boardCopy[col][row-1] != player)
				{
					isPlayerPiece = false;
					opponentCount = getNumAdjBelow(col, row, player*-1);
					counter = opponentCount;
				}
				else
				{
					isPlayerPiece = true;
					playerCount = getNumAdjBelow(col, row, player);
					counter = playerCount;
				}
			}
			if(isPlayerPiece)
			{
				if(playerCount == k)
					return 100 * player;
				else
					verticalCount = playerCount * 2;
			}
			else
			{
				if(opponentCount == k-1)
					return 99*player;
				else
					verticalCount = opponentCount;
			}

			//Then check above
			if(row != numRows-1 && !gravityOn)
			{
				if(boardCopy[col][row-1] != player)
				{
					isPlayerPiece = false;
					opponentCount += getNumAdjAbove(col, row, player*-1);
					counter = opponentCount;
				}
				else
				{
					isPlayerPiece = true;
					playerCount += getNumAdjAbove(col, row, player);
					counter = playerCount;
				}
			}

			if(isPlayerPiece)
			{
				if(playerCount == k)
					return 100 * player;
				else
					verticalCount = (playerCount * 2) + opponentCount;
			}
			else
			{
				if(opponentCount == k-1)
					return 99*player;
				else
					verticalCount = opponentCount + (playerCount *2);
			}
			playerCount = 0;
			opponentCount = 0;
			counter = 0;


			//Check if the row has a winner


			//Start by checking left
			if(col != 0)
			{
				if(boardCopy[col-1][row] != player)
				{
					isPlayerPiece = false;
					opponentCount = getNumAdjLeft(col, row, player*-1);
					counter = opponentCount;
				}
				else
				{
					isPlayerPiece = true;
					playerCount = getNumAdjLeft(col, row, player);
					counter = playerCount;
				}

				}
			}
			if(isPlayerPiece)
			{
				if(playerCount == k)
					return 100 * player;
				else
					horizontalCount = playerCount * 2;
			}
			else
			{
				if(opponentCount == k-1)
					return 99*player;
				else
					horizontalCount = opponentCount;
			}


			//Then check right
			if(col != numCols-1)
			{
				if(boardCopy[col+1][row] != player)
				{
					isPlayerPiece = false;
					opponentCount += getNumAdjRight(col, row, player*-1);
					counter = opponentCount;
				}
				else
				{
					isPlayerPiece = true;
					playerCount += getNumAdjRight(col, row, player);
					counter = playerCount;
				}
			}
			if(isPlayerPiece)
			{
				if(playerCount == k)
					return 100 * player;
				else
					horizontalCount = (playerCount * 2) + opponentCount;
			}
			else
			{
				if(opponentCount == k-1)
					return 99*player;
				else
					horizontalCount = opponentCount + (playerCount *2);
			}

			playerCount = 0;
			opponentCount = 0;
			counter = 0;


			//Check left right diagonal(/)

			//Start by checking bottom left
			if(row != 0 && col != 0)
			{
				if(boardCopy[col-1][row-1] != player)
				{
					isPlayerPiece = false;
					opponentCount = getNumAdjBottomLeft(col, row, player);
					counter = opponentCount;
				}
				else
				{
					isPlayerPiece = true;
					playerCount = getNumAdjBottomLeft(col, row, player);
					counter = playerCount;
				}
			}
			if(isPlayerPiece)
			{
				if(playerCount == k)
					return 100 * player;
				else
					lrDiagCount = playerCount * 2;
			}
			else
			{
				if(opponentCount == k-1)
					return 99*player;
				else
					lrDiagCount = opponentCount;
			}

			//Then check top right
			if(row != (numRows-1) && col != (numCols-1))
			{
				if(boardCopy[col+1][row+1] != player)
				{
					isPlayerPiece = false;
					opponentCount += getNumAdjTopRight(col, row, player);
					counter = opponentCount;
				}
				else
				{
					isPlayerPiece = true;
					playerCount += getNumAdjTopRight(col, row, player);
					counter = playerCount;
				}
			}
			lrDiagCount = counter;
			if(isPlayerPiece)
			{
				if(playerCount == k)
					return 100 * player;
				else
					verticalCount = (playerCount * 2) + opponentCount;
			}
			else
			{
				if(opponentCount == k-1)
					return 99 * player;
				else
					verticalCount = opponentCount + (playerCount *2);
			}

			playerCount = 0;
			opponentCount = 0;
			counter = 0;

			//Lastly, check right left diagonal (\)

			//Start by checking bottom right
			if(row != 0 && col != (numCols-1))
			{
				if(boardCopy[col+1][row-1] != player)
				{
					isPlayerPiece = false;
					opponentCount = getNumAdjBottomRight(col, row, player);
					counter = opponentCount;
				}
				else
				{
					isPlayerPiece = true;
					playerCount = getNumAdjBottomRight(col, row, player);
					counter = playerCount;
				}
			}
			if(isPlayerPiece)
			{
				if(playerCount == k)
					return 100 * player;
				else
					rlDiagCount = playerCount * 2;
			}
			else
			{
				if(opponentCount == k-1)
					return 99 * player;
				else
					rlDiagCount = opponentCount;
			}

			//Then check top left
			if(row != (numRows-1) && col!= 0)
			{
				if(boardCopy[col-1][row+1] != player)
				{
					isPlayerPiece = false;
					opponentCount += getNumAdjTopLeft(col, row, player);
					counter = opponentCount;
				}
				else
				{
					isPlayerPiece = true;
					playerCount += getNumAdjTopLeft(col, row, player);
					counter = opponentCount;
				}

			}

			if(isPlayerPiece)
			{
				if(playerCount == k)
					return 100 * player;
				else
					verticalCount = (playerCount * 2) + opponentCount;
			}
			else
			{
				if(opponentCount == k-1)
					return 99*player;
				else
					verticalCount = opponentCount + (playerCount *2);
			}

			playerCount = 0;
			opponentCount = 0;
			counter = 0;


//			std::cout << "VerticalC: " << verticalCount << std::endl;
//			std::cout << "HorizontalC: " << horizontalCount << std::endl;
//			std::cout << "lrDiagCount: " << lrDiagCount <<std::endl;
//			std::cout << "rlDiagCount: " << rlDiagCount <<std::endl;


			return (verticalCount + horizontalCount + lrDiagCount + rlDiagCount) * player;



}

AiMove AIShell::getBestMove(int** board, int player, int depth, int col, int row) {

    // Base case, check for end state
    if (depth == depth_limit) {
    	AiMove move = AiMove(getScore(col,row,player*-1)); /// getting score of the currentstate
    	//std::cout<<move.score;
    	//if (move.score == 2){std::cout<<"got 2!!!!" << std::endl;}
    	move.x = col;
    	move.y = row;
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
            	//std::cout << "player is " << player << " depth: " << depth <<std::endl;
                //std::cout<<"For move at: "<<x<<y<<std::endl;
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
                //for (int i=0; i < moves.size(); i++){
                	//std::cout << i << ": " << moves[i].score << std::endl;
                //}
                board[x][y] = 0;
                //break;
            }
        }
    }

    // Pick the best move for the current player
    //for (int i =0; i < moves.size();i++)
    //{
    	//std::cout<< "m: " << moves[i].score<< std::endl;
    //}


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
            	//std::cout<< "m: " <<moves[i].score<< std::endl;
                bestMove = i;
                bestScore = moves[i].score;
            }
        }
    }
    // Return the best move
    return moves[bestMove];
}


//Returns the number of adjacent pieces equal to the player below the player
int AIShell::getNumAdjBelow(int col, int row, int player)
{
	int counter = 0;
	if (row != 0)
	{
		for (int y = row-1; y>=0; y--)
		{
			if(counter == (k-1) || boardCopy[col][y] != player)
				break;
			counter++;
		}
	}
	return counter;

}

//Returns the number of adjacent vertical pieces equal to the player above the player
int AIShell::getNumAdjAbove(int col, int row, int player)
{
	int counter = 0;
	if(row != numRows-1)
	{
		for(int y = row-1; y<= numRows; y++)
		{
			if(counter == (k-1) || boardCopy[col][y] != player)
				break;
			counter++;
		}
	}
	return counter;
}

//Returns the number of adjacent horizontal pieces equal to the player to the left of the player
int AIShell::getNumAdjLeft(int col, int row, int player)
{
	int counter = 0;
	if(col != 0)
	{
		for(int x = col-1; x >= 0; x--)
		{
			if(counter == (k-1) || boardCopy[x][row] != player)
				break;
			counter++;
		}
	}
	return counter;
}

//Returns the number of adjacent horizontal pieces equal to the player to the right of the player
int AIShell::getNumAdjRight(int col, int row, int player)
{
	int counter = 0;
	if(col != numCols-1)
	{
		for(int x = col+1; x < numCols; x++)
		{
			if(counter == (k-1) || boardCopy[x][row] != player)
				break;
			counter++;
		}
	}
	return counter;
}

//Returns the number of adjacent diagonal pieces equal to the player to the bottom right diagonal of the player
int AIShell::getNumAdjBottomLeft(int col, int row, int player)
{
	int counter = 0;
	if(row != 0 && col != 0)
	{
		int x, y;
		for(x = col-1, y = row-1; x >= 0 && y >= 0; x--, y--)
		{
			if(counter == (k-1) || boardCopy[x][y] != player)
				break;
			counter++;
		}
	}

	return counter;
}

//Returns the number of adjacent diagonal pieces equal to the player to the top right diagonal of the player
int AIShell::getNumAdjTopRight(int col, int row, int player)
{
	int counter = 0;
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
	return counter;
}

//Returns the number of adjacent diagonal pieces to the player to the bottom right diagonal of the player
int AIShell::getNumAdjBottomRight(int col, int row, int player)
{
	int counter;
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

	return counter;
}

int AIShell::getNumAdjTopLeft(int col, int row, int player)
{
	int counter;
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

	return counter;
}
