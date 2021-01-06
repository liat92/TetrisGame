#include "Bomb.h"

//-----------------------------------------------------------------
//                          constructor
//-----------------------------------------------------------------

/*
  Bomb constructor.
*/
Bomb::Bomb(int xCord, int yCord)
	:Block(xCord, yCord, Block::SPECIAL_BLOCK,  this->SIGN) {}


//-----------------------------------------------------------------
//                    Bomb Public functions 
//----------------------------------------------------------------

/*
  This function explode this bomb and the blocks at EXPLOSION_RANGE X EXPLOSION_RANGE range.
  Note: the bomb need to recognize the board in order to get permission to all the other blocks that fell 
  (if they are in its area it will explode them).
*/
int Bomb::explosion(Board &theBoard)
{
	// Note: we are going half way from the explosion range in order to get to the left and upper corner 
	int numExploded = 0;
	int yCordInitialze = theBoard.getComparableYcorOfBoard(body[0].getY()) - EXPLOSION_RANGE / 2;
	int xCordInitialze = theBoard.getComparableXcorOfBoard(body[0].getX()) - EXPLOSION_RANGE / 2;

	//Loop for explosion in EXPLOSION_RANGE X EXPLOSION_RANGE range
	for (int yCord = yCordInitialze; yCord < yCordInitialze + EXPLOSION_RANGE; yCord++)
		for (int xCord = xCordInitialze; xCord < xCordInitialze + EXPLOSION_RANGE; xCord++)
			if (!theBoard.isSquareEmpty(xCord, yCord)) // Check if there is something there 
			{
				Sleep(50);//For explode effect
				if (theBoard.clearSign(xCord, yCord)) //Check if what that was there will explode (now clear)
					numExploded++;
			}

	if (numExploded != 0)//Check if blocks exploded
		return numExploded - 1; // -1 becuase the boomb explosion itself doesn't count
	else
		return numExploded;// numExploded is 0 (no blocks exploded).
}

/*
  This function Check if the bomb will explode after one step in the 
  given direction (it will explode if there is obstacle there).
*/
bool Bomb::itWillExplodeBecauseObstacle(const Point::eKeys& direction, const Board &theBoard)
{
	int addToX, addToY;
	addToXAndYAccordingToOneStep(direction, addToX, addToY);

	int xCord = theBoard.getComparableXcorOfBoard(body[0].getX()) + addToX;
	int yCord = theBoard.getComparableYcorOfBoard(body[0].getY()) + addToY;

	return (!theBoard.isSquareEmpty(xCord, yCord) == true) ? true : false;
}

