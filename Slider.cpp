#include "Slider.h"

void Slider::Move(D3DXVECTOR2 velocity) {
	bar->addPosition( velocity);

	handle->addPosition(velocity);

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
	handle->setPositionX (pointerPosition.x - (handle->textureWidth/2.0));

	if (handle->getPosition().x - (handle->textureWidth / 2.0) < bar->getPosition().x) {
		handle->setPositionX(bar->getPosition().x - (handle->textureWidth / 2.0));
	}
	else if (handle->getPosition().x + handle->textureWidth / 2.0 > bar->getPosition().x + bar->textureWidth) {
		handle->setPositionX(bar->getPosition().x + bar->textureWidth - handle->textureWidth /2.0);
	}

}

float Slider::getValue()
{
	return ((handle->getPosition().x + (handle->textureWidth / 2.0f)) - bar->getPosition().x) / bar->textureWidth;
}
