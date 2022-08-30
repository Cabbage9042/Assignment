#pragma once



#include "WindowManager.h"
#include "DirectXManager.h"

#define KeyDown(name) Shell::directXManager.diKeys[name] & 0x80
#define ButtonDown(name) Shell::directXManager.mouseState.rgbButtons[name] & 0x80

#define gameFPS 60


enum { arial25, franklin100 };

class Shell {
public:
	static WindowManager windowManager;
	static DirectXManager directXManager;
	
};

