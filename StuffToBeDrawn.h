#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "TransformationMatrix.h"
#pragma comment(lib, "d3dx9.lib")


enum { leftAlign, centerAlign, rightAlign };
enum { topAlign, middleAlign, bottomAlign };

class StuffToBeDrawn {
public:
	int horizontalAlign;
	int verticalAlign;
	RECT cropRect;
	RECT positionRect;
	D3DXVECTOR2 relativePosition; // given postion
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
		horizontalAlign = leftAlign;
		verticalAlign = topAlign;

		textureWidth = 0;
		textureHeight = 0;

		cropRect = RECT();


		color = D3DCOLOR_XRGB(255, 255, 255);
		updatePositionRect();

	}

	StuffToBeDrawn(D3DXVECTOR2 pPosition,
		int pTextureWidth,
		int pTextureHeight,
		int pHorizontalAlign = leftAlign,
		int pVerticalAlign = topAlign,
		D3DCOLOR pColor = D3DCOLOR_XRGB(255, 255, 255)) {

		textureWidth = pTextureWidth;
		textureHeight = pTextureHeight;

		horizontalAlign = pHorizontalAlign;
		verticalAlign = pVerticalAlign;
		
		color = pColor;

		relativePosition = pPosition;
		D3DXVECTOR2 topLeftPosition = getTopLeftPosition(pPosition);

		updateCropRect();
		transformation = TransformationMatrix(topLeftPosition);
		updatePositionRect();
	}
};

