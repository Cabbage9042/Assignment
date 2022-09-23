#include "Sprite.h"

void Sprite::updateCropRect() {
	cropRect.top = currentRow * spriteHeight;
	cropRect.left = currentColumn * spriteWidth;
	cropRect.right = cropRect.left + spriteWidth;
	cropRect.bottom = cropRect.top + spriteHeight;
}

void Sprite::Draw(){
	updateCropRect();
	updatePositionRect();
	Texture::Draw();
}

void Sprite::updatePositionRect() {
	positionRect.top = getPosition().y;
	positionRect.bottom = getPosition().y + spriteHeight;
	positionRect.left = getPosition().x;
	positionRect.right = getPosition().x + spriteWidth;
}

void Sprite::setPosition(D3DXVECTOR2 vector) {
	transformation.setPosition(vector);
	updatePositionRect();
}

void Sprite::setPositionY(float y)
{
	transformation.setPositionY(y);
	updatePositionRect();
}

void Sprite::setPositionX(float x)
{
	transformation.setPositionX(x);
	updatePositionRect();
}

void Sprite::addPosition(D3DXVECTOR2 vector) {
	transformation.addPosition(vector);
	updatePositionRect();
}
void Sprite::subtractPosition(D3DXVECTOR2 vector) {
	transformation.subtractPosition(vector);
	updatePositionRect();
}
void Sprite::multiplyPosition(float n) {
	transformation.multiplyPosition(n);
	updatePositionRect();
}
void Sprite::dividePosition(float n) {
	transformation.dividePosition(n);
	updatePositionRect();
}
