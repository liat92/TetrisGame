#include "TetrisGame.h"

//-----------------------------------------------------------------
//		      Constructor/Destractor
//-----------------------------------------------------------------

/*
  TetrisGame constructor.
*/
TetrisGame::TetrisGame()
	: theBoard (Point(X_BOARD_POS, Y_BOARD_POS))
{
	gameOver = false;
	gameSpeed = TetrisGame::eSpeedRange::INITIAL_SPEED;
	curBlock = nullptr; 
}

//-----------------------------------------------------------------
//	         TetrisGame Public function
//-----------------------------------------------------------------

/*
  This function run the Tetris game.
*/
void TetrisGame::run()
{
	char keyPressed;
	printMenu(25, 5);//Print the menu

	startOrEndOrLoadGame(keyPressed); //Continue to get input while the user doesn't enter a valid input (start\exit\load)

	if (keyPressed == TetrisGame::START_OR_RESTART)
	{
		clearScreen();
		startPlaying(keyPressed);
	}
	else if (keyPressed == TetrisGame::LOAD)
	{
		clearScreen();
		ifstream inFile("TetrisGame.dat", ios::binary);
		loadGame(inFile);
		inFile.close();
		startPlaying(keyPressed);
	}
	else //The keyPressed is EXIT
	{
		printGoodByeMassege();
	}
	system("pause>null");
}


//---------------------------------Printing functions----------------------------------

/*
  This function print the menu of the game.
*/
void TetrisGame::printMenu(int xCord, int yCord)const
{
	printAtLocation("--------MENU--------", xCord, yCord);
	yCord++;

	printAtLocation("Start\\Restart     ", xCord, yCord);
	cout << "-" << START_OR_RESTART - '0' << "-";

	printAtLocation("Pause\\continue    ", xCord, yCord);
	cout << "-" << PAUSE_OR_CONTINUE - '0' << "-";

	printAtLocation("Speed up          ", xCord, yCord);
	cout << "-" << SPEED_UP - '0' << "-";

	printAtLocation("Speed down        ", xCord, yCord);
	cout << "-" << SPEED_DOWN - '0' << "-";

	printAtLocation("Save              ", xCord, yCord);
	cout << "-" << SAVE - '0' << "-";

	printAtLocation("Load              ", xCord, yCord);
	cout << "-" << LOAD - '0' << "-";

	printAtLocation("Exit              ", xCord, yCord);
	cout << "-" << EXIT - '0' << "-" << endl;
}

/*
  This function print the title of the game.
*/
void TetrisGame::printTetrisTitle()const
{
	int xCord = X_BOARD_POS - 9 , yCord = 0;
	printAtLocation("--------Tetris Game--------", xCord, yCord);
}

/* 
  This function clear the screen and print goodbye massege.
*/
void TetrisGame::printGoodByeMassege()const
{
	clearScreen();
	int xCord = X_BOARD_POS -1, yCord = Y_BOARD_POS + 5;
	printAtLocation("Good bye!", xCord, yCord);
}

/*
  This function clears the screen tell the user that the game is over.
  Print the data of the game and ask if the user want to continue.
  If yes return true else return false.
*/
bool TetrisGame::endGameAskToContinue(int xCord, int yCord)const
{
	//printDetails:
	clearScreen();
	printAtLocation("G-A-M-E  O-V-E-R ", xCord, yCord);
	yCord++;
	theStatus.show(xCord, yCord);
	yCord++;

	//Ask to continue:
	char answer;
	printAtLocation("If you want play again press 1 else press 9", xCord, yCord);
	answer = _getch();
	startOrEndOrLoadGame(answer);
	return (answer == eMenu::START_OR_RESTART) ? true : false;
}

//-------------------------------key pressed functions--------------------------------

