#include "Crashing.h"

void Crashing::InitializeLevel()
{
	textures = new vector<Texture*>;
	texts = new vector<Text*>;
	sprites = new vector<Sprite*>;

	Texture* planetTexture = new Texture("Assets/Crashing/planet.png", 200, 200, D3DXVECTOR2(500, 500));
	planet = new FlyingObject(D3DXVECTOR2(3, 3), 0.1f, 10000, 0, planetTexture);
	planetTexture = NULL;


	planet->texture->transformation.rotationCenter = planet->texture->transformation.scalingCenter = D3DXVECTOR2(100, 100);




	//space ship

	Texture* spaceshipTexture = new Texture("Assets/Crashing/spaceship.png", 32, 32, D3DXVECTOR2(0, 0));

	spaceship = new FlyingObject(D3DXVECTOR2(0, 0), 10.0f, 3, 0.05f, spaceshipTexture);

	spaceshipTexture = NULL;

	spaceship->texture->transformation.rotationCenter = spaceship->texture->transformation.scalingCenter = D3DXVECTOR2(32 / 2, 32 / 2);


}

void Crashing::GetInput()
{
	Shell::directXManager.dInputKeyboardDevice->Acquire();
	Shell::directXManager.dInputMouseDevice->Acquire();

	Shell::directXManager.dInputKeyboardDevice->GetDeviceState(256, Shell::directXManager.diKeys);
	Shell::directXManager.dInputMouseDevice->GetDeviceState(sizeof(Shell::directXManager.mouseState), &Shell::directXManager.mouseState);

	GameManager::updateKeyStatus(KeyDown(DIK_LALT) || KeyDown(DIK_RALT), &altKey);
	GameManager::updateKeyStatus(KeyDown(DIK_F4), &f4Key);
	GameManager::updateKeyStatus(KeyDown(DIK_ESCAPE), &escKey);
	GameManager::updateKeyStatus(KeyDown(DIK_W), &wKey);
	GameManager::updateKeyStatus(KeyDown(DIK_A), &aKey);
	GameManager::updateKeyStatus(KeyDown(DIK_S), &sKey);
	GameManager::updateKeyStatus(KeyDown(DIK_D), &dKey);

}

