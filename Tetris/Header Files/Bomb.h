#ifndef __BOMB_H
#define __BOMB_H

#include "Board.h"
#include "Block.h"
#include "Utility.h"

class Bomb : public Block
{
public:
	//Class attribute
	static constexpr int EXPLOSION_RANGE = 3;
	static constexpr char SIGN = '@';

	//Class method
	Bomb(int xCord, int yCord);

	int explosion(Board &theBoard);
	bool itWillExplodeBecauseObstacle(const Point::eKeys& direction, const Board &theBoard);

};

#endif // __BOMB_H

