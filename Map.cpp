#include "Map.h"
#include "Shell.h"

char Map::getCellType(int row, int col) {
	if (row >= 6 && row <= 11 && col >= 7 && col <= 10) return 'V';
	else if (row == 0 || row == numberOfCellRow - 1 ||		//first and last row
		col == 0 || col == numberOfCellColumn - 1 ||		//first and last column
		((row >= 5 && row <= 12) &&							//wall in center row
			(col >= 6 && col <= 11)) ||							//wall in center column
		(row <= 4 && col == numberOfCellColumn / 2 - 1))			//wall that define start and end
		return 'W';
	else if (row == 1 && col == numberOfCellColumn / 2)
		return 'S';
	else if (row == 1 && col == numberOfCellColumn / 2 - 2) return 'E';

	else return 'F';
}

bool Map::isCollided(RECT a, RECT b) {

	bool collided = true;
	if (a.bottom < b.top) {
		collided = false;
	}if (a.top > b.bottom) {
		collided = false;
	}if (a.right < b.left) {
		collided = false;
	}if (a.left > b.right) {
		collided = false;
	}

	//cout << collided << endl;
	return collided;

}


void Map::setLeverAndHole(int leverForWhichTrap) {
	int col = traps[leverForWhichTrap].lever.nthColumn;
	int row = traps[leverForWhichTrap].lever.nthRow;


	switch (leverForWhichTrap) {
	case topRight:
		traps[leverForWhichTrap].lever.positionRect.top = cells.at(row).at(col)->positionRect.top;
		traps[leverForWhichTrap].lever.positionRect.left = cells.at(row).at(col)->positionRect.left;
		traps[leverForWhichTrap].lever.positionRect.right = cells.at(row).at(col)->positionRect.right;
		traps[leverForWhichTrap].lever.positionRect.bottom = cells.at(row).at(col)->positionRect.bottom -
			floorSprite.spriteHeight / 2;
		setHoleTo('V', traps[leverForWhichTrap].trapBottomRightPosition.row,
			traps[leverForWhichTrap].trapBottomRightPosition.col + 1);

		break;
	case bottomRight:
		traps[leverForWhichTrap].lever.positionRect.top = cells.at(row).at(col)->positionRect.top;
		traps[leverForWhichTrap].lever.positionRect.left = cells.at(row).at(col)->positionRect.left +
			floorSprite.spriteWidth / 2;;
		traps[leverForWhichTrap].lever.positionRect.right = cells.at(row).at(col)->positionRect.right;
		traps[leverForWhichTrap].lever.positionRect.bottom = cells.at(row).at(col)->positionRect.bottom;


		setHoleTo('V', traps[leverForWhichTrap].trapBottomRightPosition.row,
			traps[leverForWhichTrap].trapBottomRightPosition.col + 1);
		break;
	case bottomLeft:
		traps[leverForWhichTrap].lever.positionRect.top = cells.at(row).at(col)->positionRect.top +
			floorSprite.spriteHeight / 2;
		traps[leverForWhichTrap].lever.positionRect.left = cells.at(row).at(col)->positionRect.left;
		traps[leverForWhichTrap].lever.positionRect.right = cells.at(row).at(col)->positionRect.right;
		traps[leverForWhichTrap].lever.positionRect.bottom = cells.at(row).at(col)->positionRect.bottom;

		setHoleTo('V', traps[leverForWhichTrap].trapBottomRightPosition.row,
			traps[leverForWhichTrap].trapBottomRightPosition.col - 5);
		break;

	case topLeft:
		traps[leverForWhichTrap].lever.positionRect.top = cells.at(row).at(col)->positionRect.top;
		traps[leverForWhichTrap].lever.positionRect.left = cells.at(row).at(col)->positionRect.left;
		traps[leverForWhichTrap].lever.positionRect.right = cells.at(row).at(col)->positionRect.right -
			floorSprite.spriteWidth / 2;
		traps[leverForWhichTrap].lever.positionRect.bottom = cells.at(row).at(col)->positionRect.bottom;



		setHoleTo('V', traps[leverForWhichTrap].trapBottomRightPosition.row,
			traps[leverForWhichTrap].trapBottomRightPosition.col - 5);
		break;
	}
}

