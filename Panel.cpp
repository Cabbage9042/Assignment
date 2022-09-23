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

	for (auto slider : *this->sliders) {
		slider->Move(vector);
	}

}

void Panel::CreateButton(Button* button){
	button->texture->relativePosition = button->texture->transformation.position;
	button->texture->transformation.position += transformation.position;
	button->texture->updatePositionRect();
	button->texture->transformation.UpdateMatrix();

	button->label->relativePosition = button->label->transformation.position;
	button->label->transformation.position += transformation.position;
	button->label->updatePositionRect();
	button->label->transformation.UpdateMatrix();

	buttons->push_back(button);

}

void Panel::CreateLabel(Text* label)
{
	label->relativePosition = label->transformation.position;
	label->transformation.position += transformation.position;
	label->updatePositionRect();
	label->transformation.UpdateMatrix();
	labels->push_back(label);
}

void Panel::CreateSlider(Slider* slider)
{
	slider->bar->relativePosition = slider->bar->transformation.position;
	slider->bar->transformation.position+=transformation.position;
	slider->bar->updatePositionRect();
	slider->bar->transformation.UpdateMatrix();

	slider->handle->relativePosition = slider->handle->transformation.position;
	slider->handle->transformation.position+=transformation.position;
	slider->handle->updatePositionRect();
	slider->handle->transformation.UpdateMatrix();

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