void Crashing::Update(int framesToUpdate)
{	//must
	if ((altKey.isHolding && f4Key.isHolding)) {
		PostQuitMessage(0);
		return;
	}

	if (escKey.isPressed) {
		GameManager::levelVector->back()->UninitializeLevel();
		delete GameManager::levelVector->back();
		GameManager::levelVector->back() = NULL;
		GameManager::levelVector->pop_back();
		return;
	}
	for (int i = 0; i < framesToUpdate; i++) {
		//planet move
		planetMoving();


		//spaceship move
		if (wKey.isHolding) {
			spaceship->acceleration.x =
				sin(spaceship->texture->transformation.rotation) * spaceship->force / spaceship->mass;
			spaceship->acceleration.y =
				-cos(spaceship->texture->transformation.rotation) * spaceship->force / spaceship->mass;
		}
		if (aKey.isHolding) {
			spaceship->texture->transformation.rotation -= rotationSpeed;
		}
		if (dKey.isHolding) {
			spaceship->texture->transformation.rotation += rotationSpeed;
		}

		spaceship->velocity += spaceship->acceleration;
		spaceship->velocity *= 1 - spaceship->energyLostRate;
		spaceship->texture->transformation.position += spaceship->velocity;

		//cout << 'a' << " " << spaceship->acceleration.x << " " << spaceship->acceleration.y <<
		//	'v' << " " << spaceship->velocity.x << " " << spaceship->velocity.y << endl;


		spaceship->texture->transformation.UpdateMatrix();
		spaceship->texture->updatePositionRect();
		stayInsideWindow(spaceship);


		//circle collide, planet not move
		//if (circlesCollided(spaceship->texture, planet->texture, &vectorBetweenPoints)) {
		//	
		//	spaceship->texture->transformation.position -= spaceship->velocity;

		//	D3DXVECTOR2 wall = D3DXVECTOR2(-vectorBetweenPoints.y, vectorBetweenPoints.x);

		//	D3DXVECTOR2 vectorI = projectionOn(&wall, &spaceship->velocity);
		//	D3DXVECTOR2 vectorJ = projectionOn(&vectorBetweenPoints, &spaceship->velocity);

		//	D3DXVECTOR2 reflexedVector = vectorI - vectorJ;
		//	spaceship->velocity = reflexedVector;

		//	cout << vectorI.x << ' ' << vectorI.y << endl;
		//	//cout << reflexedVector.x << ' ' << reflexedVector.y<<endl;

		//	spaceship->texture->transformation.UpdateMatrix();
		//	spaceship->texture->updatePositionRect();
		//	stayInsideWindow(spaceship);
		//}

		//circle collide, planet move
		if (circlesCollided(spaceship->texture, planet->texture, &vectorBetweenPoints)) {

			spaceship->texture->transformation.position -= spaceship->velocity;


			float totalForce = planet->force * D3DXVec2Length(&planet->acceleration) + spaceship->force * D3DXVec2Length(&spaceship->acceleration);
			
			spaceship->acceleration.x += (totalForce / 2) / spaceship->mass;
			spaceship->acceleration.y += (totalForce / 2) / spaceship->mass;


			spaceship->velocity += spaceship->acceleration;

			planet->acceleration.x += (totalForce / 2) / planet->mass;
			planet->acceleration.y += (totalForce / 2) / planet->mass;

			planet->velocity += planet->acceleration;



			spaceship->texture->transformation.UpdateMatrix();
			spaceship->texture->updatePositionRect();
			stayInsideWindow(spaceship);

			planet->texture->transformation.UpdateMatrix();
			planet->texture->updatePositionRect();
			stayInsideWindow(planet);
		}




		spaceship->acceleration = D3DXVECTOR2(0, 0);
	}


	altKey.isPressed = false;
	f4Key.isPressed = false;
	escKey.isPressed = false;
	wKey.isPressed = false;
	aKey.isPressed = false;
	sKey.isPressed = false;
	dKey.isPressed = false;
}



D3DXVECTOR2 Crashing::projectionOn(D3DXVECTOR2* projectedAxis, D3DXVECTOR2* projectionOfVector)
{
	return(D3DXVec2Dot(projectionOfVector, projectedAxis) / (pow(D3DXVec2Length(projectedAxis), 2)) * *projectedAxis);
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



void Crashing::planetMoving()
{
	planet->velocity += planet->acceleration;
	planet->texture->transformation.position += planet->velocity;
	planet->texture->transformation.UpdateMatrix();

	stayInsideWindow(planet);
}

void Crashing::stayInsideWindow(FlyingObject* obj)
{
	if (obj->texture->transformation.position.x < 0) {
		obj->texture->transformation.position.x = 0;
		obj->velocity.x *= -1;
	}
	if (obj->texture->transformation.position.x + obj->texture->textureWidth > MyWindowWidth) {
		obj->texture->transformation.position.x = MyWindowWidth - obj->texture->textureWidth;
		obj->velocity.x *= -1;
	}
	if (obj->texture->transformation.position.y < 0) {
		obj->texture->transformation.position.y = 0;
		obj->velocity.y *= -1;
	}
	if (obj->texture->transformation.position.y + obj->texture->textureHeight > MyWindowHeight) {
		obj->texture->transformation.position.y = MyWindowHeight - obj->texture->textureHeight;
		obj->velocity.y *= -1;
	}

	spaceship->texture->transformation.UpdateMatrix();
	spaceship->texture->updatePositionRect();
}

bool Crashing::circlesCollided(Texture* circleA, Texture* circleB, D3DXVECTOR2* vectorBetweenPoints) {

	*vectorBetweenPoints = (circleA->transformation.rotationCenter + circleA->transformation.position) - (circleB->transformation.rotationCenter + circleB->transformation.position);
	//cout << D3DXVec2LengthSq(vectorBetweenPoints) << endl;
	return ((circleA->textureWidth / 2) + (circleB->textureWidth / 2)) * ((circleA->textureWidth / 2) + (circleB->textureWidth / 2)) >=
		D3DXVec2LengthSq(vectorBetweenPoints);


}

