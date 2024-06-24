#include "MainWindow.h"
#include <CommCtrl.h>
#include <iostream>
#include <shellapi.h>

MainWindow::MainWindow(HINSTANCE hInstance) : m_hInstance(hInstance), m_pRecycleBin(nullptr) {}

MainWindow::~MainWindow() {
    delete m_pRecycleBin;
}

void MainWindow::Show(int nCmdShow) {
    // Load recycle bin icons from shell32.dll
    HICON hIconFull = LoadIcon(GetModuleHandle(L"shell32.dll"), MAKEINTRESOURCE(32));
    HICON hIconEmpty = LoadIcon(GetModuleHandle(L"shell32.dll"), MAKEINTRESOURCE(31));

    // Register window class
    WNDCLASS wc = { };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = L"RecycleBinApp";
    wc.hIcon = hIconFull; // Use full recycle bin icon for the window

    RegisterClass(&wc);

    // Create main window
    m_hWnd = CreateWindowEx(0, L"RecycleBinApp", L"Fake Recycle Bin", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 400, NULL, NULL, m_hInstance, this);

    if (!m_hWnd) return;

    SetWindowLongPtr(m_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    ShowWindow(m_hWnd, nCmdShow);
    UpdateWindow(m_hWnd);

    // Create RecycleBin instance
    m_pRecycleBin = new RecycleBin(m_hWnd);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Cleanup icons
    DestroyIcon(hIconFull);
    DestroyIcon(hIconEmpty);
}

LRESULT CALLBACK MainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    MainWindow* pThis = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (message) {
    case WM_CREATE: {
        // Create list view control
        HWND hListView = CreateWindowEx(0, WC_LISTVIEW, L"", WS_CHILD | WS_VISIBLE | LVS_REPORT,
            10, 10, 400, 300, hWnd, NULL, NULL, NULL);
        DragAcceptFiles(hWnd, TRUE); // Enable drag-and-drop
        break;
    }
    case WM_DROPFILES: {
        // Handle dropped files
        HDROP hDrop = (HDROP)wParam;
        wchar_t szFileName[MAX_PATH];
        UINT nFiles;

        hDrop = (HDROP)wParam;
        nFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);

        for (UINT i = 0; i < nFiles; i++) {
            DragQueryFile(hDrop, i, szFileName, MAX_PATH);
            // Move file to recycle bin
            std::wcout << L"Dropped file: " << szFileName << std::endl;

            // Move file to recycle bin (faked)
            if (pThis && pThis -> m_pRecycleBin)
            {
                pThis->m_pRecycleBin->MoveToRecycleBin(szFileName);
            }
            else
            {
                std::wcerr << L"RecycleBin instance is not initialized" << std::endl;
            }

        }

        DragFinish(hDrop);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
