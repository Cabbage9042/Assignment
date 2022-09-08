#include "Pause.h"
#include "Shell.h"
#include "Level.h"



//sprite
enum { pointer };

void Pause::InitializeLevel() {
	//must
	textures = new vector<Texture*>;
	texts = new vector<Text*>;
	sprites = new vector<Sprite*>;

	//button start  ***
	GameManager::CreateTexture("Assets/nbutton.png", textures, 459, 96, D3DXVECTOR2(MyWindowWidth / 2, MyWindowHeight / 2), centerAlign);


	//button quit  ***
	GameManager::CreateTexture("Assets/nbutton.png", textures, 459, 96, D3DXVECTOR2(MyWindowWidth / 2, (MyWindowHeight / 2) + 96 * 2), centerAlign);
	GameManager::CreateTexture("Assets/pause.png", textures, 320,285 , D3DXVECTOR2(MyWindowWidth / 2, (MyWindowHeight / 2) -350), centerAlign);

	//text    ***

	GameManager::CreateText(texts, "Continue", GameManager::fonts->at(arial25), D3DXVECTOR2(MyWindowWidth / 2, MyWindowHeight / 2 + 35), centerAlign);
	GameManager::CreateText(texts, "Return Main Menu", GameManager::fonts->at(arial25), D3DXVECTOR2(MyWindowWidth / 2, ((MyWindowHeight / 2) + 96 * 2) + 35), centerAlign);


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
}

void Pause::GetInput() {

	//all must
	Shell::directXManager.dInputKeyboardDevice->Acquire();
	Shell::directXManager.dInputMouseDevice->Acquire();

	Shell::directXManager.dInputKeyboardDevice->GetDeviceState(256, Shell::directXManager.diKeys);
	Shell::directXManager.dInputMouseDevice->GetDeviceState(sizeof(Shell::directXManager.mouseState), &Shell::directXManager.mouseState);


	GameManager::updateKeyStatus(KeyDown(DIK_LALT) || KeyDown(DIK_RALT), &altKey);
	GameManager::updateKeyStatus(KeyDown(DIK_F4), &f4Key);
	GameManager::updateKeyStatus(ButtonDown(0), &leftButton);


	sprites->at(pointer)->transformation.position.x += Shell::directXManager.mouseState.lX;
	sprites->at(pointer)->transformation.position.y += Shell::directXManager.mouseState.lY;

}

void Pause::Update(int framesToUpdate) {

	//must
	if ((altKey.isHolding && f4Key.isHolding)) {
		PostQuitMessage(0);
		return;
	}

	//change parameter of isHoverOn to button u want
	if (sprites->at(pointer)->isHoverOn(textures->at(PContinue))) {
		//must
		sprites->at(pointer)->currentColumn = 1;

		if (leftButton.isPressed) {
			Level* level = new Level();
			level->InitializeLevel();
			GameManager::levelVector->push_back(level);
			level = NULL;
		}
	}
	else if (sprites->at(pointer)->isHoverOn(textures->at(PReturnmm))) {

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

	for (int i = 0; i < framesToUpdate; i++) {
		//do animation if got



	}

	//to avoid mouse out of window, must
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


	//must
	altKey.isPressed = false;
	f4Key.isPressed = false;
	leftButton.isPressed = false;
}

//just copy and paste all
void Pause::Render() {
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
void Pause::UninitializeLevel() {
	GameManager::ReleaseTextures(textures);
	GameManager::ReleaseTexts(texts);
	GameManager::ReleaseSprite(sprites);
}
;