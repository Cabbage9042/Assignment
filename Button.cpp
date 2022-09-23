#include "Button.h"

Button::Button(Texture* ppTexture, Text* label)
{
	texture = ppTexture;
	this->label = label;
	this->label->addPosition(texture->getPosition());

	this->label->updatePositionRect();
}


void Button::Move(D3DXVECTOR2 vector)
{
	texture->addPosition(vector);
	label->addPosition(vector);
}

void Button::Release() {
	label->Release();
	label = NULL;
	texture = NULL;
}

void Button::Draw()
{
	texture->Draw();
	label->Draw();
}

bool Button::isClicked(StuffToBeDrawn* pointer, bool mouseIsPressed)
{
	return isBeingHover(pointer) && mouseIsPressed;
}

bool Button::isBeingHover(StuffToBeDrawn* pointer)
{
	return pointer->isHoverOn(this->texture);
}
