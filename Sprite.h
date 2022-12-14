#pragma once
#include "Texture.h"
class Sprite : public Texture {
	public:
	int spriteWidth;
	int spriteHeight;

	int spriteRow;
	int spriteColumn;

	int currentColumn;
	int currentRow;

	int maxFrame;

	void updateCropRect();
	void Draw();

	void updatePositionRect();

	void setPosition(D3DXVECTOR2 vector);
	void setPositionX(float x);
	void setPositionY(float y);
	void addPosition(D3DXVECTOR2 vector);
	void subtractPosition(D3DXVECTOR2 vector);
	void multiplyPosition(float n);
	void dividePosition(float n);
	Sprite() :Texture() {
		spriteWidth = 0;
		spriteHeight = 0;

		spriteRow = 0;
		spriteColumn = 0;

		currentColumn = 0;
		currentRow = 0;

		maxFrame = 0;
	}

	Sprite(LPDIRECT3DTEXTURE9 texture,
		int textureWidth, int textureHeight,
		int spriteWidth, int spriteHeight,
		int spriteRow, int spriteColumn,
		int currentColumn,int currentRow,
		int maxFrame,
		D3DXVECTOR2 position,
		int horizontalAlign = leftAlign,
		int verticalAlign = topAlign,
		D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) :
		Texture(texture, textureWidth, textureHeight, position, horizontalAlign, verticalAlign, color) {
		this->spriteWidth = spriteWidth;
		this->spriteHeight = spriteHeight;
		this->spriteRow = spriteRow;
		this->spriteColumn = spriteColumn;
		this->currentRow = currentRow;
		this->currentColumn = currentColumn;
		this->maxFrame = maxFrame;

		updatePositionRect();
	}

	Sprite(LPCSTR filePath,
		int textureWidth, int textureHeight,
		int spriteWidth, int spriteHeight,
		int spriteRow, int spriteColumn,
		int currentColumn, int currentRow,
		int maxFrame,
		D3DXVECTOR2 position,
		int horizontalAlign = leftAlign,
		int verticalAlign = topAlign,
		D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255)) :
		Texture(filePath, textureWidth, textureHeight, position, horizontalAlign, verticalAlign, color) {
		this->spriteWidth = spriteWidth;
		this->spriteHeight = spriteHeight;
		this->spriteRow = spriteRow;
		this->spriteColumn = spriteColumn;
		this->currentRow = currentRow;
		this->currentColumn = currentColumn;
		this->maxFrame = maxFrame;

		updateCropRect();
		updatePositionRect();
	}

};

