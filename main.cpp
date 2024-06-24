#include "MainWindow.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MainWindow mainWindow(hInstance);
	mainWindow.Show(nCmdShow);

	return 0;
}