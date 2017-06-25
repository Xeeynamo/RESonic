#pragma once

//////////////////////////////////////////////////////////////////////////
// XeEngine stuff
#include "XeBase.h"
#include "XeFormats.h"
#include "XeTexture.h"
#include "XeFont.h"
#include "XeFormats.h"

//////////////////////////////////////////////////////////////////////////
// Windows stuff
#include <windows.h>
#include <tchar.h>
#include "resource.h"
#define WND_NAME_CLASS	"XEENGINE"
#define WND_NAME_TITLE	"XeEngine"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
