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
	handle->transformation.position.x =pointerPosition.x - (handle->textureWidth/2.0);
	handle->updatePositionRect();

	if (handle->transformation.position.x - (handle->textureWidth / 2.0) < bar->transformation.position.x) {
		handle->transformation.position.x = bar->transformation.position.x - (handle->textureWidth / 2.0);
	}
	else if (handle->transformation.position.x + handle->textureWidth / 2.0 > bar->transformation.position.x + bar->textureWidth) {
		handle->transformation.position.x = bar->transformation.position.x + bar->textureWidth - handle->textureWidth /2.0;
	}

	handle->transformation.UpdateMatrix();
}

float Slider::getValue()
{
	return ((handle->getPosition().x + (handle->textureWidth / 2.0f)) - bar->getPosition().x) / bar->textureWidth;
}
