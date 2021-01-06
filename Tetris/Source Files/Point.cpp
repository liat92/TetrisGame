#include "Point.h"

//-----------------------------------------------------------------
//					         constructor
//-----------------------------------------------------------------

/*
  Point constructor.
*/
Point::Point(int x, int y) : x(x), y(y){}

//-----------------------------------------------------------------
//					      Point Public functions
//-----------------------------------------------------------------

//------------------------Get & Set functions----------------------

/*
  This function return the x cordinate of the point.
*/
int Point::getX() const {return x;}

/*
  This function return the y cordinate of the point.
*/
int Point::getY() const {return y;}

/*
  This function receive new x and change the x cordinate of the point.
*/
void Point::setX(int x){this->x = x;}

/*
  This function receive new y change the y cordinate of the point.
*/
void Point::setY(int y){this->y = y;}

//-----------------------others function------------------------

/*
  This function change both x and y cordinate of the point.
*/
void Point::updatePoint(int x, int y)
{
	this->x = x;
	this->y = y;
}

/*
  This function receive sign and print the sign on the screen
  acorrding to the x and y coordinate of the point.
*/
void Point::draw(char sign)const
{
	gotoxy(x, y);
	cout << sign;
}

/* 
  This function receive direction and update the coordinates
  of the point in accordance to the direction.
*/
void Point::move(Point::eKeys direction)
{
	switch (direction)
	{
	case Point::LEFT:  x--;
		break;
	case Point::RIGHT: x++;
		break;
	case Point::DOWN: y++;
		break;
	}
}