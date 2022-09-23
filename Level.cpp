#pragma once
#include "Level.h"
#include "Shell.h"

void Level::InitializeLevel() {
	textures = new vector<Texture*>;
	texts = new vector<Text*>;
	sprites = new vector<Sprite*>;
	lines = new vector<Line*>;
	audios = new vector<Audio*>;

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
	character.sprite.transformation.scalingCenter = character.sprite.transformation.rotationCenter = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);

	map.InitializeMap();

	character.sprite.setPositionX( map.startPosition.x + (map.floorSprite.spriteWidth - character.sprite.spriteWidth) / 2);
	character.sprite.setPositionY( map.startPosition.y);
	

	//audio
	audios->push_back(new Audio("Assets/button.mp3", effectGroup));
	audios->at(button)->setLoop(false);

	audios->push_back(new Audio("Assets/Level/background1.mp3", bgmGroup, AUDIO_CREATE_STREAM));
	audios->at(bgm)->setLoop(true);

	audios->push_back(new Audio("Assets/Level/lever.mp3", effectGroup));
	audios->at(lever)->setLoop(false);

	audios->push_back(new Audio("Assets/Level/walking.mp3", effectGroup));
	audios->at(walking)->setLoop(true);

	audios->push_back(new Audio("Assets/Level/scream.mp3", effectGroup));
	audios->at(scream)->setLoop(false);

	GameManager::playerHasWin = 0;
}

void Level::GetInput() {
	Shell::directXManager.dInputKeyboardDevice->Acquire();
	Shell::directXManager.dInputMouseDevice->Acquire();

	Shell::directXManager.dInputKeyboardDevice->GetDeviceState(256, Shell::directXManager.diKeys);
	Shell::directXManager.dInputMouseDevice->GetDeviceState(sizeof(Shell::directXManager.mouseState), &Shell::directXManager.mouseState);

	altKey.updateKeyStatus(KeyDown(DIK_LALT) || KeyDown(DIK_RALT));
	f4Key.updateKeyStatus(KeyDown(DIK_F4));
	escKey.updateKeyStatus(KeyDown(DIK_ESCAPE));
	downKey.updateKeyStatus(KeyDown(DIK_DOWN));
	wKey.updateKeyStatus(KeyDown(DIK_W));
	aKey.updateKeyStatus(KeyDown(DIK_A));
	sKey.updateKeyStatus(KeyDown(DIK_S));
	dKey.updateKeyStatus(KeyDown(DIK_D));

}

