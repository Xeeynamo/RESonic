#include "XeAnimation.h"
#include "XeFile.h"
#include "XeScene.h"

XeAnimation::XeAnimation()
{
	animframe = NULL;
	animchild = NULL;
	animationOver = true;
	animationIndex = 0xFFFF;
}
XeAnimation::~XeAnimation()
{
	DestroyAnimation();
}

bool XeAnimation::LoadAnimation(char *filename)
{
	XeEngine::File f;
	if (!f.Open(XeEngine::String(filename)))
		return false;
	DestroyAnimation();
	data.Alloc(f.Size());
	f.Read(data.GetMemoryHandle(), data.Size());
	f.Close();
	return LoadAnimation(&data);
}
bool XeAnimation::LoadAnimation(XeEngine::Memory *mem)
{
	if (!mem) return false;
	header = (ObjectHeader*)(mem->GetMemoryHandle());
	properties = (ObjectProperties*)(header+1);
	frame = (ObjectFrame*)(properties+1);
	hitbox = (ObjectHitbox*)(frame+header->frameCount);
	animation = (ObjectAnimation*)(hitbox+header->hitboxCount);
	animframe = new ObjectAnimationFrame*[header->animCount];
	animchild = new ObjectAnimationChildren*[header->animCount];

	ObjectAnimationFrame *memAnimFrame = (ObjectAnimationFrame*)(animation+header->animCount);
	for(int i=0; i<header->animCount; i++)
	{
		animframe[i] = memAnimFrame;
		memAnimFrame += animation[i].length;
	}
	ObjectAnimationChildren *memAnimChild = (ObjectAnimationChildren*)(memAnimFrame);
	for(int i=0, j=0; i<header->animCount; i++)
	{
		animchild[i] = memAnimChild;
		if (animation[i].childcount == 0)
			animchild[i] = NULL;
		memAnimChild += animation[i].childcount;
	}
	return true;
}
void XeAnimation::DestroyAnimation()
{
	data.Free();
	SAFE_ADELETE(animframe);
	SAFE_ADELETE(animchild);
}
char *XeAnimation::GetObjectName()
{
	return properties->name;
}
ushort XeAnimation::SetAnimation(ushort animationIndex)
{
	for(ushort i = 0; i<header->animCount; i++)
	{
		if (animation[i].index == animationIndex)
		{
			this->animationIndex = animationIndex;
			animationInternalIndex = i;
			animationOver = false;
			return i;
		}
	}
	animationOver = true;
	this->animationIndex = 0xFFFF;
	return 0xFFFF;
}