/*
  This function receive keyPressed and opreate in accordance to the menu.
*/
void TetrisGame::operateGameByKeyPressed(char &keyPressed)
{
	switch (keyPressed)
	{
	case TetrisGame::START_OR_RESTART:
		restartGame();
		break;

	case TetrisGame::PAUSE_OR_CONTINUE:
		keyPressed = _getch();
		pauseGame(keyPressed);
		break;

	case TetrisGame::SPEED_UP:
		if (gameSpeed - TetrisGame::SPEED_ADD >= TetrisGame::eSpeedRange::MAX_SPEED)
			gameSpeed -= TetrisGame::SPEED_ADD;
		break;

	case TetrisGame::SPEED_DOWN:
		if (gameSpeed + TetrisGame::SPEED_ADD <= TetrisGame::eSpeedRange::MIN_SPEED)
			gameSpeed += TetrisGame::SPEED_ADD;
		break;
	
	case TetrisGame::SAVE:
	{
		ofstream outFile("TetrisGame.dat", ios::binary | ios::trunc);
		saveGame(outFile);
		outFile.close();
	}
		break;

	case TetrisGame::LOAD:
	{
		Sleep(800);
		delete curBlock;//Delete current Block

		ifstream inFile("TetrisGame.dat", ios::binary);
		loadGame(inFile);

		theBoard.draw();
		theStatus.show();
		curBlock = createNewBlock();
		curBlock->show();

		inFile.close();		
	}
		break;

	case TetrisGame::EXIT: gameOver = true;
		break;
	}//End of switch
}

/*
  This function receive keyPressed and opreate in accordance to the Point::ekeys.
*/
void TetrisGame::operateBlockByKeyPressed(const char &keyPressed)
{
	if ((typeid(*curBlock)) == (typeid(Joker)) && keyPressed == Point::eKeys::STOP_MOVE)//We Check if this is joker and we need to stop him
	{
		fillBlockAndUpdateBoard();//We stop joker and fill him on board
		freeAndCreateNewBlock();//We need new block
	}
	else if (keyPressed == Point::eKeys::DOWN)//If the keyPressed is down the block go hard drop down
	{		
		int distance = moveHardDropDown();//Move hard drop down and get the distance
		theStatus.hardDropUpdateScore(distance);//Update the score in accordance.
		theStatus.show();//Show data
	}
	else if ((typeid(*curBlock)) == (typeid(Bomb)) && isDirectionValid((Point::eKeys)keyPressed))//Check if explode bomb
	{
		if (((Bomb*)curBlock)->itWillExplodeBecauseObstacle((Point::eKeys)keyPressed,theBoard))//Check if there is obstacle there
		{
			bombExplosion();
			freeAndCreateNewBlock();//The bomb explode so we need new block
		} 
		else if(isOkToMove((Point::eKeys)keyPressed))//There is not an obstacle that will
			//explode so just move the bomb
			curBlock->move((Point::eKeys)keyPressed);
	}
	else if (keyPressed == Point::eKeys::ROTATE)
	{
		if (isOkToRotate())//Check if the block is rotatable and if is ok to rotate him
		{
			curBlock->clearFromScreen();
			((RotateableBlocks*)curBlock)->rotate();
			curBlock->show();
		}
	}		
	else if (isOkToMove((Point::eKeys)keyPressed))
	{
		moveBlock(keyPressed);
	}	
}


//-------------------------------Save / Load functions--------------------------------

/*
  This function save the necessary data of the game: The board and the status.
  Note: the current block that fall down at the time we save is not a necessary data
  therefore we didn't save this data.
*/
void TetrisGame::saveGame(ofstream &out)const
{
	theBoard.save(out);
	theStatus.save(out);
}

/*
  This function load the data of the game: The board and the status.
  Note: the current block that fall down at the time we save is not a necessary data
  therefore we didn't load this data.
  Note 2: we use operator =  of Board and StatusGame class.
*/
void TetrisGame::loadGame(ifstream &in)
{
	theBoard = Board(in);
	theStatus = StatusGame(in);
}

//----------------------------------Game play function-----------------------------------

/*
  This function is the game function.
*/
void TetrisGame::startPlaying(char &keyPressed)
{
	curBlock = createNewBlock();

	//Printing data and board
	theStatus.show();
	printMenu(theStatus.getXStatusPositionCord(), theStatus.getYStatusPositionCord() + 3);
	printTetrisTitle();
	theBoard.draw();
	curBlock->show();

	while (!gameOver)//Play until gameOver
	{
		while (_kbhit()) //Checks if there is anything in the buffer and operate until there is nothing
		{
			keyPressed = _getch(); // take the head of the buffer
			operateGameByKeyPressed(keyPressed); // operate by menu keyPressed
			operateBlockByKeyPressed(keyPressed);// operate by  keyPressed
		}
		Sleep(gameSpeed);//The game speed

		//After user pressed action the block need to continue to move down
		if (!isOkToMove(Point::eKeys::DOWN))//Check if the block can not move down
			notValidMovingDown();//Note: this function update if game is over
		else
			moveBlock(Point::eKeys::DOWN);

	}//End of while
	printGoodByeMassege();
	delete curBlock;
}

