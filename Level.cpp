#pragma once
#include "Level.h"
#include "Shell.h"

void Level::InitializeLevel() {
	textures = new vector<Texture*>;
	texts = new vector<Text*>;
	sprites = new vector<Sprite*>;

	//for (int i = 576; i >= 0; i -= 32) {
	//	Shell::CreateTexture("Assets/button.png", textures, 459, 96, D3DXVECTOR2(MyWindowWidth / 2, 72 +i), centerAlign);
	//}

	int textureWidth = 76;
	int textureHeight = 128;
	int spriteRow = 4;
	int spriteCol = 4;
	int spriteWidth = textureWidth / spriteCol;
	int spriteHeight = textureHeight / spriteRow;
	int currentRow = 1;
	int currentColumn = 0;
	int maxFrame = 4;
	D3DXVECTOR2 position(0, 0);



	//last
	character.sprite = Sprite("Assets/Level/character.png", textureWidth, textureHeight, spriteWidth, spriteHeight, spriteRow, spriteCol, currentColumn, currentRow, maxFrame, position);

	map.InitializeMap();

	character.sprite.transformation.position.x = map.startPosition.x + (map.floorSprite.spriteWidth - character.sprite.spriteWidth) / 2;
	character.sprite.transformation.position.y = map.startPosition.y;
	character.sprite.transformation.UpdateMatrix();
}

void Level::GetInput() {
	Shell::directXManager.dInputKeyboardDevice->Acquire();
	Shell::directXManager.dInputMouseDevice->Acquire();

	Shell::directXManager.dInputKeyboardDevice->GetDeviceState(256, Shell::directXManager.diKeys);
	Shell::directXManager.dInputMouseDevice->GetDeviceState(sizeof(Shell::directXManager.mouseState), &Shell::directXManager.mouseState);

	GameManager::updateKeyStatus(KeyDown(DIK_LALT) || KeyDown(DIK_RALT), &altKey);
	GameManager::updateKeyStatus(KeyDown(DIK_F4), &f4Key);
	GameManager::updateKeyStatus(KeyDown(DIK_DOWN), &downKey);
	GameManager::updateKeyStatus(KeyDown(DIK_W), &wKey);
	GameManager::updateKeyStatus(KeyDown(DIK_A), &aKey);
	GameManager::updateKeyStatus(KeyDown(DIK_S), &sKey);
	GameManager::updateKeyStatus(KeyDown(DIK_D), &dKey);

}

void Level::Update(int framesToUpdate) {
	if ((altKey.isHolding && f4Key.isHolding)) {
		PostQuitMessage(0);
		return;
	}
	//if character enter the trap, do fly outside space ship
	if (isEnteredTrap && !map.traps[collidedTrap].lever.hasTurnedOn) {
			
		character.velocity = character.vectorBetweenHole;
		character.sprite.transformation.position += character.velocity;
		character.sprite.transformation.rotation += 0.1;
		
		character.distanceBetweenHole = D3DXVec2LengthSq(&character.vectorBetweenHole);

		cout << character.vectorBetweenHole.x << " " << character.vectorBetweenHole.y << " " << character.distanceBetweenHole << endl;
	
		if (character.sprite.transformation.position.y <0 || character.sprite.transformation.position.y > MyWindowHeight
			|| character.sprite.transformation.position.x <0 || character.sprite.transformation.position.x > MyWindowWidth) {
			GameManager::levelVector->back()->UninitializeLevel();
			delete GameManager::levelVector->back();
			GameManager::levelVector->back() = NULL;
			GameManager::levelVector->pop_back();
			return;
		}
		character.sprite.transformation.UpdateMatrix();
		return;
	}


	if (downKey.isPressed) {
		GameManager::levelVector->back()->UninitializeLevel();
		delete GameManager::levelVector->back();
		GameManager::levelVector->back() = NULL;
		GameManager::levelVector->pop_back();
		return;
	}

	//cout << "w p " << wKey.isPressed << "w h " << wKey.isHolding << " " << "w r " << wKey.isReleased;
	//cout << "a p " << aKey.isPressed << "a h " << aKey.isHolding << " " << "a r " << aKey.isReleased;
	//cout << "s p " << sKey.isPressed << "s h " << sKey.isHolding << " " << "s r " << sKey.isReleased;
	//cout << "d p " << dKey.isPressed << "d h " << dKey.isHolding << " " << "d r" << dKey.isReleased << endl;


	//cout << framesToUpdate << endl;
	for (int i = 0; i < framesToUpdate; i++) {
		character.characterAnimationCounter++;
		if (wKey.isHolding) {
			character.characterIsMoving = true;
			character.sprite.currentRow = walkingUp;
			character.velocity.y = -DEFAULT_SPEED;
		}
		if (aKey.isHolding) {
			character.characterIsMoving = true;
			character.sprite.currentRow = walkingLeft;
			character.velocity.x = -DEFAULT_SPEED;
		}
		if (sKey.isHolding) {
			character.characterIsMoving = true;
			character.sprite.currentRow = walkingDown;
			character.velocity.y = DEFAULT_SPEED;
		}
		if (dKey.isHolding) {
			character.characterIsMoving = true;
			character.sprite.currentRow = walkingRight;
			character.velocity.x = DEFAULT_SPEED;
		}
		if (character.characterIsMoving) {
			character.sprite.transformation.position += character.velocity;
			if (!wKey.isHolding && !sKey.isHolding) character.velocity.y = 0;
			if (!aKey.isHolding && !dKey.isHolding) character.velocity.x = 0;

		}
		else {
			character.velocity = D3DXVECTOR2(0, 0);
		}

		character.sprite.updatePositionRect();
		//cout << "top " << sprites->at(character)->positionRect.top;
		//cout << "bottom " << sprites->at(character)->positionRect.bottom;
		//cout << "left " << sprites->at(character)->positionRect.left;
		//cout << "right " << sprites->at(character)->positionRect.right<<endl;

		//collision check
		updateCharacterCollidedToWall();


		//touch lever or not
		updateTrapStatus();

		if (map.collidedToTrap(&character.sprite, &collidedTrap)) {
			isEnteredTrap = true;
			character.vectorBetweenHole = map.traps[collidedTrap].positionBetweenWalls - character.sprite.transformation.position;
			

			while (D3DXVec2LengthSq(&character.vectorBetweenHole) >= 30) {
				character.vectorBetweenHole *= 0.9;
			}
		}

		// if not moving, character dont move; else move in speed of 10fps
		updateCharacterAnimation();




		character.characterCollidedStatus.bottomCollided = character.characterCollidedStatus.leftCollided =
			character.characterCollidedStatus.rightCollided = character.characterCollidedStatus.topCollided = RECT();
		character.characterIsMoving = false;
		character.sprite.updatePositionRect();
		character.sprite.transformation.UpdateMatrix();
	}



	altKey.isPressed = false;
	f4Key.isPressed = false;
	escKey.isPressed = false;
	wKey.isPressed = false;
	aKey.isPressed = false;
	sKey.isPressed = false;
	dKey.isPressed = false;
}

