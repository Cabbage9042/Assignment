#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "TransformationMatrix.h"
#pragma comment(lib, "d3dx9.lib")


enum { leftAlign, centerAlign, rightAlign };

class StuffToBeDrawn {
public:

	int alignFrom;
	RECT cropRect;
	RECT positionRect;
	TransformationMatrix transformation;


	D3DCOLOR color;

	int textureWidth;
	int textureHeight;


	void updateCropRect();
	D3DXVECTOR2 getTopLeftPosition(D3DXVECTOR2 position);
	void updatePositionRect();
	bool isHoverOn(StuffToBeDrawn* textureBelow);
	bool isHoverOn(RECT rect,D3DXVECTOR2 position);
	bool isClickedOn(StuffToBeDrawn* textureBelow, bool mouseLeftButtonClicked);
	D3DXVECTOR2 getPosition() { return transformation.position; }

	

	StuffToBeDrawn() {
		transformation = TransformationMatrix();
		alignFrom = leftAlign;

		textureWidth = 0;
		textureHeight = 0;

		cropRect = RECT();


		color = D3DCOLOR_XRGB(255, 255, 255);
		updatePositionRect();

	}

	StuffToBeDrawn(D3DXVECTOR2 pPosition,
		int pTextureWidth,
		int pTextureHeight,
		int pAlignFrom = leftAlign,
		D3DCOLOR pColor = D3DCOLOR_XRGB(255, 255, 255)) {

		textureWidth = pTextureWidth;
		textureHeight = pTextureHeight;

		alignFrom = pAlignFrom;

		
		color = pColor;
		D3DXVECTOR2 topLeftPosition = getTopLeftPosition(pPosition);

		updateCropRect();
		transformation = TransformationMatrix(topLeftPosition);
		updatePositionRect();
	}
};

