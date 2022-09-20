#include "Button.h"

Button::Button(LPCSTR label, Texture** ppTexture)
{
	texture = *ppTexture;
	this->label = new Text();
}
