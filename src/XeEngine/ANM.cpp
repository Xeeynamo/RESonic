#include "ANM.h"

ANM::ANM()
{
	header = NULL;
	anim = NULL;
	vdata = NULL;
}
ANM::~ANM()
{

}

bool ANM::Load(char *filename)
{
	XeEngine::File f;
	if (!f.Open(XeEngine::String(filename), true))
		return false;
	data.Alloc(f.Size());
	f.Read(data.GetMemoryHandle(), data.Size());
	f.Close();
	header = (ANMHeader*)data.GetMemoryHandle();
	anim = (ANMAnimation*)(header+1);
	vdata = (void*)(anim+1);
	return true;
}
