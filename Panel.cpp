#include "Panel.h"

void Panel::CreateButton(Button* button){
	buttons->push_back(button);
}

void Panel::Release()
{
	for (int i = buttons->size() - 1; i >= 0; i--) {
		buttons->back()->Release();
		delete buttons->back();
		buttons->back() = NULL;
	}

	delete buttons;
	buttons = NULL;
}
