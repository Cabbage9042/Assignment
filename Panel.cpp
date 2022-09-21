#include "Panel.h"

void Panel::Move(D3DXVECTOR2 vector)
{
	this->transformation.position += vector;
	this->updatePositionRect();
	this->transformation.UpdateMatrix();

	for (auto button : *this->buttons) {
		button->Move(vector);
	}

	for (auto label : *this->labels) {
		label->Move(vector);
	}
}

void Panel::CreateButton(Button* button){
	buttons->push_back(button);
}

void Panel::CreateLabel(Text* label)
{
	label->transformation.position += transformation.position;
	label->transformation.UpdateMatrix();
	labels->push_back(label);
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

	for (int i = labels->size() - 1; i >= 0; i --) {
		labels->at(i)->Release();
		delete labels->at(i);
		labels->at(i) = NULL;
	}
	delete labels;
	labels = NULL;
}

void Panel::Draw() {
	for (int i = buttons->size() - 1; i >= 0; i--) {
		buttons->at(i)->Draw();
	}

	for (int i = labels->size() - 1; i >= 0; i--) {
		labels->at(i)->Draw();
	}

}