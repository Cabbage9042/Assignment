#include "Sprite.h"

void Sprite::updateCropRect() {
	cropRect.top = currentRow * spriteHeight;
	cropRect.left = currentColumn * spriteWidth;
	cropRect.right = cropRect.left + spriteWidth;
	cropRect.bottom = cropRect.top + spriteHeight;
}

void Sprite::Draw(){
	updateCropRect();
	Texture::Draw();
}

void Sprite::updatePositionRect() {
	positionRect.top = transformation.position.y;
	positionRect.bottom = transformation.position.y + spriteHeight;
	positionRect.left = transformation.position.x;
	positionRect.right = transformation.position.x + spriteWidth;
}

