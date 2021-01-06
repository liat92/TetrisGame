#include"Zshape.h"

/* This function initializes the body of the Plus shape according to it's current degree:
   The body will be(in accordance to point body index) :
  
    DEGREE_0  & DEGREE_180 | DEGREE_90 & DEGREE_270
  
        2  0                            2
           1  3                      1  0
                                     3
*/
Zshape::Zshape(int xCord, int yCord, eAngle theAngle)
	:RotateableBlocks(xCord, yCord, Block::REGULAR_BLOCK, theAngle)
{
	body[2].updatePoint(--xCord, yCord);
	body[1].updatePoint(++xCord, ++yCord);
	body[3].updatePoint(++xCord, yCord);
	initialBodyAccordingToAngle();
}