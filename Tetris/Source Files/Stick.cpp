#include"Stick.h"

/* This function initializes the body of the stick shape according to it's current degree:
   The body will be (in accordance to point body index):
  
    DEGREE_0  &  DEGREE_180 | DEGREE_90 & DEGREE_270
    
           0 1 2 3                      0
                                        1
                                        2
                                        3
*/
Stick::Stick(int xCord,int yCord, eAngle theAngle)
	:RotateableBlocks(xCord, yCord, Block::REGULAR_BLOCK, theAngle)
{
	xCord++;
	for (int index = 1; index < numOfPoints; index++)
		body[index].updatePoint(xCord++, yCord);
	initialBodyAccordingToAngle();
}