#include "WindowManager.h"

WNDCLASS WindowManager::wndClass;

LRESULT CALLBACK WindowManager::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void WindowManager::CreateMyWindow() {
	/*
		Step 1
		Define and Register a Window.
	*/

	//	Sset all members in wndClass to 0.

	ZeroMemory(&wndClass, sizeof(wndClass));

	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = GetModuleHandle(NULL);	//	GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowManager::WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	Register the window.
	RegisterClass(&wndClass);

	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Walking on a Spaceship", WS_OVERLAPPEDWINDOW, 0, 100, MyWindowWidth, MyWindowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(g_hWnd, 1);

	/*
		Step 2
		Create the Window.
	*/
}

void WindowManager::CleanUpMyWindow(){
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL));
}

bool WindowManager::MyWindowIsRunning() { 
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	/*
		Step 3
		Handling window messages
		NOTE! There are several ways of writing the message loop.
		You have to based on which kind of application your are writing.
	*/
	//while (msg.message != WM_QUIT)
	//{
		/*
			The if- version process one message per one iteration loop
			The while- version will clear the message queue before dealing with your own code.

			Another function is GetMessage.
			This function is not suitable for game, because it will block your program until it recieves a message.
			your code will only executed when you have messages, otherwies your pogram will be waiting... (similar to cin)
			Suitable for event based program, such as bussiness app.
		*/
		//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT)
			return false;
		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);
	}

	return true;
}