/*
  This function restart the game (all the element will be initilaze to the start data).
*/
void TetrisGame::restartGame()
{
	clearScreen();
	gotoxy(5, 5);
	cout << "NEW GAME, Get ready...";
	Sleep(1200);//For inform the user to be ready.
	clearScreen();

	gameSpeed = TetrisGame::INITIAL_SPEED;
	gameOver = false;

	//Restart and print game elements:
	theStatus.resetStatus();
	theStatus.show();
	printMenu(theStatus.getXStatusPositionCord(), theStatus.getYStatusPositionCord() + 3);

	theBoard.resetBoard();
	printTetrisTitle();
	theBoard.draw();

	//Delete current Block and Create new one:
	Sleep(200);
	delete curBlock;
	curBlock = createNewBlock();
	curBlock->show();
}

/*
  This function checks if the block that was created now override any block in its way on the board.
*/
bool TetrisGame::isGameOver()const
{
	if ((typeid(*curBlock)) != (typeid(Joker)))//Joker can move over other blocks
	{
		int xCord, yCord;
		yCord = theBoard.getComparableYcorOfBoard(curBlock->getYOfBodyInIndex(0));

		for (int i = 0; i < curBlock->getNumOfPoint(); i++)//Check each point of block
		{
			xCord = theBoard.getComparableXcorOfBoard(curBlock->getXOfBodyInIndex(i));
			yCord = theBoard.getComparableYcorOfBoard(curBlock->getYOfBodyInIndex(i));

			if (!theBoard.isSquareEmpty(xCord, yCord))
				return true;
		}
	}
	return false;
}

/*
  This function continues getting input until the user enters
  PAUSE_OR_CONTINUE key in order to pause the game .
*/
void TetrisGame::pauseGame(char& keyPressed)const
{
	do
	{
		if (_kbhit())
			keyPressed = _getch(); // take the head of the buffer

	} while ((eMenu)keyPressed != TetrisGame::PAUSE_OR_CONTINUE);
}

/*
  This function continues getting input while the user doesn't enter a
  valid input (start\exit).
*/
void TetrisGame::startOrEndOrLoadGame(char& keyPressed)const
{
	do
	{
		if (_kbhit())
			keyPressed = _getch(); // take the head of the buffer

	} while ((eMenu)keyPressed != eMenu::START_OR_RESTART && (eMenu)keyPressed != eMenu::EXIT
		&& (eMenu)keyPressed != eMenu::LOAD);
}

//--------------------------Operate Block in relation to the board of the game------------------------

/*
  This function check if the block within the board boundaries and don't go up on exsist block
  after rotation.
*/
bool TetrisGame::isOkToRotate()const
{
	if ((typeid(*curBlock)) == (typeid(Joker)) || (typeid(*curBlock)) == (typeid(Bomb))|| (typeid(*curBlock)) == (typeid(Square)))
	{
		return false; //Joker, Bomb and Square can't be rotated.
	}
	else 
	{
		RotateableBlocks* tempBlock = new RotateableBlocks(*((RotateableBlocks*)curBlock));
		tempBlock->rotate();

		bool isRotationValid = isBlockAtValidLocation(tempBlock); //addTo x and y is 0 Because we check the body in his 
		//current location- there is no movement
		delete tempBlock;//Delete temp Block
		return  isRotationValid;
	}
	
}

/* 
  This function check if the block within the board boundaries after one 
  step in the given direction and if there is not any obstacle on the movement.
*/
bool TetrisGame::isOkToMove(const Point::eKeys& direction)const
{
	int addToX,addToY;

	//We check the option to move just if the addition succeeded (becuase else the step not valid)
	if (addToXAndYAccordingToOneStep(direction, addToX, addToY))
	{
		int xCord, yCord, numOfPoints = curBlock->getNumOfPoint();

		for (int index = 0; index < numOfPoints; index++)
		{
			//Getting the location of the coordinate shoud be in the board
			xCord = ((curBlock->getXOfBodyInIndex(index)) - theBoard.getBoardStartPos().getX()) + addToX;
			yCord = ((curBlock->getYOfBodyInIndex(index)) - theBoard.getBoardStartPos().getY()) + addToY;

			//Check if the point of the body within boundaries after that check if there is obstacle
			if (theBoard.withinBoundaries(xCord, yCord))
			{
				if (isThereObstacleAt(xCord, yCord))
					return false;
			}
			else
				return false;
		}
		return true;//If we did't return false, the block can move.
	}
	return false;
}

