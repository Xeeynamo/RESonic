#include "CLI.h"

CLI::CLI()
{
	data = 0;
	*(int*)&header = 0;
}
CLI::~CLI()
{

}

bool CLI::Load(char *filename)
{
	file.Close();
	if (!file.Open(XeEngine::String(filename), true))
		return false;
	file.Read(&header, sizeof(CLIHeader));
	return true;
}
bool CLI::Save(char *filename)
{
	if (!data) return false;
	file.Close();
	if (!file.Create(XeEngine::String(filename)))
		return false;
	file.Write(&header, sizeof(CLIHeader));
	file.Write(data, header.count*header.paths);
	file.Close();
	return Load(filename);
}

short CLI::Count()
{
	return header.count;
}
void CLI::Count(short count)
{
	header.count = count;
}
char CLI::Paths()
{
	return header.paths;
}
void CLI::Paths(char count)
{
	header.paths = count;
}
void CLI::SetData(void *data)
{
	this->data = data;
	file.Read(data, header.count*header.paths);
}