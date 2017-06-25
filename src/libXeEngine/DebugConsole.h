#pragma once
#include "Console.h"

enum DEBUG_LEVEL
{
	DEBUG_LEVEL_NONE		= 0,
	DEBUG_LEVEL_HIGHPRIORITY= 0,
	DEBUG_LEVEL_ERROR		= 1,
	DEBUG_LEVEL_WARNING		= 2,
	DEBUG_LEVEL_INFO		= 3,
	DEBUG_LEVEL_EVERYTHING	= 4,
	DEBUG_LEVEL_DEFAULT		= 4,
};

namespace XeEngine
{
	class File;
}
class DebugConsole : public Console
{
private:
protected:
	DEBUG_LEVEL level;
	int funcitondepth;
	XeEngine::File *file;
public:
	DebugConsole();
	~DebugConsole();

	void SetDebugLevel(DEBUG_LEVEL);
	void Log(DEBUG_LEVEL, char *message, ...);
	void EnterFunction(char *function_name);
	void ExitFunction();
	bool isWriteOnFile();
	void WriteOnFile(bool);
};