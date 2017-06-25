#pragma once
#include "XeEngineLV1.h"
#include "XeFile.h"

struct CLIHeader
{
	short count;
	byte paths;
	byte reserved;
};
class CLI
{
private:
protected:
	void *data;
	XeEngine::File file;
	CLIHeader header;
public:
	CLI();
	~CLI();

	bool Load(char *filename);
	bool Save(char *filename);

	short Count();
	void Count(short);
	char Paths();
	void Paths(char);

	void SetData(void*);
};