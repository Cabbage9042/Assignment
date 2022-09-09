#pragma once

#ifndef GAME_HEADER
#define GAME_HEADER

#include <iostream>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>

#include "Texture.h"
#include "Text.h"
#include "Sprite.h"

struct KeyStatus {
	bool isPressed = false, isHolding = false, isReleased = true;
};

using namespace std;

class Game {
public:
	//Texture, Sprite
	vector<Texture*> *textures;
	vector<Text*> *texts;
	vector<Sprite*>* sprites;
	//vector<vector<D3DXVECTOR2>*> *vertices;

	virtual void InitializeLevel() = 0;

	virtual void GetInput() = 0;
	virtual void Update(int framesToUpdate) = 0;
	virtual void Render() = 0;

	virtual void UninitializeLevel() = 0;

};

#endif // !GAME_HEADER