/*
  This function check if the is there obstacle at the given coordinate.
*/
bool TetrisGame::isThereObstacleAt(int& xCord, int& yCord)const
{
	if ((typeid(*curBlock)) == (typeid(Joker)))
		return false;
	else
		//If the square in the given coordinate is not empty it means that there is obstacle
		//at this square so we return true
		return theBoard.isThereObstacleAt(xCord,yCord);
}

/*
  This function move block hard drop down.
*/
int TetrisGame::moveHardDropDown()
{
	int distance = 0;//The amount of step we moved.

	//As long as we can move down we move and count distance	
	while (isOkToMove(Point::DOWN))
	{
		moveBlock(Point::DOWN);
		distance++;
	}

	return distance;
}

/*
  This function move block so that if the block is joker the move is different form 
  others moves (it can move throw blocks).
*/
void TetrisGame::moveBlock(char keyPressed)const
{
	//We check if the block is Joker because it have other move then the rest of blocks
	if ((typeid(*curBlock)) == (typeid(Joker)))
		((Joker*)curBlock)->move((Point::eKeys)keyPressed, theBoard);
	else
		curBlock->move((Point::eKeys)keyPressed);
}

/*
  This function fills curBlock on the board.
*/
void TetrisGame::fillBlockOnBoard()
{
	int xCord, yCord, numOfPoints = curBlock->getNumOfPoint();
	char sign = curBlock->getSign();

	//Loop for filling block on board:
	for (int i = 0; i < numOfPoints; i++)
	{
		xCord = theBoard.getComparableXcorOfBoard(curBlock->getXOfBodyInIndex(i));
		yCord = theBoard.getComparableYcorOfBoard(curBlock->getYOfBodyInIndex(i));

		if (theBoard.isSquareEmpty(xCord, yCord))//We fill Block on board just if the square was empty
			theBoard.fillSign(sign, xCord, yCord);
	}
}

/*
  This function raffle a position and shape and returns the shape it created.
*/
 Block* TetrisGame::createNewBlock()
{
	Block* temp;
	do
	{
		int form = rand() % TetrisGame::AMOUNT_TYPE_OF_BLOCK;
		int position = rand() % RotateableBlocks::AMOUNT_OF_POSITIONS; 

		int xCord = TetrisGame::X_BOARD_POS + (Board::WIDTH)/2 ;//For initilize first Block point
		int yCord = TetrisGame::Y_BOARD_POS;

		switch ((eType)form)
		{
		case TetrisGame::SQUARE:
			temp= new Square(xCord, yCord);
			break;
		case TetrisGame::STICK:
			temp = new Stick(xCord, yCord,(RotateableBlocks::eAngle)position);
			break;
		case TetrisGame::L_SHAPE:
			temp = new Lshape(xCord, yCord,(RotateableBlocks::eAngle)position);
			break;
		case TetrisGame::Z_SHAPE:
			temp = new Zshape(xCord, yCord, (RotateableBlocks::eAngle)position);
			break;
		case TetrisGame::PLUS:
			temp = new Plus(xCord, yCord, (RotateableBlocks::eAngle)position);
			break;
		case TetrisGame::JOKER:
			temp = new Joker(xCord, yCord);
			break;
		case TetrisGame::BOMB:
			temp = new Bomb(xCord, yCord);
			break;
		default:
			return nullptr;
		}

	} while (isBlockNotAboveTopLimit(temp));//Loop to ensure that the was block that created not exceed
	                                        //from top limit

	return temp;
}

