#ifndef __BLOCK_H
#define __BLOCK_H
#include<Windows.h>

#include <iostream>
using namespace std;

#include "Point.h"
#include "Board.h"
#include <vector>

class Block
{
//Class attributes:
public:
	static constexpr int REGULAR_BLOCK = 4;
	static constexpr int SPECIAL_BLOCK = 1;
protected:
	char sign;
	int numOfPoints;
	vector<Point> body;
	

//Class Methods:
protected:
	Block(int xCord, int yCord,int numOfPoints,char sign = '%');
	Block(const Block& other);
public:
	virtual ~Block();

	//Getting functions:
	int getNumOfPoint() const;
	int getXOfBodyInIndex(int index) const;
	int getYOfBodyInIndex(int index) const;
	char getSign()const;

	//Function for moving :
	virtual void move(Point::eKeys direction);

	//Other functions:
	void show() const;
	void clearFromScreen();
};

#endif // __BLOCK_H

