#include "Text.h"
#include "Game.h"
#include "Shell.h"

void Text::updateCropRect() {
	font->DrawTextA(NULL, text, strlen(text), &cropRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));

	textureHeight = cropRect.bottom - cropRect.top;
	textureWidth = cropRect.right - cropRect.left;


}

void Text::Release() {
	font = NULL;
}

void Text::Draw() {
	Shell::directXManager.spriteBrush->SetTransform(&transformation.matrix);
	font->DrawTextA(Shell::directXManager.spriteBrush, text, strlen(text), &cropRect, 0, color);

}

