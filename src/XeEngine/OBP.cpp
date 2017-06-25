#include "OBP.h"

OBP::OBP()
{
	data = 0;
	entries = 0;
	*(int*)&header = 0;
}
OBP::~OBP()
{

}

bool OBP::Load(char *filename)
{
	if (entries) delete entries;
	file.Close();
	if (!file.Open(XeEngine::String(filename), true))
		return false;
	file.Read(&header, sizeof(OBPHeader));
	entries = new OBPEntry[header.count];
	file.Read(entries, header.count * sizeof(OBPEntry));
	file.Close();
	return true;
}
bool OBP::Save(char *filename)
{
	/*if (!data) return false;
	file.Close();
	if (!file.Create(filename))
		return false;
	file.Write(&header, sizeof(OBPHeader));
	file.Write(data, header.count*header.paths);
	file.Close();
	return Load(filename);*/
	return false;
}
ushort OBP::GetCount()
{
	return header.count;
}