void Level::Render() {
	GameManager::RenderBegin();


	map.RenderMap();
	for (int i = textures->size() - 1; i >= 0; i--) {
		textures->at(i)->Draw();
	}

	for (int i = sprites->size() - 1; i >= 0; i--) {
		sprites->at(i)->updateCropRect();
		sprites->at(i)->Draw();
	}


	character.sprite.Draw();

	for (int i = texts->size() - 1; i >= 0; i--) {
		texts->at(i)->Draw();
	}

	//Shell::directXManager.spriteBrush->SetTransform(
	//	&sprites->at(pointer)->transformation.matrix
	//);
	//Shell::directXManager.spriteBrush->Draw(
	//	sprites->at(pointer)->texture,
	//	&sprites->at(pointer)->cropRect, NULL, NULL, sprites->at(pointer)->color);


	GameManager::RenderEnd();
}

void Level::UninitializeLevel() {
	map.UninitializeMap();
	GameManager::ReleaseTextures(textures);
	GameManager::ReleaseTexts(texts);
	GameManager::ReleaseSprite(sprites);
}

void Level::updateCharacterCollidedToWall()
{
	if (map.collidedToWall(character.sprite, &character.characterCollidedStatus, &collidedXAxis, &collidedYAxis)) {
		//cout << "side " << collidedWallSide << " axis " << collidedAxis << endl;
		if (!GameManager::rectIsEqual(character.characterCollidedStatus.bottomCollided, RECT())) {
			//cout << 1;
			character.sprite.transformation.position.y = collidedYAxis;
		}
		if (!GameManager::rectIsEqual(character.characterCollidedStatus.topCollided, RECT())) {
			//cout << 2;
			character.sprite.transformation.position.y = collidedYAxis - character.sprite.spriteHeight;
		}
		if (!GameManager::rectIsEqual(character.characterCollidedStatus.leftCollided, RECT())) {
			//cout << 3;
			character.sprite.transformation.position.x = collidedXAxis;
		}
		if (!GameManager::rectIsEqual(character.characterCollidedStatus.rightCollided, RECT())) {
			//cout << 4;
			character.sprite.transformation.position.x = collidedXAxis - character.sprite.spriteWidth;
		}
		//cout << endl;
	}
}

void Level::updateTrapStatus() {
	if (map.collidedToLever(&character.sprite, &leverForWhichTrap)) {

		map.traps[leverForWhichTrap].lever.hasTurnedOn = true;
		map.setTrapTo('F', map.traps[leverForWhichTrap].trapBottomRightPosition);
		switch (leverForWhichTrap) {
		case topRight:
		case bottomRight:
			map.setHoleTo('W', map.traps[leverForWhichTrap].trapBottomRightPosition.row,
				map.traps[leverForWhichTrap].trapBottomRightPosition.col + 1);
			break;
		default:
			map.setHoleTo('W', map.traps[leverForWhichTrap].trapBottomRightPosition.row,
				map.traps[leverForWhichTrap].trapBottomRightPosition.col - 5);
			break;
		}


	}
}

void Level::updateCharacterAnimation() {
	if (!character.characterIsMoving) {
		character.characterAnimationCounter = 0;
		character.sprite.currentColumn = 0;
	}
	else {
		if (character.characterAnimationCounter % (gameFPS / character.characterFPS) == 0) {
			character.sprite.currentColumn++;
			if (character.sprite.currentColumn == character.sprite.maxFrame) {
				character.sprite.currentColumn = 0;
			}
		}
	}
}

