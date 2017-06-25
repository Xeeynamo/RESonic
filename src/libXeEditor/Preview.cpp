#include "Preview.h"

#define E_PREVIEW_OBJINFOX		8
#define E_PREVIEW_OBJINFOY		16
#define E_PREVIEW_HUDX			8
#define E_PREVIEW_HUDY			16

namespace Editor
{
#define DEBUGM_VARX			20
#define DEBUGM_MAINMENU		0
#define DEBUGM_SYSTEM		1
#define DEBUGM_LEVEL		2
#define DEBUGM_PLAYER		3
#define DEBUGM_ENTITIES		4
#define DEBUGM_LAYERS		5
#define DEBUGM_LAYERSTAT	6
#define DEBUGM_LAYERSTAT1	6
#define DEBUGM_LAYERSTAT2	7
#define DEBUGM_LAYERSTAT3	8
#define DEBUGM_LAYERSTAT4	9
#define DEBUGM_LEVELSHAKE	10


	struct MenuEntry
	{
		char* name;
		int submenu;
	};

	const int debug_menusize[] =
	{
		5,		// DEBUGM_MAINMENU
		1,		// DEBUGM_SYSTEM
		9,		// DEBUGM_LEVEL
		1,		// DEBUGM_PLAYER
		1,		// DEBUGM_ENTITIES
		5,		// DEBUGM_LAYERS
		6,		// DEBUGM_LAYERSTAT1
		6,		// DEBUGM_LAYERSTAT2
		6,		// DEBUGM_LAYERSTAT3
		6,		// DEBUGM_LAYERSTAT4
		6,		// DEBUGM_LEVELSHAKE
	};
	const MenuEntry debug_mainmenu[] =
	{
		"Debug menu",		DEBUGM_MAINMENU,
		"System",			DEBUGM_SYSTEM,
		"Level",			DEBUGM_LEVEL,
		"Player",			DEBUGM_PLAYER,
		"Entities",			DEBUGM_ENTITIES,
	};
	const MenuEntry debug_menusystem[] =
	{
		"System menu",		0,
	};
	const MenuEntry debug_menulevel[] =
	{
		"Level menu",		0,
		"Layers",			DEBUGM_LAYERS,
		"Shake",			DEBUGM_LEVELSHAKE,
		"Level set",		0,
		"Zone",				0,
		"Room",				0,
		"Act",				0,
		"Zone name",		0,
		"Camera",			0,
		"Timer",			0,
	};
	const MenuEntry debug_menuplayer[] =
	{
		"Player menu",		0,
	};
	const MenuEntry debug_menuentities[] =
	{
		"Entities menu",	0,
	};
	const MenuEntry debug_menulayers[] =
	{
		"Layers menu",	0,
		"Foreground (main)",		DEBUGM_LAYERSTAT + 0,
		"Background (main)",		DEBUGM_LAYERSTAT + 1,
		"Foreground (secondary)",	DEBUGM_LAYERSTAT + 2,
		"Background (secondary)",	DEBUGM_LAYERSTAT + 3,
	};
	const MenuEntry debug_menulayerstat[] =
	{
		"Layers menu",	0,
		"Width",		0,
		"Height",		0,
		"ParallaxID",	0,
		"null",			0,
		"Visible",		0,
	};
	const MenuEntry debug_menulevelshake[] =
	{
		"Level shake menu",	0,
		"Shake X",			0,
		"Shake Y",			0,
		"Test shake X",		0,
		"Test shake Y",		0,
		"Reset shake",		0,
	};
	const MenuEntry* debug_menu[] =
	{
		debug_mainmenu,
		debug_menusystem,
		debug_menulevel,
		debug_menuplayer,
		debug_menuentities,
		debug_menulayers,
		debug_menulayerstat,
		debug_menulayerstat,
		debug_menulayerstat,
		debug_menulayerstat,
		debug_menulevelshake,
	};
}


Editor::Preview::Preview(MainEditor *e) : Control(e)
{
#ifdef DEBUG
	m_name = "Game (Debug mode)";
#else
	m_name = "Game";
#endif
	debug = false;
	m_menustack = 0;
	m_cursor[m_menustack] = 0;
	m_menu[m_menustack] = 0;
}
Editor::Preview::~Preview()
{

}

