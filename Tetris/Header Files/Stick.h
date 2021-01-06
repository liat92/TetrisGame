#ifndef __STICK_H
#define __STICK_H

#include "RotateableBlock.h"

class Stick :  public RotateableBlocks
{
public:
	Stick(int xCord, int yCord, eAngle theAngle);
};

#endif // __STICK_H