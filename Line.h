#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "Shell.h"

class Line{
public:
	std::vector<D3DXVECTOR2> *vertices = NULL;
	D3DCOLOR color;
	float size;
	

	Line(std::vector<D3DXVECTOR2>* vertices,bool closing = true, float size = 1.0f, D3DCOLOR color =  D3DCOLOR_XRGB(255, 255, 255));

	void Draw();
	void Release();


	static void DrawLines(std::vector<Line*>* vertices);
	
private:
bool closing;
};