void Editor::Preview::_Draw()
{
	if (debug == true)
	{
		int draw_cursor = 0;
		PrintTextAligned(2, 2, debug_menu[m_menu[m_menustack]][0].name);
		PrintTextAligned(1, 4 + m_cursor[m_menustack], ">");
		for(int i = 1; i < debug_menusize[m_menu[m_menustack]]; i++)
		{
			PrintTextAligned(2, 3 + i, debug_menu[m_menu[m_menustack]][i].name);
		}

		switch(m_menu[m_menustack])
		{
		case DEBUGM_LEVEL:
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "");
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "");
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "%i", getLevel()->m_levelset);
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "%i", getLevel()->m_zone);
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "%i", getLevel()->m_room);
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "%i", getLevel()->m_act);
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "%s", "N/A");
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "%04X %04X", getLevel()->cameraX, getLevel()->cameraY);
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "%i", getLevel()->m_timer);
			break;
		case DEBUGM_LAYERSTAT1:
		case DEBUGM_LAYERSTAT2:
		case DEBUGM_LAYERSTAT3:
		case DEBUGM_LAYERSTAT4:
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "%i", getLevel()->layerProperties[m_menu[m_menustack] - DEBUGM_LAYERSTAT].width);
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "%i", getLevel()->layerProperties[m_menu[m_menustack] - DEBUGM_LAYERSTAT].height);
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "%i", getLevel()->layerProperties[m_menu[m_menustack] - DEBUGM_LAYERSTAT].parallaxID);
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "");
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "%i", getLevel()->layerVisible[m_menu[m_menustack] - DEBUGM_LAYERSTAT]);
			break;
		case DEBUGM_LEVELSHAKE:
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "%i", getLevel()->screenShakeX);
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "%i", getLevel()->screenShakeY);
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "");
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "");
			PrintTextAligned(DEBUGM_VARX, 4 + draw_cursor++, "");
		}
	}
	/*XeEngine::Game* g = getGame();
	XeEngine::Entity* e = getLevel()->GetPrimaryEntity();
	if (e)
	{
		if (debug)
		{
			PrintText(E_PREVIEW_OBJINFOX, E_PREVIEW_OBJINFOY+0, "Object pos %04i %04X", HIPART(e->x), HIPART(e->y));
			PrintText(E_PREVIEW_OBJINFOX, E_PREVIEW_OBJINFOY+8, "Camera pos %04X %04X", HIPART(g->level.cameraX), HIPART(g->level.cameraY));
			PrintText(E_PREVIEW_OBJINFOX, E_PREVIEW_OBJINFOY+16, "Speed IXY(%04X, %04X, %04X) Air %i", u16(e->inertia>>8), u16(e->speedx>>8), u16(e->speedy>>8), e->Status.air);
			PrintText(E_PREVIEW_OBJINFOX, E_PREVIEW_OBJINFOY+24, "Angle %02X Lock %02X  Dash %04X", u8(e->angle), e->slope_movelock, e->spindash_speed);
			PrintText(E_PREVIEW_OBJINFOX, E_PREVIEW_OBJINFOY+32, "Anim mod %i speed %04X", e->animspeed_mod, e->animspeed);
		}
		else
		{
			XeEngine::Entity* o = getLevel()->GetPrimaryEntity();
			if (o && o->holdPlayer)
			{
				PrintText(E_PREVIEW_HUDX, E_PREVIEW_HUDY+0,  "Score %8i", o->holdPlayer->score);
				PrintText(E_PREVIEW_HUDX, E_PREVIEW_HUDY+8, "Time  %02i:%02i:%02i", getLevel()->GetTimer()/3600, (getLevel()->GetTimer()/60)%60, (int)((float)getLevel()->GetTimer()*1.66f)%100);
				PrintText(E_PREVIEW_HUDX, E_PREVIEW_HUDY+16, "Ring  %3i", o->holdPlayer->ring);
				PrintText(E_PREVIEW_HUDX, E_PREVIEW_HUDY+24, "Lifes %3i", o->holdPlayer->lifes);
			}
		}
	}*/
}
bool Editor::Preview::_InputKeyb(int key)
{
	if (isCtrlPressed())
	{
		switch(key)
		{
		case 'D':
			debug ^= 1;
			break;
		case VK_UP:
			if (--m_cursor[m_menustack] < 0)
			{
				m_cursor[m_menustack] = debug_menusize[m_menu[m_menustack]] - 2;
			}
			break;
		case VK_DOWN:
			if (++m_cursor[m_menustack] >= debug_menusize[m_menu[m_menustack]] - 1)
			{
				m_cursor[m_menustack] = 0;
			}
			break;
		case VK_RETURN:
			m_menu[m_menustack + 1] = debug_menu[m_menu[m_menustack]][m_cursor[m_menustack] + 1].submenu;
			if (m_menu[m_menustack + 1] != 0)
			{
				m_cursor[++m_menustack] = 0;
			}
			else
			{
				switch(m_menu[m_menustack])
				{
				case DEBUGM_LAYERSTAT1:
				case DEBUGM_LAYERSTAT2:
				case DEBUGM_LAYERSTAT3:
				case DEBUGM_LAYERSTAT4:
					getLevel()->layerVisible[m_menu[m_menustack] - DEBUGM_LAYERSTAT] ^= 1;
					break;
				case DEBUGM_LEVELSHAKE:
					switch(m_cursor[m_menustack])
					{
					case 2:
						getLevel()->screenShakeX = 16;
						break;
					case 3:
						getLevel()->screenShakeY = 16;
						break;
					case 4:
						getLevel()->screenShakeX = 0;
						getLevel()->screenShakeY = 0;
						break;
					}
					break;
				}
			}
			break;
		case VK_BACK:
			if (m_menustack > 0)
			{
				m_menustack--;
			}
			else
			{
				debug ^= 1;
			}
			break;
		}
	}
	switch(key)
	{
	case 'O':
		//getLevel()->GetPrimaryEntity()->Status.died = 1;
		return false;
	}
	return false;
}
bool Editor::Preview::_InputKeyb(int key, bool up)
{
	if (isCtrlPressed())
	{
		switch(key)
		{
		case VK_UP:
			return true;
		case VK_DOWN:
			return true;
		case VK_LEFT:
			return true;
		case VK_RIGHT:
			return true;
		}
	}
	return false;
}