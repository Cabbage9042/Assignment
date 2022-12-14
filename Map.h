#pragma once
#include "Cell.h"
#include <vector>
#include "Sprite.h"
#include "Character.h"
#include "GameManager.h"
#include "Trap.h"
#define PI 3.1415926

enum { bottomSide, topSide, leftSide, rightSide};
enum { topRight, bottomRight, bottomLeft, topLeft };
//corner wall is included in horizontal rect
enum {outerTop,outerRight,outerBottom,outerLeft, 
	innerTop, innerRight, innerBottom, innerLeft, between};

class Map {
public:
	D3DXVECTOR2 topLeftCorner;	// included wall
	Sprite floorSprite;
	Texture lever;
	int numberOfCellRow;		// included wall
	int numberOfCellColumn;		// included wall
	vector<vector<Cell*> > cells; //is a wall, a floor or void. "W", "F", "V"
	D3DXVECTOR2 startPosition;
	Trap traps[4];
	RECT goalRect;
	RECT wallRect[9];



	void InitializeMap();
	void UninitializeMap();
	void RenderMap();
	bool collidedToWall(Sprite character, RectCollidedStatus* characterCollidedStatus,int *collidedXAxis,int *collidedYAxis);
	//bool collidedToAndFacingLever(Sprite* character, int* leverForWhichTrap);
	bool collidedToLever(Sprite* character, int* leverForWhichTrap);
	bool collidedToGoal(Sprite* character);
	bool collidedToTrap(Sprite* character, int* collidedTrap);

	void setHoleTo(char type, int mostBelowRow, int col, int numberOfBlockToChange = 4);
	void setTrapTo(char type, RelativePosition topRightPosition);

private:
	void updateWallRect();
	//bool collidedTcoWall(Sprite character, RectCollidedStatus* characterCollidedStatus, int* collidedXAxis, int* collidedYAxis);
	char getCellType(int row, int col);
	bool isCollided(RECT a, RECT b);
	D3DXVECTOR2 getCenterPoint(int side, RECT rect);
	RelativePosition leverPosition[4];
	RelativePosition trapBottomRightPosition[4];
	void createMap();
	void createTrap();
	void assignDefaultPosition();
	void setLeverAndHole(int leverForWhichTrap);
};

