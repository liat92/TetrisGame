#ifndef __POINT_H
#define __POINT_H

#include <iostream>
using namespace std;

#include "Gotoxy.h"

class Point
{
//Class attributes:
	int x;
	int y;
//Class Methods:
public:
	enum eKeys { LEFT = 'a', RIGHT = 'd', DOWN = 's', ROTATE = 'r', STOP_MOVE = 'e' };
	Point(int x = 0, int y = 0);
	
	//Get and Set functions:
	int  getX() const;
	int  getY() const;
	void setX(int x);
	void setY(int y);

	//Other functions:
	void updatePoint(int x, int y);
	void move(eKeys direction);
	void draw(char sign) const;
};
#endif // __TPOINT_H
