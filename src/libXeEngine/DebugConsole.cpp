#include "DebugConsole.h"
#include "File.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define WRTIE_STRING(f, s) f->Write(s, strlen(s));

DebugConsole::DebugConsole()
{
	Create();
	SetDebugLevel(DEBUG_LEVEL_EVERYTHING);
	funcitondepth = 0;
}
DebugConsole::~DebugConsole()
{
	if (file)
		delete file;
	Destroy();
}

void DebugConsole::SetDebugLevel(DEBUG_LEVEL lvl)
{
	level = lvl;
}
void DebugConsole::Log(DEBUG_LEVEL lvl, char *message, ...)
{
	if (lvl > level) return;
	char str[0x800];
	va_list args;
	va_start(args, message);

	switch(lvl)
	{
	case DEBUG_LEVEL_HIGHPRIORITY:
		SetColor(ConsoleColor_Black, ConsoleColor_LightPurple);
		break;
	case DEBUG_LEVEL_ERROR:
		SetColor(ConsoleColor_Black, ConsoleColor_LightRed);
		Print("ERROR: ");
		break;
	case DEBUG_LEVEL_WARNING:
		SetColor(ConsoleColor_Black, ConsoleColor_LightYellow);
		Print("WARNING: ");
		break;
	case DEBUG_LEVEL_INFO:
		SetColor(ConsoleColor_Black, ConsoleColor_LightCyan);
		Print("INFO: ");
		break;
	case DEBUG_LEVEL_DEFAULT:
		SetColor(ConsoleColor_Black, ConsoleColor_LightWhite);
		break;
	}
	vsprintf_s(str, message, args);
	Print(str);
	Print("\n");
	va_end(args);
	SetColor(ConsoleColor_Black, ConsoleColor_White);

	/*if (file)
	{
		char space = '\t';
		char carret = '\r';
		char newline = '\n';
		for(int i=0; i<funcitondepth; i++) file->Write(&space, 1);
		file->Write(str, strlen(str));
		file->Write(&carret, 1);
		file->Write(&newline, 1);
	}*/
}

void DebugConsole::EnterFunction(char *function_name)
{
	/*if (!isWriteOnFile()) return;
	if (DEBUG_LEVEL_INFO > level) return;
	char space = '\t';
	char ch1 = '\r';
	char ch2 = '\n';
	char ch3 = '{';
	for(int i=0; i<funcitondepth; i++) file->Write(&space, 1);
	file->Write(function_name, strlen(function_name));
	file->Write(&ch1, 1);
	file->Write(&ch2, 1);
	for(int i=0; i<funcitondepth; i++) file->Write(&space, 1);
	file->Write(&ch3, 1);
	file->Write(&ch1, 1);
	file->Write(&ch2, 1);
	funcitondepth++;*/
}
void DebugConsole::ExitFunction()
{
	/*if (!isWriteOnFile()) return;
	if (DEBUG_LEVEL_INFO > level) return;
	char space = '\t';
	char ch1 = '\r';
	char ch2 = '\n';
	char ch3 = '}';
	funcitondepth--;
	for(int i=0; i<funcitondepth; i++) file->Write(&space, 1);
	file->Write(&ch3, 1);
	file->Write(&ch1, 1);
	file->Write(&ch2, 1);*/
}
bool DebugConsole::isWriteOnFile()
{
	return file != 0;
}
void DebugConsole::WriteOnFile(bool enabled)
{
	/*if (enabled)
	{
		if (file) return;
		file = new XeEngine::File;
		file->Create(XeEngine::String("XeEngine.log"));
		Log(DEBUG_LEVEL_HIGHPRIORITY, "XeEngine log system");
	}
	else
	{
		if (!file) return;
		delete file;
		file = NULL;
	}*/
}