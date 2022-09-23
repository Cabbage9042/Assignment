#pragma once
#include <iostream>
#include "Texture.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#pragma comment(lib, "d3dx9.lib")
#include "Shell.h"

using namespace std;


void Texture::updateCropRect() {
	cropRect.left = cropRect.top = 0;
	cropRect.right = textureWidth;
	cropRect.bottom = textureHeight;
}

void Texture::Draw() {
	this->transformation.UpdateMatrix();
	Shell::directXManager.spriteBrush->SetTransform(
		&transformation.matrix
	);
	Shell::directXManager.spriteBrush->Draw(
		texture,
		&cropRect, NULL, NULL, color);

}

void Texture::Release() {
	texture->Release();
	texture = NULL;
}
