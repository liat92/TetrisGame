#include "Block.h"

//-----------------------------------------------------------------
//					constructors and distractor
//-----------------------------------------------------------------

/*
  Block constructor.
*/
Block::Block(int xCord,int yCord, int numOfPoints, char sign)
	: numOfPoints(numOfPoints), sign(sign)
{
	body.reserve(numOfPoints);
	for (int i = 0; i < numOfPoints; i++)
	{
		body.push_back(Point(xCord,yCord));
	}
}

Block::Block(const Block& other):sign(other.sign),numOfPoints(other.numOfPoints)
{
	body.reserve(numOfPoints);
	for (int i = 0; i < numOfPoints; i++)
		body.push_back(other.body[i]);
}

/*
 *  Block destructor.
*/
Block::~Block()
{
	body.clear();
}

//-----------------------------------------------------------------
//                    Block Public functions 
//-----------------------------------------------------------------

//--------------------------Get functions--------------------------

 /*
   This function return the number of point that block made off.
  */
 int Block::getNumOfPoint() const{return numOfPoints; }
 
 /*
   This function return specific x cordinate of point 
   in body (the point in the given index)
   Note: if the given index is not valid we return the first index.
 */
 int Block::getXOfBodyInIndex(int index) const
 {
	return ((index < numOfPoints) && (index >= 0)) ? body[index].getX() : 0;
 }
 
 /*
   This function return specific y cordinate of point 
   in body (the point in the given index)
   Note: if the given index is not valid we return the first index.
 */
 int Block::getYOfBodyInIndex(int index) const
 {
	 return((index < numOfPoints) && (index >= 0)) ? body[index].getY() : 0;
 }
 
 /*
   This function return the sign of the Block.
   */
 char Block::getSign()const
 {
	 return sign;
 }

//-----------------------------Move functions----------------------------------

/*
  This function receive direction and move the block.
  */
void Block::move(Point::eKeys direction)
{
	for (int i = 0; i < numOfPoints; i++)//Loop for move the body
	{
		body[i].draw(' ');
		body[i].move(direction);
	}
	this->show();
}

//------------------------------Other functions--------------------------

/* 
    This function print the block.
*/
void Block::show() const
{
	for (int i = 0; i < numOfPoints; i++)//Loop for printing each point of block
		body[i].draw(sign);
}

/*
   This function clear the block from screen.
*/
void Block::clearFromScreen()
{
	for (int index = 0; index < numOfPoints; index++)
		body[index].draw(' ');
}