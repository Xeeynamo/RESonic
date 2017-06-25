#include "XeObjectAnimation.h"
#include "XeAnimation.h"
#include "XeScene.h"
#include "XeTexture.h"
#include "XeEffect.h"

XeObjectAnimation::XeObjectAnimation()
{
	wait = 0;
	frame = 0;
	animid = 0xFFFF;
	animindex = 0;

	animation = NULL;
	anim = NULL;
	frames = NULL;
	framelist = NULL;
	child = NULL;

	animqueue = 0xFFFF;
	lockedanimframe = false;
}
XeObjectAnimation::~XeObjectAnimation()
{
	SAFE_ADELETE(child);
}
bool XeObjectAnimation::IsCreated()
{
	return animation != 0;
}
void XeObjectAnimation::SetAnimation(XeAnimation *anim)
{
	if (this->animation == anim) return;
	SAFE_ADELETE(child);
	child = new XeObjectAnimation[0x10];
	this->animation = anim;
	framelist = anim->frame;
}
void XeObjectAnimation::SetAnimationIndex(ushort index)
{
	if (!animation) return;
	if (index == animid) return;
	animindex = animation->SetAnimation(index);
	if (animindex == 0xFFFF)
	{
		con.Log(DEBUG_LEVEL_WARNING, "Object(%04X).SetAnimationIndex(%04X) %s", animation->properties->id, index, "Animation not found");
		animover = true;
		animid = animindex;
		animindex = 0;
		CheckAnimQueue();
		return;
	}
	con.Log(DEBUG_LEVEL_INFO, "Object(%04X).SetAnimationIndex(%04X)", animation->properties->id, index);
	animqueue = 0xFFFF;
	anim = &animation->animation[animindex];
	frames = animation->animframe[animindex];
	
	animid = index;
	animover = false;
	wait = frame = 0;
	for(int i=0; i<anim->childcount; i++)
	{
		int childindex = animation->animchild[animindex][i].animation;
		if (childindex == index) continue;
		child[i].SetAnimation(this->animation);
		child[i].SetAnimationIndex(childindex);
	}
}
void XeObjectAnimation::SetAnimationIndexQueue(ushort index)
{
	animqueue = index;
}
void XeObjectAnimation::CheckAnimQueue()
{
	if (animqueue != 0xFFFF)
	{
		SetAnimationIndex(animqueue);
		animqueue = 0xFFFF;
	}
	return;
}
bool XeObjectAnimation::IsAnimationOver()
{
	return animover;
}

void XeObjectAnimation::LockAnimationFrame(ObjectAnimationFrame **animframe)
{
	if (lockedanimframe == true)
	{
		con.Log(DEBUG_LEVEL_WARNING, "XeObjectAnimation::LockAnimationFrame already unlocked");
		return;
	}
	lockedanimframe = true;
	lockanimframe = frames[frame];
	*animframe = &frames[frame];
}
void XeObjectAnimation::UnlockAnimationFrame()
{
	if (lockedanimframe == false)
	{
		con.Log(DEBUG_LEVEL_WARNING, "XeObjectAnimation::LockAnimationFrame not unlocked");
		return;
	}
	lockedanimframe = false;
	frames[frame] = lockanimframe;
}
void XeObjectAnimation::LockAnimationSpeed(int newspeed)
{
	lockanimspeed = anim->speed;
	anim->speed = newspeed;
}
void XeObjectAnimation::UnlockAnimationSpeed()
{
	anim->speed = lockanimspeed;
}
void XeObjectAnimation::Do()
{
	if (animover) return;
	wait++;
	if (wait >= anim->speed)
	{
		wait = 0;
		frame++;
		if (frame >= anim->length)
		{
			if (anim->loop == 0xFF)
			{
				animover = true;
				CheckAnimQueue();
				return;
			}
			frame = anim->loop;
		}
	}
	for(int i=0; i<anim->childcount; i++)
	{
		child[i].Do();
	}
}
void XeObjectAnimation::Draw(XeTexture *tex, short x, short y, bool mirror, bool flip, float priority)
{
	if (!animation) return;
	ObjectFrame *fr = &framelist[frames[frame].frame];

	for(int i=0; i<anim->childcount; i++)
	{
		ObjectAnimationChildren *children = &animation->animchild[animindex][i];
		if (children->zorder >= 0) continue;
		child[i].Draw(tex, x - children->centerx, y - children->centery, false, false, priority);
	}
	if (frames[frame].alpha != 0)
	{
		XeScene::SetPosition(x, y, priority);
		XeEffect::SetFadeFactor(1.0f/256.0f * float(frames[frame].alpha));
		XeScene::SetScale(float(frames[frame].width) / (mirror ? -32.0f : 32.0f), float(frames[frame].height) / (flip ? -32.0f : 32.0f));
		XeScene::SetRotation(float(frames[frame].rotation) * (360.0f/255.0f));
		XeScene::MovePosition(-fr->centerx, -fr->centery, 0.0f);
		tex->Draw(fr->sourcex, fr->sourcey, fr->width, fr->height, fr->sheet, NULL);
	}
	for(int i=0; i<anim->childcount; i++)
	{
		ObjectAnimationChildren *children = &animation->animchild[animindex][i];
		if (children->zorder < 0) continue;
		child[i].Draw(tex, x - children->centerx, y - children->centery, mirror, flip, priority);
	}
}
XeRect XeObjectAnimation::GetRect()
{
	XeRect r;
	r.left = frames->width - frames->centerx;
	r.right = r.left + frames->width;
	r.top = frames->height - frames->centery;
	r.bottom = r.top + frames->height;
	return r;
}