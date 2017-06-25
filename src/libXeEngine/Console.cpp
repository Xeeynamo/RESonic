#include "Console.h"
#include <stdio.h>
#include <stdarg.h>

#ifdef PLATFORM_WINDOWS
#include <windows.h>
#else
#endif

Console::Console()
{
	fConsole = NULL;
	hConsoleOut = NULL;
}
Console::~Console()
{
	Destroy();
}

void Console::Create()
{
#ifdef PLATFORM_WINDOWS
	// Crea una console in Windows
	AllocConsole();
#else
#endif
	// Apre stdout nella console per permettere l'uso di printf, putc etc
	freopen_s((FILE**)&fConsole, "CONOUT$", "w+b", stdout);
	if (fConsole)	// Se stdout è stato correttamente aperto
	{
#ifdef PLATFORM_WINDOWS
		// Allora ottieni l'handle della STDOUT
		hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
#else
#endif
	}
	else // altrimenti se c'è stato un errore
	{
#ifdef PLATFORM_WINDOWS
		// Dealloca una console in Windows
		FreeConsole();
#else
#endif
	}
}
void Console::Destroy()
{
	/*if (fConsole)
		fclose((FILE*)fConsole);*/
}
void Console::GetBufferSize(short *x, short *y)
{
#ifdef PLATFORM_WINDOWS
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	GetConsoleScreenBufferInfo(hConsoleOut, &screenBufferInfo);
	*x = screenBufferInfo.dwCursorPosition.X;
	*y = screenBufferInfo.dwCursorPosition.Y;
#else
#endif
}
void Console::SetBufferSize(short x, short y)
{
#ifdef PLATFORM_WINDOWS
	COORD coord = {x, y};
	SMALL_RECT rect = {0, 0, x-1, y-1};
	SetConsoleWindowInfo(hConsoleOut, true, &rect);
	SetConsoleScreenBufferSize(hConsoleOut, coord);
#else
#endif
}
void Console::Clear()
{
#ifdef PLATFORM_WINDOWS
	short w, h;
	GetBufferSize(&w, &h);
	COORD coord = {0, 0};
	DWORD charsWritten;
	FillConsoleOutputCharacter(hConsoleOut, 0, w * h, coord, &charsWritten);
	SetXY(0, 0);
#else
#endif
}
void Console::SetXY(short x, short y)
{
#ifdef PLATFORM_WINDOWS
	COORD coord = {x , y};
	SetConsoleCursorPosition(hConsoleOut, coord);
#else
#endif
}
void Console::SetColor(ConsoleColor background, ConsoleColor foreground)
{
#ifdef PLATFORM_WINDOWS
	SetConsoleTextAttribute(hConsoleOut, foreground | (background<<4));
#else
#endif
}
void Console::Print(char *string, ...)
{
	char str[0x800];
	va_list args;
	va_start(args, string);
	vsprintf_s(str, string, args);
	printf(str);
	va_end(args);
}