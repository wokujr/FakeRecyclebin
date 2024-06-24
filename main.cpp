#include "MainWindow.h"
#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	FILE* stream;
	AllocConsole();
	freopen_s(&stream, "CONOUT$", "w", stdout);
	freopen_s(&stream, "CONOUT$", "w", stdin);
	

	MainWindow mainWindow(hInstance);
	mainWindow.Show(nCmdShow);

	FreeConsole();
	return 0;
}