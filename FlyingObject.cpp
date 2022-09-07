#include "FlyingObject.h"

FlyingObject::FlyingObject(D3DXVECTOR2 velocity, float force, float mass, Texture* texture)
{
	this->velocity = velocity;
	acceleration = DEFAULT_VELOCITY;

	this->force = force;
	this->mass = mass;

	this->texture = texture;

}

void FlyingObject::Release()
{
	texture->Release();
	delete texture;
	texture = NULL;
}
