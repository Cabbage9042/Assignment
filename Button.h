#pragma once
#include "Text.h"
#include "Texture.h"

class Button
{
public:
	Text *label;
	Texture* texture;

	/// <summary>
	/// position in label   is relative position in button
	/// position in texture is relative position in panel
	/// </summary>
	/// <param name="label"></param>
	/// <param name="ppTexture"></param>
	Button(Text *label, Texture** ppTexture);
	void Release();
};

