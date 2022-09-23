#pragma once
#include "Texture.h"

class Slider
{
public:
	Texture* bar;
	Texture* handle;
	bool isChanging = false;

	Slider(Texture* bar, Texture* handle) {
		this->bar = bar;

		handle->transformation.position += bar->transformation.position;
		this->handle = handle;
	}

	void Move(D3DXVECTOR2 velocity);
	void Release();
	void Draw();

	/// <summary>
	/// position is relative position of bar
	/// </summary>
	/// <param name="position"></param>
	void MoveHandle(D3DXVECTOR2 pointerPosition);
	float getValue();

};

