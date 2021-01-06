#ifndef __JOKER_H
#define __JOKER_H

#include "Block.h"
#include "Board.h"
#include "Utility.h"

class Joker : public Block
{
public:
	//Class attribute
	static constexpr char SIGN = '$';

	//Class method
	Joker(int xCord, int yCord);

	void move(Point::eKeys direction,const Board &theBoard);
};

#endif // __JOKER_H