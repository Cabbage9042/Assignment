#include "Crashing.h"

void Crashing::InitializeLevel()
{
	textures = new vector<Texture*>;
	texts = new vector<Text*>;
	sprites = new vector<Sprite*>;

	Texture* planetTexture = new Texture("Assets/Crashing/planet.png", 200, 200, D3DXVECTOR2(0, 0));
	planet = new FlyingObject(planetTexture);
	planetTexture = NULL;
	
	int textureWidth = 64;
	int textureHeight = 64;
	int spriteRow = 2;
	int spriteCol = 2;
	int spriteWidth = textureWidth / spriteCol;
	int spriteHeight = textureHeight / spriteRow;
	int currentColumn = 1;
	int currentRow = 0;
	int maxFrame = 1;

	Sprite* spaceshipSprite = new Sprite("Assets/Crashing/spaceship.png", textureWidth, textureHeight, spriteWidth, spriteHeight,
		spriteRow, spriteCol, currentColumn, currentRow, maxFrame, D3DXVECTOR2(0, 0));

	spaceship = new FlyingObject(spaceshipSprite);

	spaceshipSprite = NULL;


}

void Crashing::GetInput()
{
	Shell::directXManager.dInputKeyboardDevice->Acquire();
	Shell::directXManager.dInputMouseDevice->Acquire();

	Shell::directXManager.dInputKeyboardDevice->GetDeviceState(256, Shell::directXManager.diKeys);
	Shell::directXManager.dInputMouseDevice->GetDeviceState(sizeof(Shell::directXManager.mouseState), &Shell::directXManager.mouseState);

	GameManager::updateKeyStatus(KeyDown(DIK_LALT) || KeyDown(DIK_RALT), &altKey);
	GameManager::updateKeyStatus(KeyDown(DIK_F4), &f4Key);
	GameManager::updateKeyStatus(KeyDown(DIK_DOWN), &downKey);

}

void Crashing::Update(int framesToUpdate)
{	//must
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

	

	downKey.isPressed = false;
	altKey.isPressed = false;
	f4Key.isPressed = false;
}

void Crashing::Render()
{

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

	planet->texture->Draw();
	spaceship->texture->Draw();
	GameManager::RenderEnd();
}

void Crashing::UninitializeLevel()
{
	planet->Release();
	delete planet;
	planet = NULL;

	spaceship->Release();
	delete spaceship;
	spaceship = NULL;
		
	GameManager::ReleaseTextures(textures);
	GameManager::ReleaseTexts(texts);
	GameManager::ReleaseSprite(sprites);
}