/*
  This function free the given block and create another (this function update the status in accordance)
  and checks if after creating a new block the game is over.
*/
void TetrisGame::freeAndCreateNewBlock()
{
	delete curBlock;//Delete current Block
	curBlock = createNewBlock();

	theStatus.updateNumFellBlocks();//Update the number of fell blocks (by 1)
	theStatus.show();

	//We check and update if the game is over
	gameOver = isGameOver();

	curBlock->show();

	if (gameOver)
	{
		Sleep(200);//For let the user see why the game is over
		//If the user want to play again, so the game is not over
		if (endGameAskToContinue(15, 10))
			restartGame();
	}
}

/*
  This function fill the block on board and update the board in accordance
  (this function update the status in accordance).
*/
void TetrisGame::fillBlockAndUpdateBoard()
{
	//Fill Block on signBoard:
	fillBlockOnBoard();

	int line;
	int numOfPoints = curBlock->getNumOfPoint();
	int numOfRemovedLines = 0;

    //Loop for checking if lines are full in according to the block that filled
	for (int index = 0; index < numOfPoints; index++)
	{
		line = theBoard.getComparableYcorOfBoard(curBlock->getYOfBodyInIndex(index));

		if (theBoard.isLineFull(line))
		{
			numOfRemovedLines++;
			theBoard.moveForwardBlocks(line);
		}
	}

	theStatus.clearLineUpdateScore(numOfRemovedLines, (typeid(*curBlock)) == (typeid(Joker)));
	theStatus.show();
}

/*
 This function handles cases where block cannot go down (this function update the status
 and gamever in accordance).
*/
void TetrisGame::notValidMovingDown()
{	
	if ((typeid(*curBlock)) == (typeid(Bomb)))//Check if current block is bomb
		bombExplosion();//If bomb can not move down it exploded
	else//The block is not bomb so we just fill block and update board
		fillBlockAndUpdateBoard();

	freeAndCreateNewBlock();//Note: the attribute "gameOver" will be changed in accordance
	
}

/*
  This function explode bomb (this function update the status in accordance).
*/
void TetrisGame::bombExplosion()
{
	fillBlockOnBoard();//Because we want to remove the sign of bomb from board with the explosion

	int numExploded = ((Bomb*)curBlock)->explosion(theBoard);//Bomb exploded blocks and return how many
	theStatus.bombExplosionUpdateScore(numExploded);//We update the score in accordance bomb explosion
	theStatus.show();
}

 //-------------------------------------------------------------------------------
 //			     Checking functions 
 //-------------------------------------------------------------------------------

/*
   This function checks if the block that was created was not build above top limit.
*/ 
 bool TetrisGame::isBlockNotAboveTopLimit(Block *&temp)const
 {
	 int numOfPoints = temp->getNumOfPoint();

	 for (int index = 0; index < numOfPoints; index++)
	 {
		 if (temp->getYOfBodyInIndex(index) < Y_BOARD_POS)
			 return true; 
	 }
	 return false;
 }

/*
   This function receive adding to x and y (that represent step od the block) and block.
   The function check if the block with after steps will be in valid location.
*/
 bool TetrisGame::isBlockAtValidLocation(RotateableBlocks * &curBlock)const
 {
	 int xCord, yCord;
	 int numOfPoints = curBlock->getNumOfPoint();

	 for (int index = 0; index < numOfPoints; index++)
	 {
		 //Getting the location of the coordinate shoud be in the board
		 xCord = ((curBlock->getXOfBodyInIndex(index)) - theBoard.getBoardStartPos().getX());
		 yCord = ((curBlock->getYOfBodyInIndex(index)) - theBoard.getBoardStartPos().getY());

		 //Check if the point of the body within boundaries and Check if it can move
		 if (theBoard.withinBoundaries(xCord, yCord))
		 {
			 if (isThereObstacleAt(xCord, yCord))
				 return false;
		 }
		else
			return false;
	 }
	 return true;//If we did't return false, the block is in valid location.
 }

 /*
 * This function receive Point::eKeys and check if this eKeys of direction (left,right,down).
*/
 bool TetrisGame::isDirectionValid(Point::eKeys direction)
 {
	 return (direction == Point::eKeys::DOWN || direction == Point::eKeys::LEFT || direction == Point::eKeys::RIGHT);
 }

 /* This function recieve string and this string will be print in the place that the cordinates present.
    and going down a row.
 */
 void TetrisGame::printAtLocation(const char* str, int& xCordinate, int& yCordinate) const
 {
	 gotoxy(xCordinate, yCordinate++);//yCordinate++ for line down
	 cout << str;
 }
