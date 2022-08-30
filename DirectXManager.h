#pragma once

#include "WindowManager.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")



class DirectXManager {
public:
	static IDirect3DDevice9* d3dDevice;	//d3d device Virtual Graphic Card
	static LPDIRECTINPUT8 dInput;
	static LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
	static LPDIRECTINPUTDEVICE8 dInputMouseDevice;
	static BYTE  diKeys[256];
	static DIMOUSESTATE mouseState;

	//spriteBrush
	static LPD3DXSPRITE spriteBrush;


	void CreateMyDX(HWND g_hWnd);
	void CreateMyDInput(HWND g_hWnd);

	void CleanUpMyDInput();
	void CleanUpMyDX();


};

