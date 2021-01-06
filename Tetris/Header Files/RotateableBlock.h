#ifndef __ROTATEABLE_BLOCKS_H
#define __ROTATEABLE_BLOCKS_H

#include <Windows.h>
#include "Block.h"
#include <iostream>
using namespace std;
#include <ctgmath>

class RotateableBlocks : public Block
{

public:
	enum eAngle { DEGREE_0, DEGREE_90, DEGREE_180, DEGREE_270 };
	static constexpr int AMOUNT_OF_POSITIONS = 4;
	static constexpr int INDEX_OF_CENTER_POINT = 1;
	static constexpr int MATRIX_SIZE = 2;

protected:
	eAngle curAngle;
public:
	RotateableBlocks(int xCord, int yCord, int numOfPoints, eAngle curAngle, char sign = '%');
	RotateableBlocks(const RotateableBlocks &other);

	void rotate();
	void initialBodyAccordingToAngle();
	void updateDegreeAfterRotation();
};

#endif //__ROTATEABLE_BLOCKS_H