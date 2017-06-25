#include "Editor.h"
#include "EditorRES.h"

#define EDITOR_COLLISION_ZOOM	8
#define EDITOR_OBJECTEDITOR_X	(EDITOR_OBJECT_X+256+24)
#define EDITOR_OBJECTEDITOR_Y	(EDITOR_OBJECT_Y+16)

void XeEditor::init_Collision()
{
	_colverse = 0;
	_colpreview = 0;
	_blockselected = 0;
}
void XeEditor::draw_Collision()
{
	XeScene::SetPosition(EDITOR_OBJECT_X, EDITOR_OBJECT_Y);
	g->effect.SetClutDepth(0, CLUT_COUNT);
	g->effect.SetClutIndex(0);
	g->effect.SetProperties(1);
	texCollision.Draw(0);
	g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y, "File: %s ", level->MakePath(level->currentAct, STAGEFILE_HBX));
	g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y+16, "Collision verse: %s", _colverse ? "Wall" : "Floor");
	g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y+24, "Collision ID %02X ", _colpreview);

	g->PrintText(EDITOR_OBJECTEDITOR_X, EDITOR_OBJECTEDITOR_Y-8, "0123465789ABCDEF");
	g->PrintText(EDITOR_OBJECTEDITOR_X-16, EDITOR_OBJECTEDITOR_Y, "0\n1\n2\n3\n4\n6\n5\n7\n8\n9\nA\nB\nC\nD\nE\nF");
	g->PrintText(EDITOR_OBJECTEDITOR_X+16*EDITOR_COLLISION_ZOOM+8, EDITOR_OBJECTEDITOR_Y, "0\n1\n2\n3\n4\n6\n5\n7\n8\n9\nA\nB\nC\nD\nE\nF");
	g->PrintText(EDITOR_OBJECTEDITOR_X, EDITOR_OBJECTEDITOR_Y+16*EDITOR_COLLISION_ZOOM+8, "0123465789ABCDEF");

	_scene->SetPosition(EDITOR_OBJECTEDITOR_X, EDITOR_OBJECTEDITOR_Y);
	_scene->SetScale(EDITOR_COLLISION_ZOOM, EDITOR_COLLISION_ZOOM);
	texCollision.Draw((_colpreview&0xF)<<4, _colpreview&~0xF, 16, 16, 0, NULL);
}
void XeEditor::input_Collision(WPARAM key, bool keyup)
{
	if (keyup == true) return;
	switch(key)
	{
	case VK_F4:
		if (keyup)
		{
			XeEngine::MemoryCopy(levelHitbox.hitbox, g->level.collision, sizeof(g->level.collision));
			levelHitbox.Save(name_levelHitbox);
		}
		break;
	case VK_DELETE:
		XeEngine::MemoryFill(g->level.collision[_colpreview], 0x10);
		break;
	case 'V':
		_colverse ^= 1;
		break;
	}
}
void XeEditor::char_Collision(WPARAM character)
{
}
void XeEditor::mouse_Collision(short x, short y, WPARAM button)
{
	_colpreview = _colselected;
	if (mousex >= EDITOR_OBJECTEDITOR_X && mousex < EDITOR_OBJECTEDITOR_X+(16*EDITOR_COLLISION_ZOOM)
		&& mousey >= EDITOR_OBJECTEDITOR_Y-1 && mousey < EDITOR_OBJECTEDITOR_Y+(17*EDITOR_COLLISION_ZOOM))
	{
		int mx = mousex - EDITOR_OBJECTEDITOR_X;
		int my = mousey - EDITOR_OBJECTEDITOR_Y;
		mx /= EDITOR_COLLISION_ZOOM;
		my /= EDITOR_COLLISION_ZOOM;

		if (button != 0 && my == 0x10)
		{
			g->level.collision[_colpreview][mx] = 0;
		}
		else if (button == MK_LBUTTON)
			g->level.collision[_colpreview][mx] = (~(my))+0x11;
		else if (button == MK_RBUTTON)
			g->level.collision[_colpreview][mx] = ~(my);
	}
	else
	{
		if (mousex >= EDITOR_OBJECT_X && mousex <= EDITOR_OBJECT_X + 256 &&
			mousey >= EDITOR_OBJECT_Y && mousey <= EDITOR_OBJECT_Y + 256)
		{
			int mx = mousex - EDITOR_OBJECT_X;
			int my = mousey - EDITOR_OBJECT_Y;
			_colpreview = (mx>>4) | (my&~0xF);
			if (button == MK_LBUTTON)
			{
				_colselected = _colpreview;
			}
		}

	}
}