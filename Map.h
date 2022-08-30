#pragma once
#include "Cell.h"
#include <vector>
#include "Sprite.h"

struct RectCollidedStatus {
	RECT topCollided = RECT();
	RECT leftCollided = RECT();
	RECT bottomCollided = RECT();
	RECT rightCollided = RECT();
};

enum { bottomSide, topSide, leftSide, rightSide};

class Map {
public:
	D3DXVECTOR2 topLeftCorner;	// included wall
	Sprite floorSprite;
	int numberOfCellRow;		// included wall
	int numberOfCellColumn;		// included wall
	vector<vector<Cell*> > cells; //is a wall, a floor or void. "W", "F", "V"
	D3DXVECTOR2 startPosition;
	D3DXVECTOR2 endPosition;

	void InitializeMap();
	void UninitializeMap();
	void RenderMap();
	bool collidedToWall(Sprite character, RectCollidedStatus* characterCollidedStatus,int *collidedXAxis,int *collidedYAxis);


private:
	char getCellType(int row, int col);
	bool isCollided(RECT a, RECT b);
	D3DXVECTOR2 getCenterPoint(int side, RECT rect);

};

