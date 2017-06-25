#include "HBX.h"
#include "XeEngineLV1.h"

HBX::HBX()
{

}
HBX::~HBX()
{

}

bool HBX::Load(char *filename)
{
	XeEngine::File f;
	if (!f.Open(XeEngine::String(filename), true))
		return false;
	f.Read(hitbox, sizeof(hitbox));
	f.Read(angle, sizeof(angle));
	f.Close();
	return true;
}
bool HBX::Save(char *filename)
{
	XeEngine::File f;
	if (!f.Create(XeEngine::String(filename)))
		return false;
	f.Write(hitbox, sizeof(hitbox));
	f.Write(angle, sizeof(angle));
	f.Close();
	return true;
}