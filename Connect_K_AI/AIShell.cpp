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
	this->boardCopy = copyboard(this->gameState);
	if(gravityOn)
		this->depth_limit = 6;
	else
		this->depth_limit = 4;
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
	
	AiMove bestMove = getBestMove(boardCopy, 1, 0, -1);
	//std::cout<<"BM: "<<bestMove.x<<bestMove.y<<std::endl;
	Move m = Move(bestMove.x, bestMove.y);
	return m;
	 
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
	int verticalScore;
	int horizontalScore;
	int lrDiagScore;
	int rlDiagScore;
	int totalScore = 500;

	int threatCount = 0;

	//std::cout<<col<<row<<std::endl;
	//Check if the column has a winner
	verticalScore = getVerticalScore(col, row, player);
	//std::cout<<"VerticalScore:"<<verticalScore<<std::endl;
	if(verticalScore == 1000 || verticalScore == -1000)
		return verticalScore;
	if(verticalScore == 999 || verticalScore == -999)
		threatCount += 1;

	//Check if the row has a winner
	horizontalScore = getHorizontalScore(col, row, player);
	//std::cout<<"HorizontalScore:"<<horizontalScore<<std::endl;
	if(horizontalScore == 1000 || horizontalScore == -1000)
		return horizontalScore;
	if(horizontalScore == 999 || horizontalScore == -999)
		threatCount += 1;

	//Check left right diagonal(/)
	lrDiagScore = getLRDiagonalScore(col, row, player);
	//std::cout<<"lrDiagScore:"<<lrDiagScore<<std::endl;
	if(lrDiagScore == 1000 || lrDiagScore == -1000)
		return lrDiagScore;
	if(lrDiagScore == 999 || lrDiagScore == -999)
		threatCount += 1;

	//Lastly, check right left diagonal (\)
	rlDiagScore = getRLDiagonalScore(col, row, player);
	//std::cout<<"rlDiagScore:"<<rlDiagScore<<std::endl;
	if(rlDiagScore == 1000 || rlDiagScore == -1000)
	{
		return rlDiagScore;
	}
	if(rlDiagScore == 999 || rlDiagScore == -999)
		threatCount += 1;

	if(threatCount != 0)
	{
		//std::cout<<threatCount<<std::endl;
		if(player == AI_PIECE)
			return 995 + threatCount;
		else
			return (-995) - threatCount;
	}

	totalScore = totalScore + verticalScore + horizontalScore + lrDiagScore + rlDiagScore;
	//std::cout<<"Total Score:"<<totalScore<<std::endl;
	return totalScore;
}



