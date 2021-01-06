#include "RotateableBlock.h"

//-----------------------------------------------------------------
//					        constructors 
//-----------------------------------------------------------------

/*
  RotateableBlocks constructor.
*/
RotateableBlocks::RotateableBlocks(int xCord, int yCord, int numOfPoints, eAngle curAngle, char sign)
	:Block(xCord, yCord, numOfPoints, sign) , curAngle(curAngle){}

RotateableBlocks::RotateableBlocks(const RotateableBlocks &other) : Block(other), curAngle(other.curAngle) {}

//-----------------------------------------------------------------
//                    RotateableBlocks Public functions 
//-----------------------------------------------------------------

/*
  This function rotate blocks by a formula (we use matrix that represent 
  rotation by angle of 90 degrees).
 */
void RotateableBlocks::rotate()
{
	int rotationMatrix[MATRIX_SIZE][MATRIX_SIZE] = { {0,1}, {-1,0} };
	                                                                 
	int  vectorRotX, vectorTx;
	int  vectorRotY, vectorTy;

	//The center point of the block determined to be the body in index 1
	int centerPointX = body[INDEX_OF_CENTER_POINT].getX();
	int centerPointY = body[INDEX_OF_CENTER_POINT].getY();

	for (int index = 0; index < numOfPoints; index++)
	{
		vectorRotX = body[index].getX() - centerPointX;
		vectorRotY = body[index].getY() - centerPointY;

		vectorTx = rotationMatrix[0][0]*vectorRotX + rotationMatrix[0][1]*vectorRotY;
		vectorTy = rotationMatrix[1][0]*vectorRotX + rotationMatrix[1][1]*vectorRotY;

		body[index].setX(centerPointX + vectorTx);
		body[index].setY(centerPointY + vectorTy);
	}

	updateDegreeAfterRotation();
}

/*
  This function initial the body according to its current angle.
*/
void RotateableBlocks::initialBodyAccordingToAngle()
{
	//The body of each block initial to be in position of degree 0 so we need to 
	//update the body according to the current degree.
	if (curAngle > DEGREE_0)
	{
		for (int numOftimes = 0; numOftimes < curAngle; numOftimes++)
			rotate();
	}
}

/* 
  This function update degree to the current degree.
  Note: if the angle is more than 270 then it will be initialized to 0 angle.
*/
void RotateableBlocks::updateDegreeAfterRotation()
{
	int updatedDegree = curAngle; 

	(updatedDegree == RotateableBlocks::DEGREE_270) ? updatedDegree = RotateableBlocks::DEGREE_0 : updatedDegree++;

	curAngle = (RotateableBlocks::eAngle)updatedDegree;
}
