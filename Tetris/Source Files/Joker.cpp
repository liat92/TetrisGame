#include "Joker.h"

//-----------------------------------------------------------------
//                          constructor
//-----------------------------------------------------------------

/*
  Joker constructor.
*/
Joker::Joker(int xCord, int yCord) : Block(xCord, yCord, Block::SPECIAL_BLOCK, this->SIGN){}

//-----------------------------------------------------------------
//                    Joker Public functions 
//----------------------------------------------------------------

/*
  This function move joker (we can see when it move through blocks).
  Note : The joker recognize the board because it needs to know if it
  steps on a block that is already exists or not.
*/
void Joker::move(Point::eKeys direction,const Board &theBoard)
{
	//Check if there is not any obstacle and 
	//after movement the block is within the bounderies  

	int currentX = theBoard.getComparableXcorOfBoard(body[0].getX());
	int currentY = theBoard.getComparableYcorOfBoard(body[0].getY());
	int addToX , addToY;
		
	addToXAndYAccordingToOneStep(direction, addToX, addToY);
		
	if (theBoard.isSquareEmpty(currentX, currentY))
		body[0].draw(' ');
	else //There is something in this place, we dont want to destroy just to present our position right now
	{
		char sign = theBoard.getSignInBoard(currentX, currentY);
		this->show();
		Sleep(100);//For the effect
		body[0].draw(sign);
	}
				
	body[0].move(direction);
		
	if (theBoard.isSquareEmpty(currentX+ addToX, currentY+ addToY))//We show joker just if the place that it move on empty
		this->show();
}