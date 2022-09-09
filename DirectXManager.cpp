#include "DirectXManager.h"
#include <iostream>


IDirect3DDevice9* DirectXManager::d3dDevice;
LPDIRECTINPUT8 DirectXManager::dInput;
LPDIRECTINPUTDEVICE8 DirectXManager::dInputKeyboardDevice;
LPDIRECTINPUTDEVICE8 DirectXManager::dInputMouseDevice;
BYTE DirectXManager::diKeys[256];
DIMOUSESTATE DirectXManager::mouseState;

LPD3DXSPRITE DirectXManager::spriteBrush;
LPD3DXLINE DirectXManager::lineBrush;

void DirectXManager::CreateMyDX(HWND g_hWnd) {
	//	Define Direct3D 9. [Object]
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	//	Define how the screen presents.
	D3DPRESENT_PARAMETERS d3dPP;
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = MyWindowWidth;
	d3dPP.BackBufferHeight = MyWindowHeight;
	d3dPP.hDeviceWindow = g_hWnd;

	//	Create a Direct3D 9 device. [Virtual Graphic Card]
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL /*D3DDEVTYPE_REF*/, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

	direct3D9->Release();
	direct3D9 = NULL;

	


	//spriteBrush
	hr = D3DXCreateSprite(d3dDevice, &spriteBrush);
	if (FAILED(hr)) {
		std::cout << "sprite fail" << std::endl;
	}

	//lineBrush

	hr = D3DXCreateLine(d3dDevice, &lineBrush);
	if (FAILED(hr)) {
		std::cout << "line fail" << std::endl;
	}
}

void DirectXManager::CreateMyDInput(HWND g_hWnd) {

	//	Create the Direct Input object.
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);

	//	Set the input data format.
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	//	Set the cooperative levels
	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);


	/*MOUSE*/
	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);

	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
	dInputMouseDevice->SetCooperativeLevel(g_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);

}

void DirectXManager::CleanUpMyDInput() {
	//	Release keyboard device.
	dInputKeyboardDevice->Unacquire();

	//	Release DirectInput.
	dInput->Release();
	dInput = NULL;

	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;
	
	dInputMouseDevice->Release();
	dInputMouseDevice = NULL;


}

void DirectXManager::CleanUpMyDX() {
	d3dDevice->Release();
	d3dDevice = NULL;

	spriteBrush->Release();
	spriteBrush = NULL;

	lineBrush->Release();
	lineBrush = NULL;
}