void Map::createMap() {
	char charCellType;
	RECT cellPositionRect;

	for (int row = 0; row < numberOfCellRow; row++) {
		cells.push_back(vector<Cell*>());
		for (int column = 0; column < numberOfCellColumn; column++) {
			charCellType = getCellType(row, column);


			cellPositionRect.top = topLeftCorner.y + (row * floorSprite.spriteHeight);
			cellPositionRect.bottom = cellPositionRect.top + floorSprite.spriteHeight;
			cellPositionRect.left = topLeftCorner.x + (column * floorSprite.spriteWidth);
			cellPositionRect.right = cellPositionRect.left + floorSprite.spriteWidth;


			cells.back().push_back(new Cell(
				GameManager::randomNumber(0, 5), GameManager::randomNumber(0, 2),
				charCellType, cellPositionRect));
			if (charCellType == 'S') {
				startPosition.x = topLeftCorner.x + (column * floorSprite.spriteWidth);
				startPosition.y = topLeftCorner.y + (row * floorSprite.spriteHeight);

			}
			else if (charCellType == 'E') {
				goalRect = cellPositionRect;
			}

		}
	}

}

void Map::createTrap() {
	int createdTrapCount = 0;
	for (int i = 0; i < 4; i++) {
		traps[i].isSet = GameManager::randomNumber(0, 2);
		//traps[i].isSet = true;
		if (i == 3 && createdTrapCount == 0) traps[i].isSet = true;
		if (!traps[i].isSet) continue; else createdTrapCount++;

		traps[i].lever.nthColumn = leverPosition[i].col;
		traps[i].lever.nthRow = leverPosition[i].row;
		traps[i].trapBottomRightPosition = trapBottomRightPosition[i];

		//positionRect
		traps[i].positionRect.right = topLeftCorner.x + (floorSprite.spriteWidth * (traps[i].trapBottomRightPosition.col + 1)) - 1;
		traps[i].positionRect.bottom = topLeftCorner.y + (floorSprite.spriteHeight * (traps[i].trapBottomRightPosition.row + 1)) - 1;
		traps[i].positionRect.left = topLeftCorner.x + (floorSprite.spriteWidth * (traps[i].trapBottomRightPosition.col - 4));
		traps[i].positionRect.top = topLeftCorner.y + (floorSprite.spriteHeight * (traps[i].trapBottomRightPosition.row - 3));

		switch (i) {
		case topRight:
		case bottomRight:
			traps[i].positionBetweenWalls.x = topLeftCorner.x + ((traps[i].trapBottomRightPosition.col + 1) * floorSprite.spriteWidth);
			traps[i].positionBetweenWalls.y = topLeftCorner.y + ((traps[i].trapBottomRightPosition.row - 1) * floorSprite.spriteHeight);
			break;
		default:
			traps[i].positionBetweenWalls.x = topLeftCorner.x + ((traps[i].trapBottomRightPosition.col - 5) * floorSprite.spriteWidth);
			traps[i].positionBetweenWalls.y = topLeftCorner.y + ((traps[i].trapBottomRightPosition.row - 2) * floorSprite.spriteHeight);
			break;
		}
		setLeverAndHole(i);

		setTrapTo('T', traps[i].trapBottomRightPosition);


	}
}

void Map::assignDefaultPosition() {
	leverPosition[topRight].col = 10;
	leverPosition[topRight].row = 1;

	leverPosition[bottomRight].col = 16;
	leverPosition[bottomRight].row = 11;

	leverPosition[bottomLeft].col = 7;
	leverPosition[bottomLeft].row = 16;

	leverPosition[topLeft].col = 1;
	leverPosition[topLeft].row = 6;

	trapBottomRightPosition[topRight].col = 16;
	trapBottomRightPosition[topRight].row = 4;

	trapBottomRightPosition[bottomRight].col = 16;
	trapBottomRightPosition[bottomRight].row = 16;

	trapBottomRightPosition[bottomLeft].col = 5;
	trapBottomRightPosition[bottomLeft].row = 16;

	trapBottomRightPosition[topLeft].col = 5;
	trapBottomRightPosition[topLeft].row = 4;



}

void Map::setHoleTo(char type, int mostBelowRow, int col, int numberOfBlockToChange) {
	for (int j = mostBelowRow; j >= mostBelowRow - numberOfBlockToChange + 1; j--)
		cells.at(j).at(col)->type = type;
}





