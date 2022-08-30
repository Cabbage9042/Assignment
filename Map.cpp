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
	numberOfCellRow = numberOfCellColumn = 18;
	int cellWidth = 32, cellHeight = 32;
	//topLeftCorner = D3DXVECTOR2(
	//	(MyWindowWidth / 2) - (cellWidth * numberOfCellColumn / 2),
	//	(MyWindowHeight / 2) - (cellHeight * numberOfCellRow / 2));
	topLeftCorner = D3DXVECTOR2(
		(MyWindowWidth / 2) - (cellWidth * numberOfCellColumn / 2),
		(MyWindowHeight / 2) - (cellHeight * numberOfCellRow / 2));

	floorSprite = Sprite("Assets/Level/floor.png", 160, 64, 32, 32, 2, 5, 0, 0, 9, D3DXVECTOR2(0, 0));
	floorSprite.updateCropRect();

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
				GameManager::randomNumber(0,5), GameManager::randomNumber(0, 2),
				charCellType, cellPositionRect));
			if (charCellType == 'S') {

				startPosition.x = topLeftCorner.x + (column * floorSprite.spriteWidth);
				startPosition.y = topLeftCorner.y + (row * floorSprite.spriteHeight);

			}

		}
	}
}

void Map::UninitializeMap() {
	floorSprite.Release();

	for (int row = cells.size() - 1; row >= 0; row--) {
		for (int col = cells.back().size() - 1; col >= 0; col--) {
			delete cells.back().back();
			cells.back().at(col) = NULL;
			cells.back().pop_back();
			cells.back().shrink_to_fit();
		}
		//vector<Cell*>().swap(cells.at(row));
		cells.pop_back();
	}

}

void Map::RenderMap() {

	for (int row = 0; row < numberOfCellRow; row++) {
		for (int col = 0; col < numberOfCellColumn; col++) {
			floorSprite.transformation.position =
				D3DXVECTOR2(topLeftCorner.x + (col * floorSprite.spriteWidth),
					topLeftCorner.y + (row * floorSprite.spriteHeight)
				);

			floorSprite.transformation.UpdateMatrix();
			if (cells.at(row).at(col)->type == 'V') continue;
			if (cells.at(row).at(col)->type == 'W') floorSprite.color = D3DCOLOR_XRGB(255 / 2, 255 / 2, 255 / 2);
			else floorSprite.color = D3DCOLOR_XRGB(255, 255, 255);

			floorSprite.currentColumn = cells.at(row).at(col)->nthColumn;
			floorSprite.currentRow = cells.at(row).at(col)->nthRow;
			floorSprite.updateCropRect();
			Shell::directXManager.spriteBrush->SetTransform(&floorSprite.transformation.matrix);
			Shell::directXManager.spriteBrush->Draw(floorSprite.texture, &floorSprite.cropRect, NULL, NULL, floorSprite.color);
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
					characterCollidedStatus->bottomCollided = cells.at(row).at(col)->positionRect;
					*collidedYAxis = cells.at(row).at(col)->positionRect.bottom;

				}
				if (character.isHoverOn(cells.at(row).at(col)->positionRect,
					getCenterPoint(bottomSide, character.positionRect))) {
					characterCollidedStatus->topCollided = cells.at(row).at(col)->positionRect;
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
