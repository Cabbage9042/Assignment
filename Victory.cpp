#include "Victory.h"
#include "Shell.h"
#include "Level.h"
#include "MainMenu.h"



void Victory::InitializeLevel() {
	//must
	textures = new vector<Texture*>;
	texts = new vector<Text*>;
	sprites = new vector<Sprite*>;
	lines = new vector<Line*>;
	audios = new vector<Audio*>;

	//button start  ***
	GameManager::CreateTexture("Assets/nbutton.png", textures, 459, 96, D3DXVECTOR2(MyWindowWidth / 2, (MyWindowHeight / 2) - 48), centerAlign);


	//button quit  ***
	GameManager::CreateTexture("Assets/nbutton.png", textures, 459, 96, D3DXVECTOR2(MyWindowWidth / 2, (MyWindowHeight / 2) + 96), centerAlign);


	GameManager::CreateTexture("Assets/nbutton.png", textures, 459, 96, D3DXVECTOR2(MyWindowWidth / 2, (MyWindowHeight / 2) + 96 * 2.5), centerAlign);

	GameManager::CreateTexture("Assets/Victory/victory.png", textures, 420, 350, D3DXVECTOR2(MyWindowWidth / 2, (MyWindowHeight / 2) - 400), centerAlign);

	//text    ***

	GameManager::CreateText(texts, "Restart", GameManager::fonts->at(arial25), D3DXVECTOR2(MyWindowWidth / 2, MyWindowHeight / 2 + 35 - 48), centerAlign);
	GameManager::CreateText(texts, "Return Main Menu", GameManager::fonts->at(arial25), D3DXVECTOR2(MyWindowWidth / 2, ((MyWindowHeight / 2) + 96) + 35), centerAlign);
	GameManager::CreateText(texts, "Quit Game", GameManager::fonts->at(arial25), D3DXVECTOR2(MyWindowWidth / 2, ((MyWindowHeight / 2) + 96 * 2.5) + 35), centerAlign);

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

	//audio
	audios->push_back(new Audio("Assets/button.mp3", effectGroup));
	audios->at(button)->setLoop(false);

	audios->push_back(new Audio("Assets/Victory/victory.mp3", effectGroup));
	audios->at(victory)->setLoop(false);
	audios->at(victory)->play();

}

void Victory::GetInput() {

	//all must
	Shell::directXManager.dInputKeyboardDevice->Acquire();
	Shell::directXManager.dInputMouseDevice->Acquire();

	Shell::directXManager.dInputKeyboardDevice->GetDeviceState(256, Shell::directXManager.diKeys);
	Shell::directXManager.dInputMouseDevice->GetDeviceState(sizeof(Shell::directXManager.mouseState), &Shell::directXManager.mouseState);


	altKey.updateKeyStatus(KeyDown(DIK_LALT) || KeyDown(DIK_RALT));
	f4Key.updateKeyStatus(KeyDown(DIK_F4));
	leftButton.updateKeyStatus(ButtonDown(0));

	
	sprites->at(pointer)->addPosition(D3DXVECTOR2(Shell::directXManager.mouseState.lX, Shell::directXManager.mouseState.lY));

}

void Victory::Update(int framesToUpdate) {

	//must
	if ((altKey.isHolding && f4Key.isHolding)) {
		PostQuitMessage(0);
		return;
	}

	//change parameter of isHoverOn to button u want
	if (sprites->at(pointer)->isHoverOn(textures->at(VRestart))) {
		//must
		sprites->at(pointer)->currentColumn = 1;

		if (leftButton.isPressed) {
			GameManager::levelVector->at(0)->audios->at(button)->play();

			//remove all level in vector except for mainmanu, and push back level
			for (int i = GameManager::levelVector->size() - 1; i >= 1; i--) {
				GameManager::levelVector->at(i)->UninitializeLevel();
				delete GameManager::levelVector->at(i);
				GameManager::levelVector->at(i) = NULL;
				GameManager::levelVector->pop_back();
				GameManager::levelVector->shrink_to_fit();
			}

			GameManager::levelVector->push_back(new Level());
			GameManager::levelVector->back()->InitializeLevel();
			return;
		}
	}
	else if (sprites->at(pointer)->isHoverOn(textures->at(VReturnmm))) {

		sprites->at(pointer)->currentColumn = 1;
		if (leftButton.isPressed) {
			GameManager::levelVector->at(0)->audios->at(button)->play();

			//remove all level in vector except for mainmanu
			for (int i = GameManager::levelVector->size() - 1; i >= 1; i--) {
				GameManager::levelVector->at(i)->UninitializeLevel();
				delete GameManager::levelVector->at(i);
				GameManager::levelVector->at(i) = NULL;
				GameManager::levelVector->pop_back();
				GameManager::levelVector->shrink_to_fit();
			}
			return;
		}
	}
	else if (sprites->at(pointer)->isHoverOn(textures->at(VQuit))) {

		sprites->at(pointer)->currentColumn = 1;
		if (leftButton.isPressed) {
			GameManager::levelVector->at(0)->audios->at(button)->play();
			PostQuitMessage(0);
			return;
		}
	}
	//must
	else {
		sprites->at(pointer)->currentColumn = 0;
	}

	//to avoid mouse out of window
	sprites->at(pointer)->updatePositionRect();
	if (sprites->at(pointer)->getPosition().x < 0) {
		sprites->at(pointer)->setPositionX(0);
	}
	if (sprites->at(pointer)->getPosition().x > MyWindowWidth) {
		sprites->at(pointer)->setPositionX(MyWindowWidth - 1);
	}
	if (sprites->at(pointer)->getPosition().y < 0) {
		sprites->at(pointer)->setPositionY (0);
	}
	if (sprites->at(pointer)->getPosition().y > MyWindowHeight) {
		sprites->at(pointer)->setPositionY(MyWindowHeight - 1);
	}
	sprites->at(pointer)->updateCropRect();


	//must
	altKey.isPressed = false;
	f4Key.isPressed = false;
	leftButton.isPressed = false;
}

//just copy and paste all
void Victory::Render() {
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

	Line::DrawLines(lines);

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
void Victory::UninitializeLevel() {
	GameManager::ReleaseTextures(textures);
	GameManager::ReleaseTexts(texts);
	GameManager::ReleaseSprite(sprites);
	GameManager::ReleaseLines(lines);
	GameManager::ReleaseAudios(audios);
}
;