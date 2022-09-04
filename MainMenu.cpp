#include "MainMenu.h"
#include "Shell.h"
#include "Level.h"



void MainMenu::InitializeLevel() {
	//must
	textures = new vector<Texture*>;
	texts = new vector<Text*>;
	sprites = new vector<Sprite*>;


	//button start
	GameManager::CreateTexture("Assets/button.png", textures, 459, 96, D3DXVECTOR2(MyWindowWidth / 2, MyWindowHeight / 2), centerAlign);


	//button quit
	GameManager::CreateTexture("Assets/button.png", textures, 459, 96, D3DXVECTOR2(MyWindowWidth / 2, (MyWindowHeight / 2) + 96 * 2), centerAlign);


	//text
	GameManager::CreateText(texts, "Walking on a spaceship", GameManager::fonts->at(franklin100), D3DXVECTOR2(MyWindowWidth / 2, MyWindowHeight / 5), centerAlign);
	GameManager::CreateText(texts, "Start", GameManager::fonts->at(arial25), D3DXVECTOR2(MyWindowWidth / 2, MyWindowHeight / 2 + 35), centerAlign);
	GameManager::CreateText(texts, "Quit", GameManager::fonts->at(arial25), D3DXVECTOR2(MyWindowWidth / 2, ((MyWindowHeight / 2) + 96 * 2) + 35), centerAlign);


	//must
	int textureWidth = 54;
	int textureHeight = 35;
	int spriteRow = 1;
	int spriteCol = 2;
	int spriteWidth = textureWidth / spriteCol;
	int spriteHeight = textureHeight / spriteRow;
	int currentColumn = 0;
	int currentRow = 0;
	int maxFrame = 1;
	GameManager::CreateSprite(sprites, "Assets/pointer.png", textureWidth, textureHeight, spriteWidth, spriteHeight,
		spriteRow, spriteCol, currentColumn, currentRow, maxFrame, D3DXVECTOR2(0, 0));

	textureWidth = 76;
	textureHeight = 128;
	spriteRow = 4;
	spriteCol = 4;
	spriteWidth = textureWidth / spriteCol;
	spriteHeight = textureHeight / spriteRow;
	currentRow = 3;
	currentColumn = 0;
	maxFrame = 4;
	D3DXVECTOR2 position(0, MyWindowHeight - spriteHeight);
	character.sprite = Sprite("Assets/Level/character.png", textureWidth, textureHeight, spriteWidth, spriteHeight, spriteRow, spriteCol, currentColumn, currentRow, maxFrame, position);
	character.sprite.transformation.scalingCenter = character.sprite.transformation.rotationCenter = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);


}


void MainMenu::GetInput() {

	//all must
	Shell::directXManager.dInputKeyboardDevice->Acquire();
	Shell::directXManager.dInputMouseDevice->Acquire();

	Shell::directXManager.dInputKeyboardDevice->GetDeviceState(256, Shell::directXManager.diKeys);
	Shell::directXManager.dInputMouseDevice->GetDeviceState(sizeof(Shell::directXManager.mouseState), &Shell::directXManager.mouseState);


	GameManager::updateKeyStatus(KeyDown(DIK_LALT) || KeyDown(DIK_RALT), &altKey);
	GameManager::updateKeyStatus(KeyDown(DIK_F4), &f4Key);
	GameManager::updateKeyStatus(ButtonDown(0), &leftButton);
	GameManager::updateKeyStatus(KeyDown(DIK_SPACE), &spaceKey);


	sprites->at(pointer)->transformation.position.x += Shell::directXManager.mouseState.lX;
	sprites->at(pointer)->transformation.position.y += Shell::directXManager.mouseState.lY;

}

