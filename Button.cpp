#include "Button.h"

Button::Button(Texture* ppTexture, Text* label, D3DXVECTOR2 panelPosition)
{
	texture = ppTexture;
	texture->transformation.position += panelPosition;
	this->label = label;
	this->label->transformation.position +=
		texture->transformation.position;
	this->texture->transformation.UpdateMatrix();
	this->texture->updatePositionRect();
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
