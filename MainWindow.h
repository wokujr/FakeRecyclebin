#pragma once
#include "RecycleBin.h"
#include <Windows.h>

class MainWindow
{
public:
	MainWindow(HINSTANCE hInstance);
	~MainWindow();

	void Show(int nCmdShow);

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	RecycleBin* m_pRecycleBin;


};