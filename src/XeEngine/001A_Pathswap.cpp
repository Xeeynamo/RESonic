#include "001A_Pathswap.h"

Obj001A_Pathswap::Obj001A_Pathswap() : XeObject(0x001A)
{
	collision.left = collision.right = collision.top = collision.bottom = 8<<16;
	Animation.SetAnimationIndex(0x0000);
}
Obj001A_Pathswap::~Obj001A_Pathswap()
{
}
void Obj001A_Pathswap::Do()
{
	Animation.Do();
}
void Obj001A_Pathswap::CollisionObject(XeObject *o)
{
	if (o->holdPlayer)
	{
		o->path ^= 1;
	}
}