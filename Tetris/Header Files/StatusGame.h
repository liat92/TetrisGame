#ifndef __STATUS_GAME_H
#define __STATUS_GAME_H

#include <iostream>
using namespace std;
#include "Gotoxy.h"
#include <fstream>

class StatusGame
{
//Class attributes:
public:
	enum eScore {HARD_DROP = 2,BOMB_EXPLOSION = 50, SINGELE_LINE_CLEAR = 100, ADDITION_LINE = 200};
private:
	int xStatusPositionCord;
	int yStatusPositionCord;
	int numFellBlocks;
	int score;

//Class Methods:
public:
	StatusGame(int numFellBlocks = 0, int score = 0, int xStatusPositionCord = 0, int yStatusPositionCord = 0);
	StatusGame(const StatusGame& other) = delete;
	StatusGame(ifstream& in);

	//Getting function:
	int getXStatusPositionCord()const;
	int getYStatusPositionCord()const;

	//Show functions:
	void show()const;
	void show(int& xCord, int& yCord)const;

	//Update Score Function:
	void clearLineUpdateScore(int numOfRemovedLines, bool isByJoker);
	void hardDropUpdateScore(int distance);
	void bombExplosionUpdateScore(int numOfSquareExplode);

	//Others Function:
	void save(ofstream &out) const;
	void resetStatus();
	void updateNumFellBlocks(int addition = 1);
};

#endif // __STATUS_GAME_H