D3DXVECTOR2 Map::getCenterPoint(int side, RECT rect) {
	D3DXVECTOR2 tempPosition;
	switch (side) {
	case topSide: tempPosition.x = rect.right - ((rect.right - rect.left) / 2);
		tempPosition.y = rect.top;
		break;
	case bottomSide: tempPosition.x = rect.right - ((rect.right - rect.left) / 2);
		tempPosition.y = rect.bottom;
		break;
	case leftSide: tempPosition.y = rect.bottom - ((rect.bottom - rect.top) / 2);
		tempPosition.x = rect.left;
		break;
	case rightSide: tempPosition.y = rect.bottom - ((rect.bottom - rect.top) / 2);
		tempPosition.x = rect.right;
		break;
	}
	return tempPosition;
}





void Map::InitializeMap() {
	assignDefaultPosition();

	numberOfCellRow = numberOfCellColumn = 18;
	int cellWidth = 32, cellHeight = 32;
	//topLeftCorner = D3DXVECTOR2(
	//	(MyWindowWidth / 2) - (cellWidth * numberOfCellColumn / 2),
	//	(MyWindowHeight / 2) - (cellHeight * numberOfCellRow / 2));
	topLeftCorner = D3DXVECTOR2(
		(MyWindowWidth / 2) - (cellWidth * numberOfCellColumn / 2),
		(MyWindowHeight / 2) - (cellHeight * numberOfCellRow / 2));

	floorSprite = Sprite("Assets/Level/floor.png", 160, 64, 32, 32, 2, 5, 0, 0, 9, D3DXVECTOR2(0, 0));

	lever = Texture("Assets/Level/lever.png", 32, 32, D3DXVECTOR2(0, 0));
	lever.transformation.rotationCenter = D3DXVECTOR2(lever.textureWidth / 2, lever.textureHeight / 2);
	lever.transformation.scalingCenter = lever.transformation.rotationCenter;

	createMap();

	createTrap();


}


//bool Map::collidedToAndFacingLever(Sprite* character, int* leverForWhichTrap)
//{
//	if (!collidedToLever(character, leverForWhichTrap)) return false;
//	switch (*leverForWhichTrap) {
//	case topRight: return character->currentRow == walkingUp;
//	case bottomRight: return character->currentRow == walkingRight;
//	case bottomLeft: return character->currentRow == walkingDown;
//	case topLeft: return character->currentRow == walkingLeft;
//	default: return false;
//	}
//}


void Map::UninitializeMap() {
	floorSprite.Release();

	for (int row = cells.size() - 1; row >= 0; row--) {
		for (int col = cells.back().size() - 1; col >= 0; col--) {
			delete cells.back().back();
			cells.back().at(col) = NULL;
			cells.back().pop_back();
			cells.back().shrink_to_fit();
		}
		cells.pop_back();
		cells.shrink_to_fit();
	}

	lever.Release();

}

void Map::RenderMap() {

	for (int row = 0; row < numberOfCellRow; row++) {
		for (int col = 0; col < numberOfCellColumn; col++) {
			floorSprite.transformation.position =
				D3DXVECTOR2(topLeftCorner.x + (col * floorSprite.spriteWidth),
					topLeftCorner.y + (row * floorSprite.spriteHeight));

			floorSprite.transformation.UpdateMatrix();

			switch (cells.at(row).at(col)->type) {
			case 'V': continue;
			case 'W': floorSprite.color = D3DCOLOR_XRGB(255 / 2, 255 / 2, 255 / 2); break;
			case 'S':floorSprite.color = D3DCOLOR_XRGB(255, 0, 0); break;
			case 'E': floorSprite.color = D3DCOLOR_XRGB(0, 255, 0); break;
			case 'T': floorSprite.color = D3DCOLOR_XRGB(255, 165, 0); break;
			default: floorSprite.color = D3DCOLOR_XRGB(255, 255, 255); break;
			}

			floorSprite.currentColumn = cells.at(row).at(col)->nthColumn;
			floorSprite.currentRow = cells.at(row).at(col)->nthRow;

			floorSprite.Draw();

			/*Lever*/
			for (int leverLoop = 0; leverLoop < 4; leverLoop++) {
				if (!traps[leverLoop].isSet) continue;
				if (traps[leverLoop].lever.nthRow == row && traps[leverLoop].lever.nthColumn == col) {
					lever.transformation.position.x = cells.at(row).at(col)->positionRect.left;
					lever.transformation.position.y = cells.at(row).at(col)->positionRect.top;
					lever.transformation.rotation = leverLoop * 90 * PI / 180;

					if (traps[leverLoop].lever.hasTurnedOn) {
						lever.transformation.scaling = D3DXVECTOR2(-1, 1);
					}
					else {
						lever.transformation.scaling = D3DXVECTOR2(1, 1);
					}

					lever.transformation.UpdateMatrix();
					lever.Draw();
					break;
				}
			}

		}
	}

}

