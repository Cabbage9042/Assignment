#include "MainMenu.h"
#include "Shell.h"
#include "Level.h"


//sprite
enum { pointer };

void MainMenu::InitializeLevel() {
	textures = new vector<Texture*>;
	texts = new vector<Text*>;
	sprites = new vector<Sprite*>;

	//button start
	GameManager::CreateTexture("Assets/button.png", textures, 459, 96, D3DXVECTOR2(MyWindowWidth / 2, MyWindowHeight / 2), centerAlign);


	//button quit
	GameManager::CreateTexture("Assets/button.png", textures, 459, 96, D3DXVECTOR2(MyWindowWidth / 2, (MyWindowHeight / 2) + 96 * 2), centerAlign);



	GameManager::CreateText(texts, "Walking on a spaceship", GameManager::fonts->at(franklin100), D3DXVECTOR2(MyWindowWidth / 2, MyWindowHeight / 5), centerAlign);
	GameManager::CreateText(texts, "Start", GameManager::fonts->at(arial25), D3DXVECTOR2(MyWindowWidth / 2, MyWindowHeight / 2 + 35), centerAlign);
	GameManager::CreateText(texts, "Quit", GameManager::fonts->at(arial25), D3DXVECTOR2(MyWindowWidth / 2, ((MyWindowHeight / 2) + 96 * 2) + 35), centerAlign);

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
		spriteRow, spriteCol, currentColumn,currentRow, maxFrame, D3DXVECTOR2(0, 0));
}

void MainMenu::GetInput() {
	Shell::directXManager.dInputKeyboardDevice->Acquire();
	Shell::directXManager.dInputMouseDevice->Acquire();

	Shell::directXManager.dInputKeyboardDevice->GetDeviceState(256, Shell::directXManager.diKeys);
	Shell::directXManager.dInputMouseDevice->GetDeviceState(sizeof(Shell::directXManager.mouseState), &Shell::directXManager.mouseState);

	if (KeyDown(DIK_LALT) || KeyDown(DIK_RALT)) {
		altKeyPressed = true;
	}
	if (KeyDown(DIK_F4)) {
		f4KeyPressed = true;
	}


	sprites->at(pointer)->transformation.position.x += Shell::directXManager.mouseState.lX;
	sprites->at(pointer)->transformation.position.y += Shell::directXManager.mouseState.lY;

}

void MainMenu::Update(int framesToUpdate) {

	if ((altKeyPressed && f4KeyPressed) || escKeyPressed) {
		PostQuitMessage(0);
	}

	for (int i = 0; i < framesToUpdate; i++) {
		//cout << "pointer x " << sprites->at(pointer)->transformation.position.x <<
		//	"y " << sprites->at(pointer)->transformation.position.y;

		if (sprites->at(pointer)->isHoverOn(textures->at(buttonStart))) {
			sprites->at(pointer)->currentColumn = 1;
			if (ButtonDown(0)) {
				Level* level = new Level();
				level->InitializeLevel();
				GameManager::levelVector->push_back(level);
				level = NULL;
			}
		}
		else if (sprites->at(pointer)->isHoverOn(textures->at(buttonQuit))) {

			sprites->at(pointer)->currentColumn = 1;
			if (ButtonDown(0)) {
				PostQuitMessage(0);
			}
		}
		else {
			sprites->at(pointer)->currentColumn = 0;
		}
	}

	//mouse
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

	altKeyPressed = false;
	f4KeyPressed = false;
	escKeyPressed = false;
}

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

void MainMenu::UninitializeLevel() {
	GameManager::ReleaseTextures(textures);
	GameManager::ReleaseTexts(texts);
	GameManager::ReleaseSprite(sprites);
}
;