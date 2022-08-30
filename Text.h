#pragma once

#include "StuffToBeDrawn.h"

class Text : public StuffToBeDrawn{
public:
	LPCSTR text = NULL;
	LPD3DXFONT font = NULL;

	Text() :StuffToBeDrawn() {
		text = "";
		font = NULL;
	}


	Text(LPCSTR pText,
		LPD3DXFONT pFont,
		D3DXVECTOR2 pPosition,
		int pAlignFrom = leftAlign,
		D3DCOLOR pColor = D3DCOLOR_XRGB(255, 255, 255)) {

		text = pText;
		font = pFont;
		cropRect = RECT();
		alignFrom = pAlignFrom;

		updateCropRect();
		D3DXVECTOR2 topLeftPosition = getTopLeftPosition(pPosition);
		transformation = TransformationMatrix(topLeftPosition);


		color = pColor;

		updatePositionRect();
	}

	void updateCropRect();
	void Draw();
	void Release();
};
