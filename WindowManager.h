#ifndef WINDOW_HEADER
#define WINDOW_HEADER
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//macro
#define MyWindowWidth 1280
#define MyWindowHeight 720


class WindowManager {
public:
	static WNDCLASS wndClass;
	HWND g_hWnd;

	void CreateMyWindow();
	void CleanUpMyWindow();
	bool MyWindowIsRunning();
	static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

#endif 