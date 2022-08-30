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


class Map {
public:
	D3DXVECTOR2 topLeftCorner;	// included wall
	Sprite floorSprite;
	Texture lever;
	int numberOfCellRow;		// included wall
	int numberOfCellColumn;		// included wall
	vector<vector<Cell*> > cells; //is a wall, a floor or void. "W", "F", "V"
	D3DXVECTOR2 startPosition;
	D3DXVECTOR2 endPosition;
	Trap traps[4];



	void InitializeMap();
	void UninitializeMap();
	void RenderMap();
	bool collidedToWall(Sprite character, RectCollidedStatus* characterCollidedStatus,int *collidedXAxis,int *collidedYAxis);
	//bool collidedToAndFacingLever(Sprite* character, int* leverForWhichTrap);
	bool collidedToLever(Sprite* character, int* leverForWhichTrap);

	void setHoleTo(char type, int mostBelowRow, int col, int numberOfBlockToChange = 4);
	void setTrapTo(char type, RelativePosition topRightPosition);

private:
	char getCellType(int row, int col);
	bool isCollided(RECT a, RECT b);
	D3DXVECTOR2 getCenterPoint(int side, RECT rect);
	RelativePosition leverPosition[4];
	RelativePosition trapTopRightPosition[4];
	void createMap();
	void createTrap();
	void assignDefaultPosition();
	void setLeverAndHole(int leverForWhichTrap);
};

