#pragma once
#include "Text.h"
#include "Texture.h"
#include "Shell.h"

class Button
{
public:
	

	Text *label;
	Texture* texture;

	/// <summary>
	/// position in texture is relative position in panel
	/// position in label   is relative position in button
	/// </summary>
	/// <param name="label"></param>
	/// <param name="ppTexture"></param>
	void Release();
	void Draw();
	bool isClicked(StuffToBeDrawn* pointer, bool mouseIsPressed);
	bool isBeingHover(StuffToBeDrawn* pointer);
	Button(Texture* ppTexture, Text*label,D3DXVECTOR2 panelPosition);
};

