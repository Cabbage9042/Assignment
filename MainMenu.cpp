#include "MainMenu.h"
#include "Shell.h"
#include "Level.h"
#include "Crashing.h"

#define characterIsFalling (character.velocity.y > 0)

void MainMenu::InitializeLevel() {
	//must
	textures = new vector<Texture*>;
	texts = new vector<Text*>;
	sprites = new vector<Sprite*>;
	lines = new vector<Line*>;
	audios = new vector<Audio*>;

	//text
	GameManager::CreateText(texts, "Escape From Spaceship", GameManager::fonts->at(franklin100), D3DXVECTOR2(MyWindowWidth / 2, MyWindowHeight / 5), centerAlign);

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



	//title border
	vector<D3DXVECTOR2>* vectorVertices = new vector<D3DXVECTOR2>{
		D3DXVECTOR2(texts->at(0)->transformation.position.x,texts->at(0)->transformation.position.y),
		D3DXVECTOR2(texts->at(0)->transformation.position.x + texts->at(0)->textureWidth,texts->at(0)->transformation.position.y),
		D3DXVECTOR2(texts->at(0)->transformation.position.x + texts->at(0)->textureWidth,texts->at(0)->transformation.position.y + texts->at(0)->textureHeight),
		D3DXVECTOR2(texts->at(0)->transformation.position.x,texts->at(0)->transformation.position.y + texts->at(0)->textureHeight)
	};
	lines->push_back(new Line(vectorVertices));


	//audio
	audios->push_back(new Audio("Assets/button.mp3", effectGroup));
	audios->at(button)->setLoop(false);

	audios->push_back(new Audio("Assets/MainMenu/background1.mp3", bgmGroup, AUDIO_CREATE_STREAM));
	audios->at(bgm)->setLoop(true);

	//button panel
	buttonPanel = new Panel(D3DXVECTOR2(MyWindowWidth / 2, MyWindowHeight / 2), 459, 500, centerAlign);

	buttonPanel->CreateButton(new Button(
		new Texture("Assets/tbutton.png", 459, 96, D3DXVECTOR2(0, 0)),
		new Text("Start", GameManager::fonts->at(arial25), D3DXVECTOR2(459 / 2, 96 / 2), centerAlign, middleAlign)
	));

	buttonPanel->CreateButton(new Button(
		new Texture("Assets/tbutton.png", 459, 96, D3DXVECTOR2(0, 100 * 2)),
		new Text("Quit", GameManager::fonts->at(arial25), D3DXVECTOR2(459 / 2, 96 / 2), centerAlign, middleAlign)
	));

	//option panel, is dependent on button panel
	optionPanel = new Panel(D3DXVECTOR2(buttonPanel->getPosition().x + (MyWindowWidth * 4 / 5), buttonPanel->getPosition().y), MyWindowWidth * 3 / 5, MyWindowHeight / 5);
	optionPanel->CreateLabel(new Text("Background Music", GameManager::fonts->at(arial25), D3DXVECTOR2(0, 0)));
	
	bgmVolumeLabel = new Text(bgmVolumeLabelString, GameManager::fonts->at(arial25), D3DXVECTOR2(optionPanel->textureWidth, 0), rightAlign);
	
	optionPanel->CreateLabel(bgmVolumeLabel);
	optionPanel->CreateSlider(new Slider(
		new Texture("Assets/MainMenu/slider1.png", 388, 27, D3DXVECTOR2(optionPanel->labels->at(bgmVolumeLabelEnum)->relativePosition.x - 30, optionPanel->labels->at(bgmLabelEnum)->relativePosition.y), rightAlign, topAlign),
		new Texture("Assets/MainMenu/slider2.png", 6, 30, D3DXVECTOR2(388,0), leftAlign, topAlign)
	));

	optionPanel->CreateLabel(new Text("Sound Effect", GameManager::fonts->at(arial25), D3DXVECTOR2(0, optionPanel->textureHeight), leftAlign, bottomAlign));
	effectVolumeLabel = new Text(effectVolumeLabelString, GameManager::fonts->at(arial25), D3DXVECTOR2(optionPanel->textureWidth, optionPanel->textureHeight), rightAlign, bottomAlign);

	optionPanel->CreateLabel(effectVolumeLabel);
	optionPanel->CreateSlider(new Slider(
		new Texture("Assets/MainMenu/slider1.png", 388, 27, D3DXVECTOR2(optionPanel->labels->at(effectVolumeLabelEnum)->relativePosition.x - 30, optionPanel->labels->at(effectVolumeLabelEnum)->relativePosition.y), rightAlign, topAlign),
		new Texture("Assets/MainMenu/slider2.png", 6, 30, D3DXVECTOR2(388, 0), leftAlign, topAlign)
	));
}


