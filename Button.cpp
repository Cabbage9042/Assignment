#include "Button.h"

Button::Button(Texture* ppTexture, Text* label)
{
	texture = ppTexture;
	this->label = label;
	this->label->transformation.position +=
		texture->transformation.position;

	this->label->transformation.UpdateMatrix();
	this->label->updatePositionRect();
}


void Button::Move(D3DXVECTOR2 vector)
{
	texture->transformation.position += vector;
	texture->updatePositionRect();
	texture->transformation.UpdateMatrix();

	label->transformation.position += vector;
	label->updatePositionRect();
	label->transformation.UpdateMatrix();
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