bool Map::collidedToWall(Sprite character, RectCollidedStatus* characterCollidedStatus, int* collidedXAxis, int* collidedYAxis)
{
	bool result = false;
	for (int row = 0; row < numberOfCellRow; row++) {
		for (int col = 0; col < numberOfCellColumn; col++) {
			if (cells.at(row).at(col)->type != 'W') {
				continue;
			}
			if (isCollided(character.positionRect, cells.at(row).at(col)->positionRect)) {
				// character is below wall
				result = true;
				if (character.isHoverOn(cells.at(row).at(col)->positionRect,
					getCenterPoint(topSide, character.positionRect))) {
					characterCollidedStatus->topCollided = cells.at(row).at(col)->positionRect;
					*collidedYAxis = cells.at(row).at(col)->positionRect.bottom;

				}
				if (character.isHoverOn(cells.at(row).at(col)->positionRect,
					getCenterPoint(bottomSide, character.positionRect))) {
					characterCollidedStatus->bottomCollided = cells.at(row).at(col)->positionRect;
					*collidedYAxis = cells.at(row).at(col)->positionRect.top;
				}
				//character is at left of the wall
				if (character.isHoverOn(cells.at(row).at(col)->positionRect,
					getCenterPoint(rightSide, character.positionRect))) {
					characterCollidedStatus->rightCollided = cells.at(row).at(col)->positionRect;
					*collidedXAxis = cells.at(row).at(col)->positionRect.left;
				}
				if (character.isHoverOn(cells.at(row).at(col)->positionRect,
					getCenterPoint(leftSide, character.positionRect))) {
					characterCollidedStatus->leftCollided = cells.at(row).at(col)->positionRect;
					*collidedXAxis = cells.at(row).at(col)->positionRect.right;
				}
				/*if (character.positionRect.bottom > cells.at(row).at(col).positionRect.top) {
					*collidedWallSide = topSide;
					*collidedAxis = cells.at(row).at(col).positionRect.top;
					return true;
				}if (character.positionRect.right > cells.at(row).at(col).positionRect.left) {
					*collidedWallSide = leftSide;
					*collidedAxis = cells.at(row).at(col).positionRect.left;
					return true;
				}if (character.positionRect.left < cells.at(row).at(col).positionRect.right) {
					*collidedWallSide = rightSide;
					*collidedAxis = cells.at(row).at(col).positionRect.right;
					return true;
				}*/
			}
		}
	}
	return result;
}

void Map::setTrapTo(char type, RelativePosition topRightPosition) {
	for (int j = topRightPosition.row;
		j >= topRightPosition.row - 3; j--) {
		for (int k = topRightPosition.col;
			k >= topRightPosition.col - 4; k--) {

			cells.at(j).at(k)->type = type;
		}
	}
}

bool Map::collidedToGoal(Sprite* character) {
	return character->isHoverOn(goalRect, character->transformation.position + character->transformation.rotationCenter);
}


bool Map::collidedToLever(Sprite* character, int* leverForWhichTrap) {
	for (int i = 0; i <= 3; i++) {
		if (!traps[i].isSet) continue;
		if (isCollided(character->positionRect, traps[i].lever.positionRect)) {
			*leverForWhichTrap = i;
			return true;
		}
	}
	return false;
}

bool Map::collidedToTrap(Sprite* character, int* collidedTrap) {
	for (int i = 0; i <= 3; i++) {
		if (!traps[i].isSet) continue;
		if (isCollided(character->positionRect, traps[i].positionRect)) {
			*collidedTrap = i;
			return true;
		}


	}
	return false;
}