#include "Board.h"

//-----------------------------------------------------------------
//							constructor
//-----------------------------------------------------------------

/*
 *  Board constructor.
*/
Board::Board(const Point & p):boardStartPos(p)
{
	resetBoard();
}

Board::Board(ifstream& in)
{
	in.read((char*)this, sizeof(*this));
}

//-----------------------------------------------------------------
//			   		  Board Public function
//-----------------------------------------------------------------

//----------------------Gets functions---------------------

/*
  This function return the start position point of the board.
*/
const Point& Board::getBoardStartPos()const
{
	return boardStartPos;
}

/*
  This function receive x and y cordinate of specific square on 
  and return the sign in this location on board.
*/
char Board::getSignInBoard(const int &xCord, const int &yCord) const
{
	return signsBoard[yCord][xCord];
}

/*
   This function receive xCordinate (that represent coordinate on screen)
   and return the comparable x cordinate of the board (in other words 
   convert to parallel x.
*/
int Board::getComparableXcorOfBoard(const int &xCord) const
{
	return (xCord - boardStartPos.getX()) % Board::WIDTH;
}

/* 
   This function receive y Cordinate (that represent coordinate on screen)
   and return the comparable y cordinate of the board (in other words 
   convert to parallel y.
   */
int Board::getComparableYcorOfBoard(const int &yCord) const
{
	return (yCord - boardStartPos.getY()) % Board::LENGTH;
}

//----------------------Checking functions---------------------

/* 
 This function check if the recive line is full.
 */
bool Board::isLineFull(const int& line) const
{
	return (numOfFullSquareInLine[line] == WIDTH ? true : false);
}

/*
   This function check if the recive line is empty.
*/
bool Board::isLineEmpty(const int& line) const
{
	return (numOfFullSquareInLine[line] == 0 ? true : false);
}

/*
   This function check if the square in the given x and y coordinate
   is empty.
*/
bool Board::isSquareEmpty(const int &xCor, const int &yCor) const
{
	return(signsBoard[yCor][xCor] == ' ' ? true : false);
}

/* 
  The function checks if there is an obstacle in the given coordinate on the board - 
  the given coordinates must be in the board limits.
*/
bool Board::isThereObstacleAt(const int &xCord, const int &yCord)const
{
	//If the square in the given coordinate is not empty it means that there is obstacle
	//at this square so we return true
	return (!isSquareEmpty(xCord, yCord) == true) ? true : false;
}

/*
   This function check if the location in the given x and y cordinate 
   is within board boundaries.
*/
bool Board::withinBoundaries(const int &xCord, const int &yCord)const
{
	return (((yCord >= 0 && yCord < Board::LENGTH) && 
		     (xCord < Board::WIDTH && xCord >= 0)) == true? true : false);
}

/*
   This function check if at the given x & y coordinate there is something
   or this is not within boundaries.
*/
bool Board::notWithinBoundariesOrThereIsSomethingAt(const int &xCord, const int &yCord)const
{
	return !withinBoundaries(xCord, yCord) || !isSquareEmpty(xCord, yCord);
}


//----------------------Fill & clear square functions---------------------

/* 
   This function receive x and y cordinate and clear the sign in board in
   this location on board.
*/
bool Board::clearSign(const int &xCord, const int &yCord)
{
	//Check if the given coordinates in the borders of the board
	if (withinBoundaries(xCord, yCord))
	{
		//If the square was empty here we do not need to clear anythig
		if (!isSquareEmpty(xCord, yCord))
		{
			signsBoard[yCord][xCord] = ' ';//Clear sign

			//Print after the update
			gotoxy(boardStartPos.getX() + xCord, boardStartPos.getY() + yCord);
			cout << signsBoard[yCord][xCord];

			numOfFullSquareInLine[yCord]--;//update number Of full square in line
			return true; //the sign was clear successfully
		}
	}
	return false;//the sign was not clear successfully because it is not in board limit
}

/*
  This function receive x and y cordinate and fill the given sign in board in
  this location on board.
*/
void Board::fillSign(const char &sign, const int &xCord, const int &yCord)
{
	//Check if the given coordinates in the borders of the board
	if (withinBoundaries(xCord, yCord))
	{
		signsBoard[yCord][xCord] = sign;//Fill sign

		//Print after the update
		gotoxy(boardStartPos.getX() + xCord, boardStartPos.getY() + yCord);
		cout << signsBoard[yCord][xCord];

		numOfFullSquareInLine[yCord]++;//update number Of full square in line
	}

}


//----------------------------Board update functions--------------------------

/* 
   This function move down blocks starting from the given line.
   The function return the number of times we clear (move down on) full line 
   (line that was full of signs).
*/
void Board::moveForwardBlocks(const int &line) 
{
	int currentLineIndex = line -1;

	while (currentLineIndex >= 0 )//Loop for move forward the rest lines
	{
		moveDownOneLine(currentLineIndex);
		currentLineIndex--;
		
	}//end of while
}


//------------------------Other Function---------------------------------

/*
   This function draw the frame of the board and the content of the board
   (the location is start position of the board).
*/
void Board::draw() const
{
	//initialization x and y matching to board start position
	int x = boardStartPos.getX() -1;
	int y = boardStartPos.getY() -1;

	//Loop for printing frame:
	for (int i = 0; i < Board::LENGTH + 2; i++)
	{
		for (int j = 0; j < Board::WIDTH + 2; j++)
		{
			gotoxy(x + j, y + i);
			if ((i == 0 || i == Board::LENGTH + 1) || (j == 0 || j == Board::WIDTH + 1))
				cout << Board::SIGN;
			else
				cout << signsBoard[i-1][j-1];
		}
		cout << endl;
	}
}

/*
   This function reset sign board to initial state.
*/
void Board::resetBoard()
{
	for (int i = 0; i < Board::LENGTH; i++)//Loop for initialize signBoard
	{
		for (int j = 0; j < Board::WIDTH; j++)
			signsBoard[i][j] = ' ';
	}
	//Now reset the number of full square in line array respectively
	resetNumOfFullSquareInLineArray();
}

/*
   This function save the data of the board.
*/
void Board::save(ofstream &out) const
{
	out.write((const char*)this, sizeof(*this));
}

//-----------------------------------------------------------------
//			   		  Board Private function
//-----------------------------------------------------------------

/* 
   This function receive index of line of the board and move the line
   Down (this line will run over the line that was there).
*/
void Board::moveDownOneLine(const int &lineIndex)
{
	for (int xCord = 0; xCord < Board::WIDTH; xCord++)//Loop for move down the line
	{
		signsBoard[lineIndex + 1][xCord] = signsBoard[lineIndex][xCord];//Move down square

		//Print the changes:
		gotoxy(boardStartPos.getX() + xCord, boardStartPos.getY() + lineIndex + 1);
		cout << signsBoard[lineIndex + 1][xCord];
	}

	//Update the number Of full square in line array in accordance to changes
	numOfFullSquareInLine[lineIndex + 1] = numOfFullSquareInLine[lineIndex];
}

/*
  This function reset the number of full square array.
*/
void Board::resetNumOfFullSquareInLineArray()
{
	for (int i = 0; i < LENGTH; i++)
		numOfFullSquareInLine[i] = 0;
}