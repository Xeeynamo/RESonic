#pragma once
#include "XeBase.h"
#include "XeMemory.h"

struct ObjectHeader
{
	uint head;
	ushort frameCount;
	ushort animCount;
	byte hitboxCount;
	byte padding1;			// Become TYPE
	byte padding2;			
	byte padding3;
	// Become NAME
	// Become ID
	// Become VALUE
};
struct ObjectProperties
{
	char name[0x10];
	ushort id;
	short value;
	uint exp;
};
struct ObjectPropertiesEx
{
	ushort maxhp;
	ushort maxmp;
	byte atk, def, mag, spr;
	byte mir, dex, spd, lck;
	uint exp;
};
struct ObjectFrame
{
	byte sheet;
	byte collision;
	byte sourcex;
	byte sourcey;
	byte width;
	byte height;
	sbyte centerx;
	sbyte centery;
};
struct ObjectHitbox
{
	sbyte sourcex;
	sbyte sourcey;
	byte width;
	byte height;
	int padding;
};
struct ObjectAnimation
{
	ushort index;
	byte length;
	byte speed;
	byte loop;
	byte alternative;
	byte childcount;
	byte hitbox;
};
struct ObjectAnimationFrame
{
	ushort frame;
	sbyte centerx;
	sbyte centery;
	sbyte width;
	sbyte height;
	byte rotation;
	byte alpha;
	//sbyte posx childrens
	//sbyte posy childrens
	//byte rotation childrens
	//byte alpha childrens
};
struct ObjectAnimationChildren
{
	ushort animation;
	sbyte centerx;
	sbyte centery;
	sbyte width;
	sbyte height;
	byte rotation;
	sbyte zorder;
};

class XeAnimation
{
private:
public:
	ushort animationInternalIndex;
	ushort animationIndex;
	bool animationOver;

	XeEngine::Memory data;
	ObjectHeader *header;
	ObjectProperties *properties;
	ObjectFrame *frame;						// Lista dei frame dell'animazione
	ObjectHitbox *hitbox;
	ObjectAnimation *animation;
	ObjectAnimationFrame **animframe;
	ObjectAnimationChildren **animchild;
public:
	XeAnimation();
	~XeAnimation();

	bool LoadAnimation(char *filename);
	bool LoadAnimation(XeEngine::Memory *mem);
	void DestroyAnimation();
	char *GetObjectName();
	ushort GetAnimation();
	ushort SetAnimation(ushort animationIndex);
	bool IsAnimationOver();

};