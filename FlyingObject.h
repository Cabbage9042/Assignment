#pragma once
#define DEFAULT_VELOCITY D3DXVECTOR2(0,0)
#define DEFAULT_SPEED 5
#include <d3d9.h>
#include <d3dx9.h>

#include "Texture.h"

class FlyingObject{
public:
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 acceleration;
	float force;
	float mass;
	Texture* texture = NULL;

	FlyingObject(D3DXVECTOR2 velocity, float force, float mass, Texture* texture);
	void Release();
};

