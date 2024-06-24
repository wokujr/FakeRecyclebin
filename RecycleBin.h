#pragma once

#include <Windows.h>
#include <ShlObj.h>
#include <string>

class RecycleBin
{
public:
	RecycleBin(HWND hwnd);
	~RecycleBin();

	void MoveToRecycleBin(const wchar_t* filepath);
	void RestoreFromRecycleBin(const wchar_t* filepath);
	void DeleteFromRecycleBin(const wchar_t* filepath);

private:
	HWND m_hWnd;
	std::wstring getOriginalPath(const wchar_t* filePath);
	void SaveOriginalPath(const wchar_t* filePath, const std::wstring& originalPath);

};
