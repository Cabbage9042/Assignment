#include "Panel.h"

void Panel::CreateButton(Button* button){
	buttons->push_back(button);
}

void Panel::Release()
{
	for (int i = buttons->size() - 1; i >= 0; i--) {
		buttons->at(i)->Release();
		delete buttons->at(i);
		buttons->at(i) = NULL;
	}

	delete buttons;
	buttons = NULL;
}

void Panel::Draw() {
	for (int i = buttons->size() - 1; i >= 0; i--) {
		buttons->at(i)->Draw();
	}

}