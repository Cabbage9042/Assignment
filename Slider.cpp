#include "Slider.h"

void Slider::Move(D3DXVECTOR2 velocity) {
	bar->transformation.position += velocity;
	bar->updatePositionRect();
	bar->transformation.UpdateMatrix();

	handle->transformation.position += velocity;
	handle->updatePositionRect();
	handle->transformation.UpdateMatrix();
}

void Slider::Release() {
	bar->Release();
	bar = NULL;
	handle->Release();
	handle = NULL;
}

void Slider::Draw()
{
	bar->Draw();
	handle->Draw();
}

void Slider::MoveHandle(D3DXVECTOR2 pointerPosition) {
	handle->transformation.position.x =
		(bar->transformation.position.x + (((pointerPosition.x - bar->transformation.position.x)) / bar->textureWidth) * bar->textureWidth);
	handle->updatePositionRect();

	if (handle->transformation.position.x < bar->transformation.position.x) {
		handle->transformation.position.x = bar->transformation.position.x;
	}
	else if (handle->transformation.position.x > bar->transformation.position.x + bar->textureWidth) {
		handle->transformation.position.x = bar->transformation.position.x + bar->textureWidth;
	}

	handle->transformation.UpdateMatrix();
}
