#include "ObjectList.h"
#include "XeObject.h"

XeObject *CreateObject(u16 id)
{
	switch(id)
	{
	case 0x0001: return new Obj0001_Sonic;
	case 0x000F: return new Obj0001_Sonic;
	case 0x0010: return new Obj0010_Ring;
	case 0x001A: return new Obj001A_Pathswap;
	default: return new XeObject(id);
	}
}