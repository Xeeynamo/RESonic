#include "BLK.h"

BLK::BLK()
{
	data = 0;
	*(int*)&header = 0;
}
BLK::~BLK()
{

}

bool BLK::Load(char *filename)
{
	file.Close();
	if (!file.Open(XeEngine::String(filename), true))
		return false;
	file.Read(&header, sizeof(BLKHeader));
	return true;
}
bool BLK::Save(char *filename)
{
	if (!data) return false;
	file.Close();
	if (!file.Create(XeEngine::String(filename)))
		return false;
	file.Write(&header, sizeof(BLKHeader));
	file.Write(data, header.count*64*4);
	file.Close();
	return Load(filename);
}

short BLK::Count()
{
	return header.count;
}
void BLK::Count(short count)
{
	header.count = count;
}
short BLK::Destination()
{
	return header.destination;
}
void BLK::Destination(short destination)
{
	header.destination = destination;
}
void BLK::SetData(void *data)
{
	this->data = data;
	file.Read(data, header.count*64*4);
}