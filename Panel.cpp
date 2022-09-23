#include "Panel.h"

void Panel::Move(D3DXVECTOR2 vector)
{
	this->transformation.addPosition(vector);
	this->updatePositionRect();

	for (auto button : *this->buttons) {
		button->Move(vector);
	}

	for (auto label : *this->labels) {
		label->Move(vector);
	}

	for (auto slider : *this->sliders) {
		slider->Move(vector);
	}

}

void Panel::CreateButton(Button* button){
	button->texture->relativePosition = button->texture->getPosition();
	button->texture->addPosition(getPosition());

	button->label->relativePosition = button->label->transformation.getPosition();
	button->label->addPosition(getPosition());

	buttons->push_back(button);

}

void Panel::CreateLabel(Text* label)
{
	label->relativePosition = label->getPosition();
	label->addPosition(getPosition());
	labels->push_back(label);
}

void Panel::CreateSlider(Slider* slider)
{
	slider->bar->relativePosition = slider->bar->getPosition();
	slider->bar->addPosition(getPosition());
	slider->bar->updatePositionRect();

	slider->handle->relativePosition = slider->handle->getPosition();
	slider->handle->addPosition(getPosition());
	slider->handle->updatePositionRect();

	sliders->push_back(slider);
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
	if (this->getPosition().x >= MyWindowWidth || this->getPosition().x + this->textureWidth <= 0) {
		return;
	}

	for (int i = buttons->size() - 1; i >= 0; i--) {
		buttons->at(i)->Draw();
	}

	for (int i = labels->size() - 1; i >= 0; i--) {
		labels->at(i)->Draw();
	}

	for (int i = sliders->size() - 1; i >= 0; i--) {
		sliders->at(i)->Draw();
	}

}