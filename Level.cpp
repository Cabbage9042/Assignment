#pragma once
#include "Level.h"
#include "Shell.h"


void Level::updateKeyStatus(bool keyDown, KeyStatus* key) {
	if (keyDown) {
		if (!key->isHolding)	key->isPressed = true;
		key->isHolding = true;
	}
	else {
		if (key->isHolding) {
			key->isReleased = true;
		}
		else {
			key->isReleased = false;
		}
		key->isPressed = false;
		key->isHolding = false;
	}
}

bool Level::rectIsEqual(RECT a, RECT b)
{
	return (
		a.left == b.left &&
		a.right == b.right &&
		a.top == b.top &&
		a.bottom == b.bottom
		);
}

void Level::InitializeLevel() {
	textures = new vector<Texture*>;
	texts = new vector<Text*>;
	sprites = new vector<Sprite*>;

	//for (int i = 576; i >= 0; i -= 32) {
	//	Shell::CreateTexture("Assets/button.png", textures, 459, 96, D3DXVECTOR2(MyWindowWidth / 2, 72 +i), centerAlign);
	//}
	characterAnimationCounter = 0;

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
	GameManager::CreateSprite(sprites, "Assets/Level/character.png", textureWidth, textureHeight, spriteWidth, spriteHeight, spriteRow, spriteCol, currentColumn, currentRow, maxFrame, position);

	map.InitializeMap();

	sprites->at(character)->transformation.position.x = map.startPosition.x + (map.floorSprite.spriteWidth - sprites->at(character)->spriteWidth) / 2;
	sprites->at(character)->transformation.position.y = map.startPosition.y;
	sprites->at(character)->transformation.UpdateMatrix();
}

void Level::GetInput() {
	Shell::directXManager.dInputKeyboardDevice->Acquire();
	Shell::directXManager.dInputMouseDevice->Acquire();

	Shell::directXManager.dInputKeyboardDevice->GetDeviceState(256, Shell::directXManager.diKeys);
	Shell::directXManager.dInputMouseDevice->GetDeviceState(sizeof(Shell::directXManager.mouseState), &Shell::directXManager.mouseState);



	if (KeyDown(DIK_LALT) || KeyDown(DIK_RALT)) {
		if (!altKey.isHolding)	altKey.isPressed = true;
		altKey.isHolding = true;
	}
	else {
		altKey.isHolding = false;
	}
	if (KeyDown(DIK_F4)) {
		if (!f4Key.isHolding)	f4Key.isPressed = true;
		f4Key.isHolding = true;
	}

	if (KeyDown(DIK_DOWN)) {
		if (!downKey.isHolding)	downKey.isPressed = true;
		downKey.isHolding = true;
	}
	updateKeyStatus(KeyDown(DIK_W), &wKey);
	updateKeyStatus(KeyDown(DIK_A), &aKey);
	updateKeyStatus(KeyDown(DIK_S), &sKey);
	updateKeyStatus(KeyDown(DIK_D), &dKey);

}

void Level::Update(int framesToUpdate) {

	if ((altKey.isHolding && f4Key.isHolding)) {
		PostQuitMessage(0);
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
		characterAnimationCounter++;
		if (wKey.isHolding) {
			characterIsMoving = true;
			sprites->at(character)->currentRow = walkingUp;
			sprites->at(character)->transformation.position.y -= Character::velocity;
		}
		if (aKey.isHolding) {
			characterIsMoving = true;
			sprites->at(character)->currentRow = walkingLeft;
			sprites->at(character)->transformation.position.x -= Character::velocity;
		}
		if (sKey.isHolding) {
			characterIsMoving = true;
			sprites->at(character)->currentRow = walkingDown;
			sprites->at(character)->transformation.position.y += Character::velocity;
		}
		if (dKey.isHolding) {
			characterIsMoving = true;
			sprites->at(character)->currentRow = walkingRight;
			sprites->at(character)->transformation.position.x += Character::velocity;
		}

		sprites->at(character)->updatePositionRect();
		//cout << "top " << sprites->at(character)->positionRect.top;
		//cout << "bottom " << sprites->at(character)->positionRect.bottom;
		//cout << "left " << sprites->at(character)->positionRect.left;
		//cout << "right " << sprites->at(character)->positionRect.right<<endl;

		//collision check
		int collidedXAxis;
		int collidedYAxis;
		if (map.collidedToWall(*sprites->at(character), &characterCollidedStatus, &collidedXAxis, &collidedYAxis)) {
			//cout << "side " << collidedWallSide << " axis " << collidedAxis << endl;
			if (!rectIsEqual(characterCollidedStatus.bottomCollided, RECT())) {
				cout << 1;
				sprites->at(character)->transformation.position.y = collidedYAxis;
			}
			if (!rectIsEqual(characterCollidedStatus.topCollided, RECT())) {
				cout << 2;
				sprites->at(character)->transformation.position.y = collidedYAxis - sprites->at(character)->spriteHeight;
			}
			if (!rectIsEqual(characterCollidedStatus.leftCollided, RECT())) {
				cout << 3;
				sprites->at(character)->transformation.position.x = collidedXAxis;
			}
			if (!rectIsEqual(characterCollidedStatus.rightCollided, RECT())) {
				cout << 4;
				sprites->at(character)->transformation.position.x = collidedXAxis - sprites->at(character)->spriteWidth;
			}
			cout << endl;
		}


		// if not moving, character dont move; else move in speed of 10fps
		if (!characterIsMoving) {
			characterAnimationCounter = 0;
			sprites->at(character)->currentColumn = 0;
		}
		else {
			if (characterAnimationCounter % (gameFPS / characterFPS) == 0) {
				sprites->at(character)->currentColumn++;
				if (sprites->at(character)->currentColumn == sprites->at(character)->maxFrame) {
					sprites->at(character)->currentColumn = 0;
				}
			}
		}

		characterCollidedStatus.bottomCollided = characterCollidedStatus.leftCollided =
			characterCollidedStatus.rightCollided = characterCollidedStatus.topCollided = RECT();
		characterIsMoving = false;
		sprites->at(character)->updatePositionRect();
		sprites->at(character)->transformation.UpdateMatrix();
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

