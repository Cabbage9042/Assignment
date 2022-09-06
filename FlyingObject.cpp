#include "FlyingObject.h"

FlyingObject::FlyingObject(Texture* texture)
{
	velocity = DEFAULT_VELOCITY;
	acceleration = DEFAULT_VELOCITY;

	this->texture = texture;

}

void FlyingObject::Release()
{
	texture->Release();
	delete texture;
	texture = NULL;
}
