#include "Editor.h"
#include "EditorRES.h"

#define E_FILEINFO_ANIMPAL_X (EDITOR_FILEINFO_X+256+24)
#define E_FILEINFO_ANIMPAL_Y (EDITOR_FILEINFO_Y)

char *EditorLUTFormat[] =
{
	"Unknow",
	"RGB332",
	"BGR233",
	"ARGB2222",
	"BGRA2222",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	// 16 bit per color
	"RGB565",
	"BGR565",
	"XRGB1555",
	"XBGR1555",
	"ARGB1555",
	"BGRA5551",
	"ARGB4444",
	"BGRA4444",
	// 24 bit per color
	"RGB888",
	"BGR888",
	"ARGB1887",
	"BGRA8871",
	"",
	"",
	"",
	"",
	// 32 bit per color
	"XRGB8888",
	"BGRX8888",
	"ARGB8888",
	"BGRA8888",
};

void XeEditor::init_Lut()
{
	_palDepthSelected = 1;
}
void XeEditor::draw_Lut()
{
	g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y, "File: %s", level->MakePath(level->currentAct, STAGEFILE_LUT));
	g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y+8, "Format: %s", EditorLUTFormat[levelLut.Format()]);
	g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y+16, "Palette count: %i", levelLut.PaletteCount());
	g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y+24, "Colors per palette: %i", levelLut.ColorsPerPalette());
	g->PrintText(EDITOR_FILEINFO_X, EDITOR_FILEINFO_Y+32, "Destination: %i", levelLut.DestinationIndex());
	g->PrintText(EDITOR_OBJECTINFO_X, EDITOR_OBJECTINFO_Y, "Current palette: %i/256 in %i/%i", _palselected+1, _palDepthSelected+1, CLUT_COUNT);
	g->effect.SetProperties(0);
	_scene->SetPosition(EDITOR_OBJECT_X, EDITOR_OBJECT_Y);
	_scene->SetScale(EDITOR_PALETTE_SIZEF, EDITOR_PALETTE_SIZEF);
	for(int i=0; i<16; i++)
	{
		g->levelLUT.Draw(i*EDITOR_PALETTE_SIZE, _palselected, EDITOR_PALETTE_SIZE, 1, _palDepthSelected, NULL);
		_scene->MovePosition(0, 1);
	}
	g->effect.SetProperties(1);

	g->PrintText(E_FILEINFO_ANIMPAL_X, E_FILEINFO_ANIMPAL_Y, "File: %s", name_levelLut);
}
void XeEditor::input_Lut(WPARAM key, bool keyup)
{
	//
}
void XeEditor::char_Lut(WPARAM character)
{
	switch(toupper(character))
	{
	case 'O':
		if (_palDepthSelected > 0) _palDepthSelected--;
		break;
	case 'P':
		if (_palDepthSelected < CLUT_COUNT) _palDepthSelected++;
		break;
	case 'K':
		if (_palselected > 0) _palselected--;
		break;
	case 'L':
		if (_palselected < PALETTE_COUNT) _palselected++;
		break;
	}
}
void XeEditor::mouse_Lut(short x, short y, WPARAM button)
{
	if (button == MK_LBUTTON)
	{
		if (mousex >= EDITOR_OBJECT_X && mousex < EDITOR_OBJECT_X+256
			&& mousey >= EDITOR_OBJECT_Y-1 && mousey < EDITOR_OBJECT_Y+256)
		{
			CHOOSECOLOR chooseColor;
			COLORREF pal[16];
			int mx = (mousex - EDITOR_OBJECT_X)/16;
			int my = (mousey - EDITOR_OBJECT_Y)/16;

			ZeroMemory(&chooseColor, sizeof(CHOOSECOLOR));
			chooseColor.lStructSize = sizeof(chooseColor);
			chooseColor.hwndOwner = (HWND)hWnd;
			chooseColor.rgbResult = SWAP24(g->level.palette[1][_palselected][mx|(my<<4)]) & 0xFFFFFF;
			chooseColor.lpCustColors = pal;
			chooseColor.Flags = CC_ANYCOLOR | CC_RGBINIT;
			memcpy(pal, &g->level.palette[_palselected][my<<4], sizeof(pal));
			for(int i=0; i<16; i++)
			{
				pal[i] = SWAP24(pal[i]) & 0xFFFFFF;
			}

			if (ChooseColor(&chooseColor))
			{
				g->level.palette[1][_palselected][mx|(my<<4)] = (g->level.palette[1][_palselected][mx|(my<<4)] & 0xFF000000) | SWAP24(chooseColor.rgbResult);
			}
		}
	}
}