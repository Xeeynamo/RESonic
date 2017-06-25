#include "Editor.h"

#define EDITOR_PREVIEW_OBJINFO_X	8
#define EDITOR_PREVIEW_OBJINFO_Y	16

void XeEditor::init_Preview()
{
	k.k = 0;
	hudDebug = false;
}
void XeEditor::draw_Preview()
{
	XeEffect::SetProperties(1);
	XeObject *e = (XeObject*)g->level.mainobject;
	if (e)
	{
		if (hudDebug)
		{
			g->PrintText(EDITOR_PREVIEW_OBJINFO_X, EDITOR_PREVIEW_OBJINFO_Y+0, "Object pos %04X %04X", HIWORD(e->x), HIWORD(e->y));
			g->PrintText(EDITOR_PREVIEW_OBJINFO_X, EDITOR_PREVIEW_OBJINFO_Y+8, "Camera pos %04X %04X", HIWORD(g->level.cameraX), HIWORD(g->level.cameraY));
			g->PrintText(EDITOR_PREVIEW_OBJINFO_X, EDITOR_PREVIEW_OBJINFO_Y+16, "Speed IXY(%04X, %04X, %04X) Air %i", u16(e->inertia>>8), u16(e->speedx>>8), u16(e->speedy>>8), e->Status.air);
			g->PrintText(EDITOR_PREVIEW_OBJINFO_X, EDITOR_PREVIEW_OBJINFO_Y+24, "Angle %02X Lock %02X  Dash %04X", u8(e->angle), e->slope_movelock, e->spindash_speed);
			g->PrintText(EDITOR_PREVIEW_OBJINFO_X, EDITOR_PREVIEW_OBJINFO_Y+32, "Anim mod %i speed %04X", e->animspeed_mod, e->animspeed);
		}
		else
		{
			XeObject *o = level->GetAttachedObject();
			if (o && o->holdPlayer)
			{
				g->PrintText(EDITOR_PREVIEW_OBJINFO_X, EDITOR_PREVIEW_OBJINFO_Y+0,  "Score %8i", o->holdPlayer->score);
				g->PrintText(EDITOR_PREVIEW_OBJINFO_X, EDITOR_PREVIEW_OBJINFO_Y+8, "Time  %02i:%02i:%02i", level->timelevel/3600, (level->timelevel/60)%60, (int)((float)level->timelevel*1.66f)%100);
				g->PrintText(EDITOR_PREVIEW_OBJINFO_X, EDITOR_PREVIEW_OBJINFO_Y+16, "Ring  %3i", o->holdPlayer->ring);
				g->PrintText(EDITOR_PREVIEW_OBJINFO_X, EDITOR_PREVIEW_OBJINFO_Y+24, "Lifes %3i", o->holdPlayer->lifes);
			}
		}
	}
}
void XeEditor::input_Preview(WPARAM key, bool keyup)
{
	switch(key)
	{
	case VK_UP:
		k.up = !keyup;
		break;
	case VK_DOWN:
		k.down = !keyup;
		break;
	case VK_LEFT:
		k.left = !keyup;
		break;
	case VK_RIGHT:
		k.right = !keyup;
		break;

	case 'A':
		k.triangle = !keyup;
		break;
	case 'S':
		k.circle = !keyup;
		break;
	case 'D':
		k.cross = !keyup;
		break;

	case VK_RETURN:
		k.start = !keyup;
		break;

	// Debug keys
	case 'P':
		if (!keyup)
			hudDebug ^= 1;
		break;
	case 'O':
		g->level.mainobject->Status.died = 1;
		break;

	case VK_F6:
		g->SetResolution(256, 192);
		break;
	case VK_F7:
		g->SetResolution(256, 224);
		break;
	case VK_F8:
		g->SetResolution(320, 224);
		break;
	case VK_F9:
		g->SetResolution(400, 256);
		break;
	}
	g->Input(k);
}
void XeEditor::char_Preview(WPARAM character)
{

}
void XeEditor::mouse_Preview(short x, short y, WPARAM button)
{

}