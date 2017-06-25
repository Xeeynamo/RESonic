#include "Preview.h"
#include "Game.h"
#include "XeEffect.h"
#include "XeObject.h"
#include "XeLevel.h"

#define E_PREVIEW_OBJINFOX		8
#define E_PREVIEW_OBJINFOY		16
#define E_PREVIEW_HUDX			8
#define E_PREVIEW_HUDY			16

Editor::Preview::Preview(MainEditor *e) : Control(e)
{
#ifdef DEBUG
	m_name = "Game (Debug build)";
#else
	m_name = "Game";
#endif
	k.k = 0;
	debug = false;
}
Editor::Preview::~Preview()
{

}

void Editor::Preview::_Draw()
{
	Game *g = getGame();
	XeEffect::SetProperties(1);
	XeObject *e = (XeObject*)getLevel()->mainobject;
	if (e)
	{
		if (debug)
		{
			PrintText(E_PREVIEW_OBJINFOX, E_PREVIEW_OBJINFOY+0, "Object pos %04i %04X", HIWORD(e->x), HIWORD(e->y));
			PrintText(E_PREVIEW_OBJINFOX, E_PREVIEW_OBJINFOY+8, "Camera pos %04X %04X", HIWORD(g->level.cameraX), HIWORD(g->level.cameraY));
			PrintText(E_PREVIEW_OBJINFOX, E_PREVIEW_OBJINFOY+16, "Speed IXY(%04X, %04X, %04X) Air %i", u16(e->inertia>>8), u16(e->speedx>>8), u16(e->speedy>>8), e->Status.air);
			PrintText(E_PREVIEW_OBJINFOX, E_PREVIEW_OBJINFOY+24, "Angle %02X Lock %02X  Dash %04X", u8(e->angle), e->slope_movelock, e->spindash_speed);
			PrintText(E_PREVIEW_OBJINFOX, E_PREVIEW_OBJINFOY+32, "Anim mod %i speed %04X", e->animspeed_mod, e->animspeed);
		}
		else
		{
			XeObject *o = getLevel()->GetAttachedObject();
			if (o && o->holdPlayer)
			{
				PrintText(E_PREVIEW_HUDX, E_PREVIEW_HUDY+0,  "Score %8i", o->holdPlayer->score);
				PrintText(E_PREVIEW_HUDX, E_PREVIEW_HUDY+8, "Time  %02i:%02i:%02i", getLevel()->timelevel/3600, (getLevel()->timelevel/60)%60, (int)((float)getLevel()->timelevel*1.66f)%100);
				PrintText(E_PREVIEW_HUDX, E_PREVIEW_HUDY+16, "Ring  %3i", o->holdPlayer->ring);
				PrintText(E_PREVIEW_HUDX, E_PREVIEW_HUDY+24, "Lifes %3i", o->holdPlayer->lifes);
			}
		}
	}
}
bool Editor::Preview::_InputKeyb(int key)
{
	switch(key)
	{
	case 'P':
		debug ^= 1;
		return false;
	case 'O':
		getGame()->level.mainobject->Status.died = 1;
		return false;

	case VK_F6:
		getGame()->SetResolution(240, 192);
		return false;
	case VK_F7:
		getGame()->SetResolution(256, 224);
		return false;
	case VK_F8:
		getGame()->SetResolution(320, 224);
		return false;
	case VK_F9:
		getGame()->SetResolution(400, 256);
		return false;
	}
	return false;
}
bool Editor::Preview::_InputKeyb(int key, bool up)
{
	switch(key)
	{
		case VK_UP:
			k.up = !up;
			return true;
		case VK_DOWN:
			k.down = !up;
			return true;
		case VK_LEFT:
			k.left = !up;
			return true;
		case VK_RIGHT:
			k.right = !up;
			return true;

		case 'A':
			k.triangle = !up;
			return true;
		case 'S':
			k.circle = !up;
			return true;
		case 'D':
			k.cross = !up;
			return true;

		case VK_RETURN:
			k.start = !up;
			return true;
	}
	return false;
}