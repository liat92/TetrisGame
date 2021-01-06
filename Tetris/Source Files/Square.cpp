#include "Square.h"

//-----------------------------------------------------------------
//                          constructor
//-----------------------------------------------------------------

/*
  This function initializes the body of the Square shape.
   The body will be:

    0  2
    1  3
*/
Square::Square(int xCord, int yCord)
	:Block(xCord,yCord, Block::REGULAR_BLOCK)
{
	int x = body[0].getX();
	int y = body[0].getY() + 1;

	body[1].updatePoint(x++, y--);
	body[2].updatePoint(x, y++);
	body[3].updatePoint(x, y);
}