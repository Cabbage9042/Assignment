#pragma once
#include <vector>
#include "Button.h"

class Panel :public StuffToBeDrawn {
public:
	std::vector<Button*>* buttons;

	Panel(D3DXVECTOR2 position,
		int textureWidth,
		int textureHeight,
		int horizontalAlign = leftAlign,
		int verticalAlign = topAlign) :
		StuffToBeDrawn(position, textureWidth, textureHeight,
			horizontalAlign, verticalAlign) {};

	void CreateButton(Button* button);
	void Release();

};