AiMove AIShell::getBestMove(int** board, int player, int depth, int col, int row) {

    // Base case, check for end state
	int score = 0;
	if(col != -1)
	{
		score = getScore(col, row, player *	-1); // getting score of the current state
	}
    if (depth == depth_limit || isFull(board) || (score <= -996) || (score >= 996))	//if depth or terminal node has been reached
    {


    	AiMove move = AiMove(score);
    	//std::cout<<move.score<<std::endl;
    	//if (move.score == 2){std::cout<<"got 2!!!!" << std::endl;}
    	move.x = col;
    	move.y = row;
    	move.level = depth;

    	if(player == AI_PIECE)
    	{
    		//std::cout<<"Node value for AI move at "<<col<< ", " <<row<<": "<<score<<std::endl;
    	}
    	else
    	{
    		//std::cout<<"Node value for Opponent move at " <<col<< ", "<<row<<": "<<score<<std::endl;
     	}
    	//if(score <= -996 || score >= 996)
    		//std::cout<<score<<std::endl;
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
                    move = getBestMove(board, -1, depth+1,x,y);
                } else {
                    move = getBestMove(board, 1, depth+1,x,y);
                }
                moves.push_back(move);
                //for (int i=0; i < moves.size(); i++){
                	//std::cout << i << ": " << moves[i].score << std::endl;
                //}
                board[x][y] = 0;
                if(gravityOn)
                	break;
            }
        }
    }

    // Pick the best move for the current player
    //for (int i =0; i < moves.size();i++)
    //{
    	//std::cout<< "m: " << moves[i].score<< std::endl;
    //}


    int bestMove = 0;
    int lowestDepth = 999999999;
   // std::cout<<"Prints start here"<<std::endl;
    if (player == 1) {
        int bestScore = -1000000;
        for (int i = 0; i < moves.size(); i++) {
        	//std::cout<<moves[i].x<<" "<<moves[i].y<<" "<<moves[i].score<<" "<<moves[i].level<<std::endl;
            if (moves[i].score > bestScore && moves[i].level <= lowestDepth) {
                bestMove = i;
                bestScore = moves[i].score;
                lowestDepth = moves[i].level;
                //if(lowestDepth == 2)
                	//std::cout<<lowestDepth<<std::endl;
            }
        }
    } else {
        int bestScore = 1000000;
        for (int i = 0; i < moves.size(); i++) {
        	//std::cout<<moves[i].x<<" "<<moves[i].y<<" "<<moves[i].score<<" "<<moves[i].level<<std::endl;
            if (moves[i].score < bestScore && moves[i].level <= lowestDepth) {
            	//std::cout<< "m: " <<moves[i].score<< std::endl;
                bestMove = i;
                bestScore = moves[i].score;
                lowestDepth = moves[i].level;
                //if(lowestDepth == 2)
                	//std::cout<<lowestDepth<<std::endl;
            }
        }
    }
    // Return the best move
    //std::cout<<"Prints end here"<<std::endl;
    return moves[bestMove];
}


