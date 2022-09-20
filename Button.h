#pragma once
#include "Text.h"
#include "Texture.h"

class Button
{
	Text *label;
	Texture* texture;

	
	Button(LPCSTR label, Texture** ppTexture);

};

