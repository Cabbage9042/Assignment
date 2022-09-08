#include "FlyingObject.h"

FlyingObject::FlyingObject(D3DXVECTOR2 velocity, float force, float mass, float energyLostRate, Texture* texture)
{
	this->velocity = velocity;
	acceleration = DEFAULT_VELOCITY;

	this->force = force;
	this->mass = mass;
	this->energyLostRate = energyLostRate;

	this->texture = texture;

}

void FlyingObject::Release()
{
	texture->Release();
	delete texture;
	texture = NULL;
}
