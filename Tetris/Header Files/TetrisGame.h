#ifndef __TetrisGame_H
#define __TetrisGame_H

#include <iostream>
using namespace std;
#include <Windows.h>
#include <conio.h>
#include "Gotoxy.h"
#include <fstream>

#include "StatusGame.h"
#include "Board.h"
#include "Stick.h"
#include "Bomb.h"
#include "Plus.h"
#include "Zshape.h"
#include "Lshape.h"
#include "Joker.h"
#include "Square.h"
#include "Utility.h"

class TetrisGame
{

//Class attributes:
public:
	enum eSpeedRange { SPEED_ADD = 100,MAX_SPEED = 200 ,INITIAL_SPEED = 650, MIN_SPEED = 1200 };
	enum eMenu {START_OR_RESTART = '1', PAUSE_OR_CONTINUE, SPEED_UP, SPEED_DOWN, SAVE, LOAD, EXIT = '9'};
	enum eType { SQUARE, STICK,L_SHAPE,Z_SHAPE,PLUS, JOKER, BOMB };
	static constexpr int AMOUNT_TYPE_OF_BLOCK = 7;
	static constexpr int X_BOARD_POS = 35, Y_BOARD_POS =3;

private:
	Board theBoard;
	StatusGame theStatus;
	Block* curBlock;
	bool gameOver;
	int gameSpeed;

//Class Methods:
public:
	TetrisGame();
	TetrisGame(const TetrisGame &other) = delete;
	//~TetrisGame();

	void run();

private:
	
	//Printing functions:
	void printMenu(int xCord, int yCord)const;
	void printTetrisTitle()const;
	void printGoodByeMassege()const;
	void printAtLocation(const char* str, int& xCord, int& yCord)const;
	bool endGameAskToContinue(int xCord, int yCord)const;

	//key pressed functions:
	void operateGameByKeyPressed(char &keyPressed);
	void operateBlockByKeyPressed(const char &keyPressed);

	//Save/Load functions:
	void saveGame(ofstream &out)const;
	void loadGame(ifstream &in);

	//Game play function:
	void startPlaying(char &keyPressed);
	void restartGame();
	bool isGameOver()const;
	void pauseGame(char& keyPressed)const;
	void startOrEndOrLoadGame(char& keyPressed)const;

	//Operate Block in relation to the board of the game
	bool isOkToRotate()const;
	bool isOkToMove(const Point::eKeys& direction)const;
	bool isThereObstacleAt(int& xCord, int& yCord)const;
	bool isDirectionValid(Point::eKeys direction);
	int moveHardDropDown();
	void moveBlock(char keyPressed)const;
	void fillBlockOnBoard();
	Block* createNewBlock();
	void freeAndCreateNewBlock();
	void fillBlockAndUpdateBoard();
	void notValidMovingDown();
	void bombExplosion();

	//Helping functions:
	bool isBlockNotAboveTopLimit(Block *&temp)const;
	bool isBlockAtValidLocation(RotateableBlocks * &curBlock)const;
};

#endif // !__TetrisGame_H

