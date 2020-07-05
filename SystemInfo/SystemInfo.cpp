// SystemInfo.cpp : Defines the entry point for the application.
//
#pragma once
#include "stdafx.h"
#include "MainWindow.h"

// Global Variables:
#define MAX_LOADSTRING 100

HWND hWnd;
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	// init common controls to allow usage!
	InitCommonControls();
	MainWindow mainwindow;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SYSTEMINFO, szWindowClass, MAX_LOADSTRING);

	// Perform application initialization:
	hInst = hInstance;
	hWnd = mainwindow.Create(NULL, NULL); //Conflicting name if not using whole name

	int i = GetLastError();
	ShowWindow(hWnd, nCmdShow);
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SYSTEMINFO));

	// Main message loop:
	while(GetMessage(&msg, NULL, 0, 0))
	{
		if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int) msg.wParam;
}