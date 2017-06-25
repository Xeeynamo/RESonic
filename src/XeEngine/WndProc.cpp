#include "XeEngine.h"
#include "Game.h"
#include "Editor.h"
#include "XeAnimation.h"
#include "MainEditor.h"

HDC hDC;
HGLRC hRC;
Game *game;
XeEditor *editor;
Editor::MainEditor *meditor;
XeScene scene;
bool vsync;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_CREATE:
	{
		ShowCursor(FALSE);
		//S1_LevelConvertAll();
		//S1_GFXConverterAll();

		//S2_GFXConverterAll();
		//S2_BLKConverterAll();

		//CSOTN_TotalExport("X:\\Reverse\\Castlevania SOTN\\ST", "CSOTN");
		//S1LVL_GFXConverterAll();
		//S1LVL_BLKConverterAll();
		//S1LVL_ColIndexConvertAll();
		//S1LVL_MapConvertAll();
		//S2_ColIndexConvertAll();
		//S2_MapConvertAll();

		int nMyPixelFormatID;
		static PIXELFORMATDESCRIPTOR pfd = {
			sizeof (PIXELFORMATDESCRIPTOR), // strcut size 
			1,                              // Version number
			PFD_DRAW_TO_WINDOW	|			// Flags, draw to a window,
			PFD_DOUBLEBUFFER	|
			PFD_SUPPORT_OPENGL,				// use OpenGL
			PFD_TYPE_RGBA,					// RGBA pixel values
			24,								// 24-bit color
			0, 0, 0,						// RGB bits & shift sizes.
			0, 0, 0,						// Don't care about them
			0, 0,							// No alpha buffer info
			0, 0, 0, 0, 0,					// No accumulation buffer
			32,								// 32-bit depth buffer
			0,								// No stencil buffer
			0,								// No auxiliary buffers
			PFD_MAIN_PLANE,					// Layer type
			0,								// Reserved (must be 0)
			0,								// No layer mask
			0,								// No visible mask
			0								// No damage mask
		};
		hDC = GetDC(hWnd);
		nMyPixelFormatID = ChoosePixelFormat(hDC, &pfd);
		SetPixelFormat(hDC, nMyPixelFormatID, &pfd);
		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);

		// Game init
		scene.Initialize();
		game = new Game;
		game->SetScene(&scene);
		game->SetResolution(400, 240);
		game->LoadGFXFont("FONT\\S2@1.GFX");
		game->LoadGFXCLUT("FONT\\S2.LUT");

		editor = new XeEditor;
		editor->AttachGame(game);
		editor->AttachScene(&scene);
		editor->ShowFPS(true);
		editor->hWnd = hWnd;

		meditor = new Editor::MainEditor(game);
		meditor->setShowFps(true);

		//game->level.LoadStage("S1GHZ");
		game->level.SetDepthResolution(2);

		SetTimer(hWnd, 0, 15, NULL);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_SIZE:
		scene.SetRenderSize(LOWORD(lParam), HIWORD(lParam));
		scene.SetCameraSize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_PAINT:
		vsync = true;
		ValidateRect(hWnd, NULL);
		break;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_NCMOUSEMOVE:
		break;
	case WM_MOUSEWHEEL:
		editor->InputWheel((signed short)HIWORD(wParam)/120);
		meditor->InputWheel((signed short)HIWORD(wParam)/120);
		wParam = 0;
	case WM_KEYDOWN:
		editor->InputKey(wParam, false);
		meditor->InputKeyb(wParam, false);
		break;
	case WM_KEYUP:
		editor->InputKey(wParam, true);
		meditor->InputKeyb(wParam, true);
		break;
	case WM_CHAR:
		editor->InputChar(wParam);
		meditor->InputChar(wParam);
		break;
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		editor->InputMouse(LOWORD(lParam), HIWORD(lParam), wParam);
		meditor->InputMouse(LOWORD(lParam), HIWORD(lParam), wParam);
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
		editor->InputMouse(LOWORD(lParam), HIWORD(lParam), 0);
		meditor->InputMouse(LOWORD(lParam), HIWORD(lParam), 0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}