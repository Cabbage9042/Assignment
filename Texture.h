#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#pragma comment(lib, "d3dx9.lib")
#include "StuffToBeDrawn.h"
using namespace std;


/*	Call updateRect if rect need to be calculate automatically
		-the rect cover the whole texture (without the part need to be crop)

	Call SetTransform if scaling / rotation is applied
*/
class Texture : public StuffToBeDrawn {
public:
	LPDIRECT3DTEXTURE9 texture = NULL;

	void Release();
	void updateCropRect();
	void Draw();

	Texture(LPDIRECT3DTEXTURE9 pTexture,
		int pTextureWidth,
		int pTextureHeight,
		D3DXVECTOR2 pPosition,
		int pAlignFrom = leftAlign,
		D3DCOLOR pColor = D3DCOLOR_XRGB(255, 255, 255)) :
	StuffToBeDrawn(pPosition,pTextureWidth,pTextureHeight,pAlignFrom,pColor) {

		texture = pTexture;

	}

	Texture() :StuffToBeDrawn() {}

};

