#include <iostream>
using namespace std;

#include <windows.h>
#include <process.h>

#include "Utility.h"

/*
  This function adding to the coordinate according to direction.
*/
bool addToXAndYAccordingToOneStep(const Point::eKeys& direction, int& addToX, int& addToY)
{
	addToX = addToY = 0;
	//Check the direction and update addToX and addToy inaccordance
	if (direction == Point::LEFT)
		addToX--;
	else if (direction == Point::RIGHT)
		addToX++;
	else if (direction == Point::DOWN)
		addToY++;
	else//The given direction not valid so the block can not move in this direction
		return false;

	return true;//The direction was legal and therefore successfuly update add-on
}