void MainMenu::GetInput() {

	//all must
	Shell::directXManager.dInputKeyboardDevice->Acquire();
	Shell::directXManager.dInputMouseDevice->Acquire();

	Shell::directXManager.dInputKeyboardDevice->GetDeviceState(256, Shell::directXManager.diKeys);
	Shell::directXManager.dInputMouseDevice->GetDeviceState(sizeof(Shell::directXManager.mouseState), &Shell::directXManager.mouseState);

	altKey.updateKeyStatus(KeyDown(DIK_LALT) || KeyDown(DIK_RALT));
	f4Key.updateKeyStatus(KeyDown(DIK_F4));
	leftButton.updateKeyStatus(ButtonDown(0));
	spaceKey.updateKeyStatus(KeyDown(DIK_SPACE));
	dKey.updateKeyStatus(KeyDown(DIK_D));
	aKey.updateKeyStatus(KeyDown(DIK_A));

	sprites->at(pointer)->transformation.position.x += Shell::directXManager.mouseState.lX;
	sprites->at(pointer)->transformation.position.y += Shell::directXManager.mouseState.lY;

}

void MainMenu::Update(int framesToUpdate) {

	//must
	if ((altKey.isHolding && f4Key.isHolding)) {
		PostQuitMessage(0);
		return;
	}

	//start bgm will be true after initialazing main menu and before go to level
	if (startBGM) {
		audios->at(bgm)->play();
		startBGM = false;
	}

	if (buttonIsClicked()) {

		//audio
		audios->at(button)->play();
		return;
	}

	//jump if space is pressed and character is on a platform (on a button or on the floor)
	if (spaceKey.isPressed && (character.sprite.positionRect.bottom == MyWindowHeight ||
		character.sprite.positionRect.bottom == buttonPanel->buttons->at(buttonQuit)->texture->positionRect.top)) {
		character.velocity.y = JumpForce;
	}
	for (int i = 0; i < framesToUpdate; i++) {

		if (aKey.isHolding) {
			buttonPanel->Move(D3DXVECTOR2(-20, 0));
			optionPanel->Move(D3DXVECTOR2(-20, 0));
		}if (dKey.isHolding) {
			buttonPanel->Move(D3DXVECTOR2(20, 0));
			optionPanel->Move(D3DXVECTOR2(20, 0));
		}


		if (leftButton.isHolding) {
			if (sprites->at(pointer)->isHoverOn(optionPanel->sliders->at(bgmSlider)->bar) || optionPanel->sliders->at(bgmSlider)->isChanging) {
				optionPanel->sliders->at(bgmSlider)->MoveHandle(sprites->at(pointer)->getPosition());
				int volume = (int)(100.0 * optionPanel->sliders->at(bgmSlider)->getValue());



				//int to string
				if (volume == 100) {
					bgmVolumeLabelString[0] = '1';
					bgmVolumeLabelString[1] = bgmVolumeLabelString[2] = '0';
				}
				else {
					bgmVolumeLabelString[0] = (volume) / 10 + 48;
					bgmVolumeLabelString[1] = (volume) % 10 + 48;
					bgmVolumeLabelString[2] = ' ';
				}
				bgmVolumeLabel->updateCropRect();
				bgmVolumeLabel->updatePositionRect();
				bgmVolumeLabel->transformation.UpdateMatrix();

				Shell::audioManager.setBgmVolume(volume / 100.0);
				

				optionPanel->sliders->at(bgmSlider)->isChanging = true;
			}
			else if(sprites->at(pointer)->isHoverOn(optionPanel->sliders->at(effectSlider)->bar) || optionPanel->sliders->at(effectSlider)->isChanging) {
				optionPanel->sliders->at(effectSlider)->MoveHandle(sprites->at(pointer)->getPosition());
				int volume = (int)(100.0 * optionPanel->sliders->at(effectSlider)->getValue());
				//int to string
				if (volume == 100) {
					effectVolumeLabelString[0] = '1';
					effectVolumeLabelString[1] = effectVolumeLabelString[2] = '0';
				}
				else {
					effectVolumeLabelString[0] = (volume) / 10 + 48;
					effectVolumeLabelString[1] = (volume) % 10 + 48;
					effectVolumeLabelString[2] = ' ';
				}
				effectVolumeLabel->updateCropRect();
				effectVolumeLabel->updatePositionRect();
				effectVolumeLabel->transformation.UpdateMatrix();

				Shell::audioManager.setEffectVolume(volume / 100.0);


				optionPanel->sliders->at(effectSlider)->isChanging = true;

			}
		}
		else {
			optionPanel->sliders->at(bgmSlider)->isChanging = false;
			optionPanel->sliders->at(effectSlider)->isChanging = false;
		}


		moveCharacter();
	}



	//to avoid mouse out of window
	pointerStayInsideWindow();



	Shell::audioManager.updateSound();

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

	Line::DrawLines(lines);

	//panel
	buttonPanel->Draw();
	optionPanel->Draw();

	//pointer
	sprites->at(pointer)->Draw();




	GameManager::RenderEnd();
}

