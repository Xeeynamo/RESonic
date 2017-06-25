#include "XeEngine.h"
#include "Game.h"
#include "MainEditor.h"
#include "Editor.h"
#include "DebugConsole.h"
DebugConsole con;

#define USE_OLD_EDITOR 0

HINSTANCE hInst;
extern HDC hDC;
extern Game *game;
extern Editor::MainEditor *meditor;
extern XeEditor *editor;
extern bool vsync;

bool Win_RegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass, LPTSTR menu)
{
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	return RegisterClassEx(&wcex) ? true : false;
}

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	hInst = hInstance;
	if (!Win_RegisterClass(hInstance, _T(WND_NAME_CLASS), MAKEINTRESOURCE(IDR_MAIN_MENU)))
	{
		MessageBox(NULL, _T("Win_RegisterClass failed!"), _T("Error"), MB_ICONERROR);
		return -1;
	}
	HWND hWnd = CreateWindow(
		_T(WND_NAME_CLASS),				// Nome classe
		_T(WND_NAME_TITLE),				// Nome della finestra
		WS_OVERLAPPEDWINDOW,			// Proprietà
		CW_USEDEFAULT, CW_USEDEFAULT,	// Posizione
		800+16, 480+39,					// Dimensione
		NULL,							// Finestra padre
		NULL,							// Menu
		hInstance,						// Istanza
		NULL							// Parametro
		);
	if (!hWnd)
	{
		MessageBox(NULL, _T("CreateWindow failed!"), _T("Error"), MB_ICONERROR);
		return -2;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	con.Create();
	//con.SetDebugLevel(DEBUG_LEVEL_NONE);
	SetConsoleTitle("XeEngine Debug console");
	MSG msg;
	while(1)
	{
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else if (vsync)
		{
			// Background input
			/*editor->InputKey(VK_LEFT, GetAsyncKeyState(VK_LEFT)==0 ? true : false);
			editor->InputKey(VK_RIGHT, GetAsyncKeyState(VK_RIGHT)==0 ? true : false);
			editor->InputKey(VK_UP, GetAsyncKeyState(VK_UP)==0 ? true : false);
			editor->InputKey(VK_DOWN, GetAsyncKeyState(VK_DOWN)==0 ? true : false);
			editor->InputKey('A', GetAsyncKeyState('A')==0 ? true : false);
			editor->InputKey('S', GetAsyncKeyState('S')==0 ? true : false);
			editor->InputKey('D', GetAsyncKeyState('D')==0 ? true : false);*/

#if USE_OLD_EDITOR == 1
			if (editor->EditorMode == 0)
#else
			if (meditor->GetMode() == 0)
#endif
			{
				game->Do();
				game->Draw();
			}
#if USE_OLD_EDITOR == 1
			editor->Draw();
#else
			meditor->Draw();
#endif
			SwapBuffers(hDC);
			vsync = false;
		}
	}
	con.Destroy();
	return (int) msg.wParam;
}