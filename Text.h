#pragma once

#include "StuffToBeDrawn.h"

class Text : public StuffToBeDrawn{
private:
	LPCSTR text = NULL;
public:
	LPD3DXFONT font = NULL;

	Text() :StuffToBeDrawn() {
		text = "";
		font = NULL;
	}


	Text(LPCSTR pText,
		LPD3DXFONT pFont,
		D3DXVECTOR2 pPosition,
		int phorizontalAlign = leftAlign,
		int verticalAlign = topAlign,
		D3DCOLOR pColor = D3DCOLOR_XRGB(255, 255, 255)) {

		text = pText;
		font = pFont;
		cropRect = RECT();
		horizontalAlign = phorizontalAlign;
		this->verticalAlign = verticalAlign;

		updateCropRect();
		D3DXVECTOR2 topLeftPosition = getTopLeftPosition(pPosition);
		transformation = TransformationMatrix(topLeftPosition);


		color = pColor;

		updatePositionRect();
	}

	void updateCropRect();
	void setText(LPCSTR *text);
	void deleteText();
	void Draw();
	void Move(D3DXVECTOR2 vector);
	void Release();

};

