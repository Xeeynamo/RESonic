#include "0010_Ring.h"
#include "XeLevel.h"

Obj0010_Ring::Obj0010_Ring() : XeObject(0x0010)
{
	collision.left = collision.right = collision.top = collision.bottom = 8<<16;
	ingame = true;
	Animation.SetAnimationIndex(0x0000);
}
Obj0010_Ring::~Obj0010_Ring()
{
}
void Obj0010_Ring::Do()
{
	if (Animation.IsAnimationOver())
	{
		DeleteMeFromLevel();
		//level->DestroyObject(this);
	}
	Animation.Do();
}
void Obj0010_Ring::CollisionObject(XeObject *o)
{
	if (!ingame) return;
	if (o->holdPlayer)
	{
		o->holdPlayer->ring++;
		Animation.SetAnimationIndex(0xF000);
		ingame = false;
	}
}