//just copy and paste all
void MainMenu::UninitializeLevel() {
	buttonPanel->Release();
	optionPanel->Release();
	character.sprite.Release();

	GameManager::ReleaseTextures(textures);
	GameManager::ReleaseTexts(texts);
	GameManager::ReleaseSprite(sprites);
	GameManager::ReleaseLines(lines);
	GameManager::ReleaseAudios(audios);
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

bool MainMenu::buttonIsClicked() {
	if (buttonPanel->buttons->at(buttonStart)->isBeingHover(sprites->at(pointer))) {
		//must
		sprites->at(pointer)->currentColumn = 1;

		if (leftButton.isPressed) {
			Level* level = new Level();
			level->InitializeLevel();
			GameManager::levelVector->push_back(level);
			level = NULL;

			audios->at(bgm)->stop();


			resetToDefault();

			return true;

		}
	}
	else if (sprites->at(pointer)->isHoverOn(texts->at(0))) {

		sprites->at(pointer)->currentColumn = 1;
		if (leftButton.isPressed) {
			Crashing* crashing = new Crashing();
			crashing->InitializeLevel();
			GameManager::levelVector->push_back(crashing);
			crashing = NULL;

			resetToDefault(false);

			return true;
		}
	}
	else if (buttonPanel->buttons->at(buttonQuit)->isBeingHover(sprites->at(pointer))) {

		sprites->at(pointer)->currentColumn = 1;
		if (leftButton.isPressed) {
			PostQuitMessage(0);
			return true;;
		}
	}
	//must
	else {
		sprites->at(pointer)->currentColumn = 0;
	}
	return false;
}

//bool MainMenu::buttonIsClicked() {
//	if (sprites->at(pointer)->isHoverOn(textures->at(buttonStart))) {
//		//must
//		sprites->at(pointer)->currentColumn = 1;
//
//		if (leftButton.isPressed) {
//			Level* level = new Level();
//			level->InitializeLevel();
//			GameManager::levelVector->push_back(level);
//			level = NULL;
//
//			audios->at(bgm)->stop();
//
//
//			resetToDefault();
//
//			return true;
//			
//		}
//	}
//	else if (sprites->at(pointer)->isHoverOn(texts->at(0))) {
//
//		sprites->at(pointer)->currentColumn = 1;
//		if (leftButton.isPressed) {
//			Crashing* crashing = new Crashing();
//			crashing->InitializeLevel();
//			GameManager::levelVector->push_back(crashing);
//			crashing = NULL;
//
//			resetToDefault(false);
//
//			return true;
//		}
//	}
//	else if (sprites->at(pointer)->isHoverOn(buttonPanel->buttons->at(buttonQuit)->texture)) {
//
//		sprites->at(pointer)->currentColumn = 1;
//		if (leftButton.isPressed) {
//			PostQuitMessage(0);
//			return true;;
//		}
//	}
//	//must
//	else {
//		sprites->at(pointer)->currentColumn = 0;
//	}
//	return false;
//}

void MainMenu::updateCollidedToButton()
{
	if (character.sprite.positionRect.bottom >= MyWindowHeight) {
		character.sprite.transformation.position.y = MyWindowHeight - character.sprite.spriteHeight;
		character.velocity.y = 0;
	}
	//left button quit
	else if (character.sprite.positionRect.left < buttonPanel->buttons->at(buttonQuit)->texture->positionRect.left &&
		character.sprite.positionRect.right > buttonPanel->buttons->at(buttonQuit)->texture->positionRect.left &&
		!(character.sprite.positionRect.top > buttonPanel->buttons->at(buttonQuit)->texture->positionRect.bottom ||
			character.sprite.positionRect.bottom < buttonPanel->buttons->at(buttonQuit)->texture->positionRect.top) &&
		character.sprite.currentRow == walkingRight) {
		character.sprite.transformation.position.x = buttonPanel->buttons->at(buttonQuit)->texture->positionRect.left - character.sprite.spriteWidth;
		character.velocity.x *= -1;
		character.sprite.currentRow = walkingLeft;
	}
	//right button quit
	else if (character.sprite.positionRect.left < buttonPanel->buttons->at(buttonQuit)->texture->positionRect.right &&
		character.sprite.positionRect.right > buttonPanel->buttons->at(buttonQuit)->texture->positionRect.right &&
		!(character.sprite.positionRect.top > buttonPanel->buttons->at(buttonQuit)->texture->positionRect.bottom ||
			character.sprite.positionRect.bottom < buttonPanel->buttons->at(buttonQuit)->texture->positionRect.top) &&
		character.sprite.currentRow == walkingLeft) {
		character.sprite.transformation.position.x = buttonPanel->buttons->at(buttonQuit)->texture->positionRect.right;
		character.velocity.x *= -1;
		character.sprite.currentRow = walkingRight;
	}
	//on top of button quit
	else if (character.sprite.positionRect.right > buttonPanel->buttons->at(buttonQuit)->texture->positionRect.left &&
		character.sprite.positionRect.left < buttonPanel->buttons->at(buttonQuit)->texture->positionRect.right &&
		character.sprite.positionRect.bottom >  buttonPanel->buttons->at(buttonQuit)->texture->positionRect.top &&
		character.sprite.positionRect.top < buttonPanel->buttons->at(buttonQuit)->texture->positionRect.top &&
		characterIsFalling) {
		character.sprite.transformation.position.y = buttonPanel->buttons->at(buttonQuit)->texture->positionRect.top - character.sprite.spriteHeight;
		character.velocity.y = 0;
	}
	//below button quit
	else if (character.sprite.positionRect.right > buttonPanel->buttons->at(buttonQuit)->texture->positionRect.left &&
		character.sprite.positionRect.left < buttonPanel->buttons->at(buttonQuit)->texture->positionRect.right &&
		character.sprite.positionRect.top < buttonPanel->buttons->at(buttonQuit)->texture->positionRect.bottom &&
		character.sprite.positionRect.bottom > buttonPanel->buttons->at(buttonQuit)->texture->positionRect.bottom &&
		!characterIsFalling) {
		character.sprite.transformation.position.y = buttonPanel->buttons->at(buttonQuit)->texture->positionRect.bottom;
		character.velocity.y *= -1;
	}

	//below button start
	else if (character.sprite.positionRect.right > buttonPanel->buttons->at(buttonStart)->texture->positionRect.left &&
		character.sprite.positionRect.left < buttonPanel->buttons->at(buttonStart)->texture->positionRect.right &&
		character.sprite.positionRect.top < buttonPanel->buttons->at(buttonStart)->texture->positionRect.bottom &&
		character.sprite.positionRect.bottom > buttonPanel->buttons->at(buttonStart)->texture->positionRect.bottom &&
		!characterIsFalling) {
		character.sprite.transformation.position.y = buttonPanel->buttons->at(buttonStart)->texture->positionRect.bottom;
		character.velocity.y *= -1;
	}

}

void MainMenu::resetToDefault(bool resetBGM)
{
	startBGM = resetBGM;
	character.sprite.transformation.position = D3DXVECTOR2(0, MyWindowHeight - character.sprite.spriteHeight);
	character.sprite.updatePositionRect();

	sprites->at(pointer)->transformation.position = D3DXVECTOR2(0, 0);
	sprites->at(pointer)->updatePositionRect();
}

void MainMenu::moveCharacter()
{if (character.sprite.positionRect.left <= 0) {
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

		updateCollidedToButton();

		character.characterAnimationCounter++;
		if (character.characterAnimationCounter % (gameFPS / character.characterFPS) == 0) {
			character.sprite.currentColumn++;
			if (character.sprite.currentColumn == character.sprite.maxFrame) {
				character.sprite.currentColumn = 0;
			}
		}


		character.sprite.updatePositionRect();
		character.sprite.transformation.UpdateMatrix();
}
