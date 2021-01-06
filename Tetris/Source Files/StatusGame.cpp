#include "StatusGame.h"

//-----------------------------------------------------------------
//							constructors
//-----------------------------------------------------------------

/*
  StatusGame constructor.
*/
StatusGame::StatusGame(int numFellBlocks , int score , int xStatusPositionCord , int yStatusPositionCord )
	:numFellBlocks(numFellBlocks), score(score), xStatusPositionCord(xStatusPositionCord), yStatusPositionCord(yStatusPositionCord)
{}

StatusGame::StatusGame(ifstream& in)
{
	in.read((char*)this, sizeof(*this));
}

//-----------------------------------------------------------------
//			   		  StatusGame Public function
//-----------------------------------------------------------------

//---------------------Getting function---------------------

int StatusGame::getXStatusPositionCord()const { return xStatusPositionCord; }
int StatusGame::getYStatusPositionCord()const { return yStatusPositionCord; }

//---------------------Show functions---------------------

/*
  This function print on the screen the status of the game
  This function print this data at top left corner.
*/
void StatusGame::show()const
{
	gotoxy(xStatusPositionCord, yStatusPositionCord);
	cout << "Blocks that fell off: " << this->numFellBlocks << "   " << endl;
	cout << "Score: " << this->score << "    " << endl;
}

/* 
  This function print on the screen the status of the game
  This function print this data at x & y coordinate on screen.
*/
void StatusGame::show(int& xCord, int& yCord)const
{
	gotoxy(xCord, yCord++);
	cout << "Blocks that fell off: " << this->numFellBlocks << "   ";
	gotoxy(xCord, yCord++);
	cout << "Score: " << this->score << "   " << endl;
}

//-------------------Update Score Function-----------------

/*
  This function receive the number of removed lines and bool 
  parameter that represent if the lines were removed because of
  joker use.
  The function update score in accordance.
*/
void StatusGame::clearLineUpdateScore(int numOfRemovedLines, bool isByJoker)
{
	if (numOfRemovedLines > 0)//The score need to update just if lines removed
	{
		//Check if the line removed by joker use:
		if (isByJoker)
			score += (eScore::SINGELE_LINE_CLEAR / 2); //Adding to score half amount of point than SINGELE_LINE_CLEAR
		else//The lines were removed by regular block
			score += eScore::SINGELE_LINE_CLEAR + ((numOfRemovedLines - 1)*eScore::ADDITION_LINE);
	}
}

/*
  This function receive the distance that block does until the bottom
  and update score in accordance.
*/
void StatusGame::hardDropUpdateScore(int distance)
{
	score += (eScore::HARD_DROP * distance);
}

/*
  This function receive the number of square on board that explode
  and update score in accordance.
*/
void StatusGame::bombExplosionUpdateScore(int numOfSquareExplode)
{
	score -= (numOfSquareExplode*eScore::BOMB_EXPLOSION);
}

//-------------------Others Function-----------------
/*
  This function save the game.
*/
void StatusGame::save(ofstream &out) const
{
	out.write((const char*)this, sizeof(*this));
}

/*
  This function reset ths status data (to 0).
*/
void StatusGame::resetStatus()
{
	score = numFellBlocks = xStatusPositionCord= yStatusPositionCord= 0;
}

/*
  This function update the number of blocks that fail
  (default value 1).
*/
void StatusGame::updateNumFellBlocks(int addition)
{
	numFellBlocks += addition;
}