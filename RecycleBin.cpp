#include "RecycleBin.h"

#include <fstream>
#include <sstream>
#include <string>


RecycleBin::RecycleBin(HWND hwnd)
{
}

RecycleBin::~RecycleBin()
{
}

void RecycleBin::MoveToRecycleBin(const wchar_t* filepath)
{
	SHFILEOPSTRUCT fileOp;
	ZeroMemory(&fileOp, sizeof(fileOp));
	fileOp.hwnd = m_hWnd;
	fileOp.wFunc = FO_DELETE;
	fileOp.pFrom = filepath;
	fileOp.fFlags = FOF_ALLOWUNDO | FOF_SILENT | FOF_NOCONFIRMATION;

	SaveOriginalPath(filepath, filepath);

	SHFileOperation(&fileOp);
}

void RecycleBin::RestoreFromRecycleBin(const wchar_t* filepath)
{
	std::wstring originalPath = getOriginalPath(filepath);
	if (originalPath.empty())
	{
		MessageBox(m_hWnd, L"Original path not found!", L"Error", MB_ICONERROR);
		return;
	}

	SHFILEOPSTRUCT fileOp;
	ZeroMemory(&fileOp, sizeof(fileOp));
	fileOp.hwnd = m_hWnd;
	fileOp.wFunc = FO_MOVE;
	fileOp.pFrom = filepath;
	fileOp.pTo = originalPath.c_str();
	fileOp.fFlags = FOF_SILENT | FOF_NOCONFIRMATION;

	SHFileOperation(&fileOp);
}

void RecycleBin::DeleteFromRecycleBin(const wchar_t* filepath)
{
	if (DeleteFile(filepath)) {
		MessageBox(m_hWnd, L"File permanently deleted!", L"Information", MB_ICONINFORMATION);
	}
	else {
		MessageBox(m_hWnd, L"Failed to delete file!", L"Error", MB_ICONERROR);
	}
}

std::wstring RecycleBin::getOriginalPath(const wchar_t* filePath) {
	std::wstring metadataFile = std::wstring(filePath) + L".meta";
	std::wifstream inFile(metadataFile);
	if (!inFile.is_open()) {
		return L"";
	}

	std::wstringstream buffer;
	buffer << inFile.rdbuf();
	inFile.close();

	return buffer.str();
}

void RecycleBin::SaveOriginalPath(const wchar_t* filePath, const std::wstring& originalPath)
{
	std::wstring metadataFile = std::wstring(filePath) + L".meta";
	std::wofstream outFile(metadataFile);
	if (!outFile.is_open())
	{
		MessageBox(m_hWnd, L"Failed to save metadata!", L"Error", MB_ICONERROR);
		return;
	}
	outFile << originalPath;
	outFile.close();

}

