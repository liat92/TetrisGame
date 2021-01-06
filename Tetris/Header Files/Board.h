#ifndef __BOARD_H
#define __BOARD_H
#include<Windows.h>

#include <iostream>
using namespace std;

#include"Gotoxy.h"
#include "Point.h"
#include <fstream>

//class Block;

class Board
{  
//Class attributes:
public:
	static constexpr char SIGN = '#';
	static constexpr int LENGTH = 15;
	static constexpr int WIDTH = 10;
	
private:
	Point boardStartPos;
	int numOfFullSquareInLine[LENGTH];
	char signsBoard[LENGTH][WIDTH] ;

//Class Methods:
public:
	Board(const Point & p);
	Board(const Board& other) = delete;
	Board(ifstream& in);

	//Getting functions:
	const Point &getBoardStartPos()const;
	char getSignInBoard(const int &xCord, const int &yCord) const;
	int getComparableXcorOfBoard(const int &xCord) const;
	int getComparableYcorOfBoard(const int &yCord) const;

	//Checking functions:
	bool isLineFull(const int& line) const;
	bool isLineEmpty(const int& line) const;
	bool isSquareEmpty(const int &xCord, const int &yCord) const;
	bool isThereObstacleAt(const int &xCord, const int &yCord)const;
	bool withinBoundaries(const int &xCord, const int &yCord)const;
	bool notWithinBoundariesOrThereIsSomethingAt(const int &xCord, const int &yCord)const;

	//Fill & clear square functions:
	bool clearSign(const int &xCord, const int &yCord);
	void fillSign(const char &sign, const int &xCord, const int &yCord);

	//Board update functions:
	void moveForwardBlocks(const int &line);

	//Other functions:
	void save(ofstream &out) const;
	void draw() const;
	void resetBoard();
	
private:
	void moveDownOneLine(const int &lineIndex);
	void resetNumOfFullSquareInLineArray();

};

#endif // !__BOARD_H