//Returns the number of adjacent pieces equal to the player below the player
int AIShell::getNumAdjBelow(int col, int row, int player)
{
	int counter = 0;
	//std::cout<<player;
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


//WARNING: Only to be used if gravity is on, otherwise use winPossibleVertical
bool AIShell::winPossibleBelow(int col, int row, int player)
{

	int counter = 1;
	for(int y = row-1; y>=0; y--)
	{
		if(boardCopy[col][y] == (player*-1))
			break;
		counter++;
		if(counter == k)
			return true;
	}
	for(int y = row+1; y < numRows; y++)
	{
		if(boardCopy[col][y] != 0)
			break;
		counter++;
		if(counter == k)
			return true;
	}
	return false;
}


//Returns the number of adjacent vertical pieces equal to the player above the player
int AIShell::getNumAdjAbove(int col, int row, int player)
{
	int counter = 0;
	if(row != numRows-1)
	{
		for(int y = row+1; y< numRows; y++)
		{
			if(counter == (k-1) || boardCopy[col][y] != player)
				break;
			counter++;
		}
	}
	return counter;
}

bool AIShell::verticalWinPossible(int col, int row, int player)
{
	//check how many pieces are above you, adding current position to that count
	//see how many spaces are below you that lead to a win
	//if these added together lead to k, a win is possible
	int counter = 1;
	for(int y = row-1; y>=0; y--)
	{
		if(boardCopy[col][y] == (player*-1))
			break;
		counter++;
		if(counter == k)
			return true;
	}
	for(int y = row+1; y < numRows; y++)
	{
		if(boardCopy[col][y] == (player*-1))
			break;
		counter++;
		if(counter == k)
			return true;
	}
	return false;
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
	//std::cout<<"num left for "<< col << " " << row<<" "<<counter<<std::endl;
	return counter;
}

bool AIShell::horizontalWinPossible(int col, int row, int player)
{
	int counter = 1;
	for(int x = col-1; x >= 0; x--)
	{
		if(boardCopy[x][row] == (player*-1))
			break;
		counter++;
		if(counter == k)
			return true;
	}
	for(int x = col+1; x<numCols; x++)
	{
		if(boardCopy[x][row] == (player*-1))
			break;
		counter++;
		if(counter == k)
			return true;
	}
	return false;
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

//Returns the number of adjacent diagonal pieces equal to the player to the bottom left diagonal of the player
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
	int counter = 0;
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
	int counter = 0;
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

int AIShell::getVerticalScore(int col, int row, int player)
{
	//If there is no possibility of winning for either player, return
	//If there is a possibility to win, then we add weights to pieces
	//If pieces on both sides are different playets. ONLY if different players
	//THEN we use what we know about win possibility to weight side
	//ex a win is possible for opponent, but we have a piece on the left
	//so the right side can lead to an opponent win
	bool canWin;
	bool canOpponentWin;
	if(gravityOn)
	{
		canWin = winPossibleBelow(col, row, player);
		canOpponentWin = winPossibleBelow(col, row, player*-1);
		int bottomPiece = -7;
		int bottomCount;
		int bottomScore = 0;
		if(canWin == false && canOpponentWin == false)
				return 0;
		if(canWin)
		{
			bottomPiece = player;
			bottomCount = getNumAdjBelow(col, row, bottomPiece);
			if(bottomCount >= k-1)
			{
				if(player == AI_PIECE)
					return 1000;
				else
					return -1000;
			}
			if(bottomCount > k/2)
				return (1 + bottomCount) * 1.5 * player;
			else
				return (1 + bottomCount) * player;
		}
		if(canOpponentWin)
		{
			bottomPiece = player*-1;
			bottomCount = getNumAdjBelow(col, row, bottomPiece);
			if(bottomCount >= k-1)
			{
				if(player == AI_PIECE)
					return 999;
				else
					return -999;
			}
			if(bottomCount > k/2)
				return bottomCount * 2 * (player*-1) * -1;
			else
				return bottomCount * (player*-1);
		}

	}
	else
	{
		canWin = verticalWinPossible(col, row, player);
		canOpponentWin = verticalWinPossible(col, row, player);
		if(canWin == false && canOpponentWin == false)
			return 0;
		int bottomPiece = -7;
		int topPiece = -7;
		int bottomCount = 0;
		int bottomScore = 0;
		int topCount = 0;
		int topScore = 0;
		if(row != 0)
			bottomPiece = boardCopy[col][row-1];
		if(row != numRows-1)
			topPiece = boardCopy[col][row+1];
		if(canWin && (topPiece == player*-1 || row == numRows-1))	//the player can win but only from bottom pieces
		{
			if(bottomPiece == 0)
			{
				bottomScore =  1 * player;
			}
			else
			{
				bottomCount = getNumAdjBelow(col, row, bottomPiece);
				if(bottomCount >= k-1)
				{
					if(player == AI_PIECE)
						return 1000;
					else
						return -1000;
				}
				if(bottomCount > k/2)
					bottomScore = bottomCount * 1.5 * player;
				else
					bottomScore = bottomCount * player;
			}
			canWin = false;
		}
		if(canWin && (bottomPiece == player*-1 || row == 0))	//the player can win but only from top pieces
		{
			if(topPiece == 0)
			{
				topScore = 1 * player;
			}
			else
			{
				topCount = getNumAdjAbove(col, row, topPiece);
				if(topCount >= k-1)
				{
					if(player == AI_PIECE)
						return 1000;
					else
						return -1000;
				}
				if(topCount > k/2)
					topScore = topCount * 1.5 * player;
				else
					topScore = topCount * player;
			}
			canWin = false;
		}

		if(canWin)
		{
			if((topPiece == 0 || topPiece == -7) && (topPiece == 0 || topPiece == -7))
			{
				return 1 * player;		//possible to win because it is surrounded by blanks
			}
			if(topPiece != 0)
				topCount = getNumAdjAbove(col, row, topPiece);
			if(bottomPiece != 0)
				bottomCount = getNumAdjBelow(col, row, bottomPiece);
			if((topCount + bottomCount) >= k-1)
			{
				if(player == AI_PIECE)
					return 1000;
				else
					return -1000;
			}
			if(topCount + bottomCount > k/2)
				return (topCount + bottomCount) * 1.5 * player;
			else
				return (topCount + bottomCount) * player;
		}

		if(canOpponentWin && (topPiece == player || row == numRows-1))	//the opponent can win but only from bottom pieces
		{
			if(bottomPiece == 0)
			{
				bottomScore =  1 * player;
			}
			else
			{
				bottomCount = getNumAdjBelow(col, row, bottomPiece);
				if(bottomCount >= k-1)
				{
					if(player == AI_PIECE)
						return 999;
					else
						return -999;
				}
				if(bottomCount+1 > k/2)
					bottomScore = bottomCount * 2 * (player*-1) * -1;
				else
					bottomScore = bottomCount * (player*-1);
			}
			canOpponentWin = false;
		}

		if(canOpponentWin && (bottomPiece == player || row == 0))	//the opponent can win but only from top pieces
		{
			if(topPiece == 0)
			{
				topScore = 1 * player;
			}
			else
			{
				topCount = getNumAdjAbove(col, row, topPiece);
				if(topCount >= k-1)
				{
					if(player == AI_PIECE)
						return 999;
					else
						return -999;
				}
				if(topCount+1 > k/2)
					topScore = topCount * 2 * (player*-1) * -1;
				else
					topScore = topCount * (player*-1) *-1;
			}
			canOpponentWin = false;
		}

		if(canOpponentWin)
		{
			if((topPiece == 0 || topPiece == -7) && (topPiece == 0 || topPiece == -7))
			{
				return 1 * player;		//possible to win because it is surrounded by blanks
			}
			if(topPiece != 0)
				topCount = getNumAdjAbove(col, row, topPiece);
			if(bottomPiece != 0)
				bottomCount = getNumAdjBelow(col, row, bottomPiece);
			if((topCount + bottomCount) >= k-1)
			{
				if(player == AI_PIECE)
					return 999;
				else
					return -999;
			}
			if(topCount + bottomCount+1 > k/2)
				return (topCount + bottomCount) * 2 * (player*-1) * -1;
			else
				return (topCount + bottomCount) * (player*-1);
		}
		return (topScore + bottomScore);
	}
}

int AIShell::getHorizontalScore(int col, int row, int player)
{

	//Need to rewrite a lot
	//If there is no possibility of winning for either player, return
	//If there is a possibility to win, then we add weights to pieces
	//If pieces on both sides are different players. ONLY if different players
	//THEN we use what we know about win possibility to weight side
	//ex a win is possible for opponent, but we have a piece on the left
	//so the right side can lead to an opponent win

	bool canWin = horizontalWinPossible(col, row, player);
	bool canOpponentWin = horizontalWinPossible(col, row, player*-1);

	if(canWin == false && canOpponentWin == false)
		return 0;

	int leftPiece = -7;
	int rightPiece = -7;
	int rightCount = 0;
	int rightScore = 0;
	int leftCount = 0;
	int leftScore = 0;
	int totalScore = 0;
	if(col != 0)
		leftPiece = boardCopy[col-1][row];
	if(col != numCols-1)
		rightPiece = boardCopy[col+1][row];
	if(canWin && (leftPiece == player*-1 || col == 0))	//the player can win, but only on the right side
	{
		if(rightPiece == 0)	//There are only blanks to the right, but it is possible to win
		{
			rightScore = 1 * player;
		}
		else
		{
			rightCount = getNumAdjRight(col, row, rightPiece);
			if(rightCount >= k-1)	//The player will win if he puts piece here
			{
				if(player == AI_PIECE)
					return 1000;
				else
					return -1000;
			}
			if(rightCount > k/2)
				rightScore = rightCount * 1.5 * player;
			else
				rightScore = rightCount * player;

		}
		canWin = false;
	}
	if(canWin && (rightPiece == player*-1 || col == numCols-1))	//the player can win, but only on the left side
	{
		if(leftPiece == 0)
			leftScore = 1 * player;	//There are only blanks to the left, but it is possible to win
		else
		{
			leftCount = getNumAdjLeft(col, row, leftPiece);
			if(leftCount >= k-1)	//The player will win if he puts piece here
			{
				if(player == AI_PIECE)
					return 1000;
				else
					return -1000;
			}
			if(leftCount > k/2)
				leftScore = leftCount * 1.5 * player;
			else
				leftScore = leftCount * player;
		}
		canWin = false;

	}
	if(canWin)
	{
		if((leftPiece == 0 || leftPiece == -7) && (rightPiece == 0 || rightPiece == -7))
		{
			totalScore = 1 * player;		//possible to win because it is surrounded by blanks
			return totalScore;
		}
		if(leftPiece != 0)
			leftCount = getNumAdjLeft(col,row,leftPiece);
		if(rightPiece != 0)
			rightCount = getNumAdjRight(col,row,rightPiece);
		if((leftCount+rightCount)>= k-1)	//The player will win if he puts piece here
		{
			if(player == AI_PIECE)
				return 1000;
			else
				return -1000;
		}
		if((leftCount+rightCount) > k/2)
			return (leftCount+rightCount) * 1.5 * player;
		else
			return (leftCount+rightCount) * player;
	}

	if(canOpponentWin && (leftPiece == player || col == 0))	//The opponent can win, but only on the right side
	{
		if(rightPiece == 0)
			rightScore = 1 * player;
		else
		{
			rightCount = getNumAdjRight(col, row, rightPiece);
			if(rightCount >= k-1)
			{
				if(player == AI_PIECE)
					return 999;
				else
					return -999;
			}
			if(rightCount > k/2)
				rightScore = rightCount * 2 * (player*-1) * -1;
			else
				rightScore = rightCount * (player*-1);
		}
		canOpponentWin = false;
	}

	if(canOpponentWin && (rightPiece == (player) || col == numCols-1))	//The opponent can win, but only on the left side
	{
		if(leftPiece == 0)
			leftScore = 1 * player;
		else
		{
			leftCount = getNumAdjLeft(col, row, leftPiece);
			if(leftCount >= k-1)
			{
				if(player == AI_PIECE)
					return 999;
				else
					return -999;
			}
			if(leftCount > k/2)
				leftScore = leftCount * 2 * (player*-1) * -1;
			else
				leftScore = leftCount * (player*-1);
		}
		canOpponentWin = false;
	}
	if(canOpponentWin)
	{
		if((leftPiece == 0 || leftPiece == -7) && (rightPiece == 0 || rightPiece == -7))
		{
			totalScore = 1 * player;		//possible to win because it is surrounded by blanks
			return totalScore;
		}
		if(leftPiece != 0)
			leftCount = getNumAdjLeft(col,row,leftPiece);
		if(rightPiece != 0)
			rightCount = getNumAdjRight(col,row,rightPiece);
		if((leftCount+rightCount)>= k-1)	//The opponent will win if he puts piece here
		{
			if(player == AI_PIECE)
				return 999;
			else
				return -999;
		}
		if((leftCount+rightCount) > k/2)
			return (leftCount+rightCount) * 2 * (player*-1) * -1;
		else
		{
			return (leftCount+rightCount) * (player*-1);
		}

	}
	return (leftScore + rightScore);
}

//Check left right diagonal(/)
int AIShell::getLRDiagonalScore(int col, int row, int player)
{
	int leftPiece = player;
	int rightPiece = player;

	int leftCount = 0;
	int rightCount = 0;

	//start by checking bottom left
	if(row != 0 && col != 0)
	{
		if(boardCopy[row-1][col-1] != player)
			leftPiece *= -1;
		leftCount = getNumAdjBottomLeft(col, row, leftPiece);
	}

	if(leftCount >= k-1)
		{
			if(leftPiece == AI_PIECE)
			{
				if(player == AI_PIECE)
					return 1000;
				else
					return -999;
			}
			else
			{
				if(player == AI_PIECE)
					return 999;
				else
					return -1000;
			}
		}

	//Then check top right
	if(row != (numRows-1) && col != (numCols-1))
	{
		if(boardCopy[col+1][row+1] != player)
			rightPiece *= -1;
		rightCount = getNumAdjTopRight(col, row, rightPiece);
	}

	if(rightCount >= k-1)
		{
			if(rightPiece == AI_PIECE)
			{
				if(player == AI_PIECE)
					return 1000;
				else
					return -999;
			}
			else
			{
				if(player == AI_PIECE)
					return 999;
				else
					return -1000;
			}
		}


	int leftScore = 0;
	int rightScore = 0;

	if(rightCount >= k/2)
	{
		if(rightPiece == player)
			rightScore = rightCount * 1.5;
		else
			rightScore = rightCount * 2 * -1;
	}
	else
		rightScore = rightCount;

	if(leftCount >= k/2)
	{
		if(leftPiece == player)
			leftScore =  leftCount * 1.5;
		else
			leftScore = leftCount * 2 * -1;
	}
	else
		leftScore = leftCount;


	if(rightPiece == leftPiece)
	{
		if((leftCount + rightCount) >= k-1)
		{
			if(leftPiece == AI_PIECE)
			{
				if(player == AI_PIECE)
					return 1000;
				else
					return -999;
			}
			else
			{
				if(player == AI_PIECE)
					return 999;
				else
					return -1000;
			}

		}
		return ((rightScore + leftScore) * rightPiece);
	}

	if(rightPiece == AI_PIECE)
		return (rightScore - leftScore);
	else
		return (leftScore - rightScore);

}

//Check right left diagonal (\)
int AIShell::getRLDiagonalScore(int col, int row, int player)
{
	int leftPiece = player;
	int rightPiece = player;

	int leftCount = 0;
	int rightCount = 0;


	//Start by checking bottom right
	if(row != 0 && col != (numCols-1))
	{
		if(boardCopy[row-1][col+1] != player)
			rightPiece *= -1;
		rightCount = getNumAdjBottomRight(col, row, rightPiece);
	}

	if(rightCount >= k-1)
	{
		if(rightPiece == AI_PIECE)
		{
			if(player == AI_PIECE)
				return 1000;
			else
				return -999;
		}
		else
		{
			if(player == AI_PIECE)
				return 999;
			else
				return -1000;
		}
	}

	//Then check top left
	if(row != (numRows-1) && col!= 0)
	{
		if(boardCopy[row+1][col-1] != player)
			leftPiece *= -1;
		leftCount = getNumAdjTopLeft(col, row, leftPiece);
	}


	if(leftCount >= k-1)
	{
		if(leftPiece == AI_PIECE)
		{
			if(player == AI_PIECE)
				return 1000;
			else
				return -999;
		}
		else
		{
			if(player == AI_PIECE)
				return 999;
			else
				return -1000;
		}
	}

	int leftScore = 0;
	int rightScore = 0;

	if(rightCount >= k/2)
	{
		if(rightPiece == player)
			rightScore = rightCount * 1.5;
		else
			rightScore = rightCount * 2 * -1;
	}
	else
		rightScore = rightCount;

	if(leftCount >= k/2)
	{
		if(leftPiece == player)
			leftScore = leftCount * 1.5;
		else
			leftScore = leftCount * 2 * -1;
	}
	else
		leftScore = leftCount;

	if(rightPiece == leftPiece)
	{
		if((leftCount + rightCount) >= k-1)
		{
			if(leftPiece == AI_PIECE)
			{
				if(player == AI_PIECE)
					return 1000;
				else
					return -999;
			}
			else
			{
				if(player == AI_PIECE)
					return 999;
				else
					return -1000;
			}

		}
		return ((rightScore + leftScore) * rightPiece);
	}
	if(rightPiece == AI_PIECE)
		return (rightScore  - leftScore);
	else
		return (leftScore - rightScore);


}

//Returns true if a board is full
bool AIShell::isFull(int** board)
{
	for(int row = 0; row < numRows; row++)
	{
		for(int col = 0; col < numCols; col++)
		{
			if(board[col][row] == 0)
				return false;
		}
	}
	return true;
}