void Level::Update(int framesToUpdate) {
	if ((altKey.isHolding && f4Key.isHolding)) {
		PostQuitMessage(0);
		return;
	}
	if (escKey.isPressed) {
		GameManager::levelVector->push_back(new Pause());
		GameManager::levelVector->back()->InitializeLevel();
		return;
	}


	//if character is losing
	if (GameManager::playerHasWin == -1) {
		//if character enter the trap, do fly outside space ship
		if (isEnteredTrap && !map.traps[collidedTrap].lever.hasTurnedOn) {

			character.velocity = character.vectorBetweenHole;
			character.sprite.addPosition(character.velocity);
			character.sprite.transformation.rotation += 0.1;

			//go to game over if character out of window
			if (character.sprite.getPosition().y <0
				|| character.sprite.getPosition().y > MyWindowHeight
				|| character.sprite.getPosition().x <0
				|| character.sprite.getPosition().x > MyWindowWidth) {

				//stop scream
				audios->at(scream)->stop();

				//uninitialize level
				GameManager::levelVector->back()->UninitializeLevel();
				delete GameManager::levelVector->back();
				GameManager::levelVector->back() = NULL;
				GameManager::levelVector->pop_back();
				GameManager::levelVector->shrink_to_fit();

				//init gameover
				GameManager::levelVector->push_back(new GameOver());
				GameManager::levelVector->back()->InitializeLevel();


				return;
			}

			//audio
			audios->at(walking)->stop();
			isPlayingWalkingSound = false;

			if (!isPlayingScreamSound) {
				audios->at(scream)->play();
				isPlayingScreamSound = true;
			}

			audios->at(scream)->channel->setVolume(screamVolume);
			screamVolume -= 0.0015;
			if (screamVolume < 0) {
				screamVolume = 0;
			}
			audios->at(scream)->channel->setPan(calculatePan());




			Shell::audioManager.updateSound();

			return;
		}
	}

	for (int i = 0; i < framesToUpdate; i++) {

		characterMovingStatus();

		character.sprite.updatePositionRect();

		//collision check
		updateCharacterCollidedToWall();

		//goal or not (if win)
		if (map.collidedToGoal(&character.sprite)) {
			//uninitialize level
			GameManager::levelVector->back()->UninitializeLevel();
			delete GameManager::levelVector->back();
			GameManager::levelVector->back() = NULL;
			GameManager::levelVector->pop_back();
			GameManager::levelVector->shrink_to_fit();

			//init victory
			GameManager::levelVector->push_back(new Victory());
			GameManager::levelVector->back()->InitializeLevel();
			return;
		}

		//touch lever or not
		updateTrapStatus();

		enterTrapChecking();

		// if not moving, character dont move; else move in speed of 10fps
		updateCharacterAnimation();

		character.characterCollidedStatus.topCollided = character.characterCollidedStatus.leftCollided =
			character.characterCollidedStatus.rightCollided = character.characterCollidedStatus.bottomCollided = RECT();
		character.characterIsMoving = false;
		character.sprite.updatePositionRect();

		//audio
		if (startBGM) {
			audios->at(bgm)->play();
			startBGM = false;
		}
		Shell::audioManager.updateSound();
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
	Line::DrawLines(lines);

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
	GameManager::ReleaseLines(lines);
	GameManager::ReleaseAudios(audios);
}

void Level::updateCharacterCollidedToWall()
{
	if (map.collidedToWall(character.sprite, &character.characterCollidedStatus, &collidedXAxis, &collidedYAxis)) {
		//cout << "side " << collidedWallSide << " axis " << collidedAxis << endl;
		if (!GameManager::rectIsEqual(character.characterCollidedStatus.topCollided, RECT())) {
			//cout << 1;
			character.sprite.setPositionY(collidedYAxis);
		}
		if (!GameManager::rectIsEqual(character.characterCollidedStatus.bottomCollided, RECT())) {
			//cout << 2;
			character.sprite.setPositionY(collidedYAxis - character.sprite.spriteHeight);
		}
		if (!GameManager::rectIsEqual(character.characterCollidedStatus.leftCollided, RECT())) {
			//cout << 3;
			character.sprite.setPositionX( collidedXAxis);
		}
		if (!GameManager::rectIsEqual(character.characterCollidedStatus.rightCollided, RECT())) {
			//cout << 4;
			character.sprite.setPositionX(collidedXAxis - character.sprite.spriteWidth);
		}
		//cout << endl;
	}
}

void Level::updateTrapStatus() {
	if (map.collidedToLever(&character.sprite, &leverForWhichTrap)) {

		//play lever sound effect
		if (map.traps[leverForWhichTrap].lever.hasTurnedOn == false) {
			audios->at(lever)->play();
		}

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

void Level::characterMovingStatus()
{
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
		character.sprite.addPosition(character.velocity);
		if (!wKey.isHolding && !sKey.isHolding) character.velocity.y = 0;
		if (!aKey.isHolding && !dKey.isHolding) character.velocity.x = 0;

		//audio
		if (isPlayingWalkingSound == false) {
			audios->at(walking)->play();
			isPlayingWalkingSound = true;
		}

		//calculate and set pan (left right track)
		audios->at(walking)->channel->setPan(calculatePan());


	}
	else {
		character.velocity = D3DXVECTOR2(0, 0);

		//audio
		if (isPlayingWalkingSound) {
			audios->at(walking)->stop();
			isPlayingWalkingSound = false;
		}
	}
}

void Level::enterTrapChecking() {

	//if character enter into a trap
	if (map.collidedToTrap(&character.sprite, &collidedTrap)) {
		isEnteredTrap = true;
		character.vectorBetweenHole = map.traps[collidedTrap].positionBetweenWalls - character.sprite.getPosition(); // distance between character and hole

		//shorten the distance so that the velocity of flying out is not too fast
		while (D3DXVec2LengthSq(&character.vectorBetweenHole) >= 30) {
			character.vectorBetweenHole *= 0.9;
		}

		GameManager::playerHasWin = -1;




	}
}

float Level::calculatePan() {
	return -(MyWindowWidth / 2 - character.sprite.getPosition().x) / (MyWindowWidth / 4);
}



void Level::updateCharacterAnimation() {
	character.characterAnimationCounter++;
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

