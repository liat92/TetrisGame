#include"Lshape.h"


/*
 This function initializes the body of the Lshape according to it's given start degree

    DEGREE_0  | DEGREE_90 | DEGREE_180 |  DEGREE_270
        0          2 0         3 1 2           3
    2 1 3          1           0	       1
                   3                         0 2
*/
Lshape::Lshape(int xCord, int yCord, eAngle theAngle)
	:RotateableBlocks(xCord, yCord, Block::REGULAR_BLOCK, theAngle)
{
	body[2].updatePoint(xCord, ++yCord);
	body[1].updatePoint(++xCord, yCord);
	body[3].updatePoint(++xCord, yCord);
	initialBodyAccordingToAngle();
}