void MainMenu::Update(int framesToUpdate) {

	//must
	if ((altKey.isHolding && f4Key.isHolding)) {
		PostQuitMessage(0);
		return;
	}

	//change parameter of isHoverOn to button u want
	pointerOnButton();

	if (spaceKey.isPressed && (character.sprite.positionRect.bottom == MyWindowHeight ||
		character.sprite.positionRect.bottom == textures->at(buttonStart)->positionRect.top ||
		character.sprite.positionRect.bottom == textures->at(buttonQuit)->positionRect.top)) {
		character.velocity.y = JumpForce;
	}
	for (int i = 0; i < framesToUpdate; i++) {
		//do animation if got

		if (character.sprite.positionRect.left <= 0) {
			character.sprite.currentRow = walkingRight;
			character.velocity.x = DEFAULT_SPEED;
		}
		else if (character.sprite.positionRect.right >= MyWindowWidth) {
			character.sprite.currentRow = walkingLeft;
			character.velocity.x = -DEFAULT_SPEED;
		}

		character.velocity.y += Gravity;
		character.sprite.transformation.position += character.velocity;

		character.sprite.updatePositionRect();


		if (character.sprite.positionRect.bottom >= MyWindowHeight) {
			character.sprite.transformation.position.y = MyWindowHeight - character.sprite.spriteHeight;
			character.velocity.y = 0;
		}
		else if (character.sprite.positionRect.right > textures->at(buttonQuit)->positionRect.left &&
			character.sprite.positionRect.left < textures->at(buttonQuit)->positionRect.right &&
			character.sprite.positionRect.bottom >  textures->at(buttonQuit)->positionRect.top &&
			character.sprite.positionRect.top <  textures->at(buttonQuit)->positionRect.top	) {
			character.sprite.transformation.position.y = textures->at(buttonQuit)->positionRect.top - character.sprite.spriteHeight;
			character.velocity.y = 0;
		}


		if (character.characterAnimationCounter % (gameFPS / character.characterFPS) == 0) {
			character.sprite.currentColumn++;
			if (character.sprite.currentColumn == character.sprite.maxFrame) {
				character.sprite.currentColumn = 0;
			}
		}

		character.sprite.updatePositionRect();
		character.sprite.transformation.UpdateMatrix();
	}

	//to avoid mouse out of window, must
	pointerStayInsideWindow();


	//must
	altKey.isPressed = false;
	f4Key.isPressed = false;
	leftButton.isPressed = false;
	spaceKey.isPressed = false;
}



//just copy and paste all
void MainMenu::Render() {

	GameManager::RenderBegin();
	for (int i = textures->size() - 1; i >= 0; i--) {
		textures->at(i)->Draw();
	}

	for (int i = sprites->size() - 1; i >= pointer + 1; i--) {
		sprites->at(i)->Draw();
	}

	for (int i = texts->size() - 1; i >= 0; i--) {
		texts->at(i)->Draw();
	}

	character.sprite.Draw();

	//pointer
	sprites->at(pointer)->Draw();
	//Shell::directXManager.spriteBrush->SetTransform(
	//	&sprites->at(pointer)->transformation.matrix
	//);
	//Shell::directXManager.spriteBrush->Draw(
	//	sprites->at(pointer)->texture,
	//	&sprites->at(pointer)->cropRect, NULL, NULL, sprites->at(pointer)->color);


	GameManager::RenderEnd();
}

//just copy and paste all
void MainMenu::UninitializeLevel() {
	character.sprite.Release();

	GameManager::ReleaseTextures(textures);
	GameManager::ReleaseTexts(texts);
	GameManager::ReleaseSprite(sprites);
}
void MainMenu::pointerStayInsideWindow()
{
	sprites->at(pointer)->updatePositionRect();
	if (sprites->at(pointer)->transformation.position.x < 0) {
		sprites->at(pointer)->transformation.position.x = 0;
	}
	if (sprites->at(pointer)->transformation.position.x > MyWindowWidth) {
		sprites->at(pointer)->transformation.position.x = MyWindowWidth - 1;
	}
	if (sprites->at(pointer)->transformation.position.y < 0) {
		sprites->at(pointer)->transformation.position.y = 0;
	}
	if (sprites->at(pointer)->transformation.position.y > MyWindowHeight) {
		sprites->at(pointer)->transformation.position.y = MyWindowHeight - 1;
	}
	sprites->at(pointer)->transformation.UpdateMatrix();
	sprites->at(pointer)->updateCropRect();
}

void MainMenu::pointerOnButton() {
	if (sprites->at(pointer)->isHoverOn(textures->at(buttonStart))) {
		//must
		sprites->at(pointer)->currentColumn = 1;

		if (leftButton.isPressed) {
			Level* level = new Level();
			level->InitializeLevel();
			GameManager::levelVector->push_back(level);
			level = NULL;

			character.sprite.transformation.position = D3DXVECTOR2(0, MyWindowHeight - character.sprite.spriteHeight);
			character.sprite.updatePositionRect();

			sprites->at(pointer)->transformation.position = D3DXVECTOR2(0, 0);
			sprites->at(pointer)->updatePositionRect();
		}
	}
	else if (sprites->at(pointer)->isHoverOn(textures->at(buttonQuit))) {

		sprites->at(pointer)->currentColumn = 1;
		if (leftButton.isPressed) {
			PostQuitMessage(0);
			return;
		}
	}
	//must
	else {
		sprites->at(pointer)->currentColumn = 0;
	}
}