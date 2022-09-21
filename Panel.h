#pragma once
#include <vector>
#include "Button.h"
#include "Slider.h"

class Panel :public StuffToBeDrawn {
public:
	std::vector<Button*>* buttons;
	std::vector<Text*>* labels;
	std::vector<Slider*>* sliders;

	Panel(D3DXVECTOR2 position,
		int width,
		int height,
		int horizontalAlign = leftAlign,
		int verticalAlign = topAlign) :
		StuffToBeDrawn(position, width, height,
			horizontalAlign, verticalAlign) {
		buttons = new std::vector<Button*>();
		labels = new std::vector<Text*>();
		sliders = new std::vector<Slider*>();
	};


	void Move(D3DXVECTOR2 vector);
	void CreateButton(Button* button);
	void CreateLabel(Text* label);
	void CreateSlider(Slider* slider);
	void Release();
	void Draw();

};

