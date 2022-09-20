#include "Button.h"

Button::Button(Text* label, Texture** ppTexture)
{
	texture = *ppTexture;
	this->label = label;
	this->label->transformation.position +=
		texture->transformation.position;
	
}

void Button::Release(){
	label->Release();
	label = NULL;
	texture = NULL;
}
