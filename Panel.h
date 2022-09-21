#pragma once
#include <vector>
#include "Button.h"

class Panel :public StuffToBeDrawn {
public:
	std::vector<Button*>* buttons;

	Panel(D3DXVECTOR2 position,
		int width,
	int height,
		int horizontalAlign = leftAlign,
		int verticalAlign = topAlign) :
		StuffToBeDrawn(position, width, height,
			horizontalAlign, verticalAlign) {
		buttons = new std::vector<Button*>();
	};

	void CreateButton(Button* button);
	void Release();
	void Draw();

};

