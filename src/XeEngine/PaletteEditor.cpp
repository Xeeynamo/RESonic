#include "PaletteEditor.h"
#include "PaletteSelector.h"
#include "Slidebar.h"

const char *paletteeditor_formats[] =
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

#define E_PALETTEINFO_X	E_FILEINFO_X
#define E_PALETTEINFO_Y	(E_FILEINFO_Y+48)
#define E_FILEINFO_ANIMPAL_X (E_FILEINFO_X+256+24)
#define E_FILEINFO_ANIMPAL_Y (E_FILEINFO_Y)
#define E_PALETTE_SIZE	16
#define E_PALETTE_SIZEF	(float)(E_PALETTE_SIZE)
#define E_PALETTE_COLORCHANGER_X (E_PALETTEINFO_X + 16*E_PALETTE_SIZE + 16)
#define E_PALETTE_COLORCHANGER_Y(i) (E_PALETTEINFO_Y + 16 + i*16)
#define E_PALETTE_COLORCHANGER_W	72

void eChangeColor(Editor::Slidebar *o, Editor::Control *parent, int value)
{
	((Editor::PaletteEditor*)parent)->WriteColor(o);
}

Editor::PaletteEditor::PaletteEditor(MainEditor *e) : Control(e)
{
	m_name = "Palette editor";
	
	palSelector = new PaletteSelector(e, this, E_PALETTEINFO_X+1, E_PALETTEINFO_Y + 16, 256);
	slideR = new Slidebar(e, this, E_PALETTE_COLORCHANGER_X + 16, E_PALETTE_COLORCHANGER_Y(0), E_PALETTE_COLORCHANGER_W);
	slideR->setMax(256);
	slideR->eChangeValue = eChangeColor;
	slideG = new Slidebar(e, this, E_PALETTE_COLORCHANGER_X + 16, E_PALETTE_COLORCHANGER_Y(1), E_PALETTE_COLORCHANGER_W);
	slideG->setMax(256);
	slideG->eChangeValue = eChangeColor;
	slideB = new Slidebar(e, this, E_PALETTE_COLORCHANGER_X + 16, E_PALETTE_COLORCHANGER_Y(2), E_PALETTE_COLORCHANGER_W);
	slideB->setMax(256);
	slideB->eChangeValue = eChangeColor;
	slideA = new Slidebar(e, this, E_PALETTE_COLORCHANGER_X + 16, E_PALETTE_COLORCHANGER_Y(3), E_PALETTE_COLORCHANGER_W);
	slideA->setMax(256);
	slideA->eChangeValue = eChangeColor;

	controlList.Add(palSelector);
	controlList.Add(slideR);
	controlList.Add(slideG);
	controlList.Add(slideB);
	controlList.Add(slideA);
}
Editor::PaletteEditor::~PaletteEditor()
{

}

Color Editor::PaletteEditor::getColor()
{
	return palSelector->getColor();
}
void Editor::PaletteEditor::setColor(Color color)
{
	return palSelector->setColor(color);
}

void Editor::PaletteEditor::WriteColor(Slidebar *s)
{
	Color color = getColor();
	Color value = MIN(s->getValue(), 0xFF);
	if (s == slideR)
	{
		color = (color & 0xFF00FFFF) | (value << 16);
	}
	else if (s == slideG)
	{
		color = (color & 0xFFFF00FF) | (value << 8);
	}
	else if (s == slideB)
	{
		color = (color & 0xFFFFFF00) | (value << 0);
	}
	else if (s == slideA)
	{
		color = (color & 0x00FFFFFF) | (value << 24);
	}
	setColor(color);
}

void Editor::PaletteEditor::_Draw()
{
	Color c = getColor();
	byte r = (c >> 16) & 0xFF;
	byte g = (c >> 8) & 0xFF;
	byte b = (c >> 0) & 0xFF;
	byte a = (c >> 24) & 0xFF;
	if (prev != c)
	{
		prev = c;
		slideR->setValue(r);
		slideG->setValue(g);
		slideB->setValue(b);
		slideA->setValue(a);
	}


	PrintText(E_FILEINFO_X, E_FILEINFO_Y, "File: %s", getLevel()->MakePath(getLevel()->currentAct, STAGEFILE_LUT));
	/*PrintText(E_FILEINFO_X, E_FILEINFO_Y+8, "Format: %s", paletteeditor_formats[getGame()->levelLUT.Format()]);
	PrintText(E_FILEINFO_X, E_FILEINFO_Y+16, "Palette count: %i", levelLut.PaletteCount());
	PrintText(E_FILEINFO_X, E_FILEINFO_Y+24, "Colors per palette: %i", levelLut.ColorsPerPalette());
	PrintText(E_FILEINFO_X, E_FILEINFO_Y+32, "Destination: %i", levelLut.DestinationIndex());*/
	PrintText(E_PALETTEINFO_X, E_PALETTEINFO_Y, "Current palette: %i/256 in %i/%i", palSelector->getLutIndex()+1, palSelector->getDepthIndex()+1, CLUT_COUNT);

	PrintText(E_FILEINFO_ANIMPAL_X, E_FILEINFO_ANIMPAL_Y, "File: %s", getLevel()->MakePath(getLevel()->currentAct, STAGEFILE_DPL));

	PrintText(E_PALETTE_COLORCHANGER_X, E_PALETTE_COLORCHANGER_Y(-1), "Selected color: %02X", palSelector->getColorIndex());
	TextColor(TEXTCOLOR_RED);	PrintChar(E_PALETTE_COLORCHANGER_X, E_PALETTE_COLORCHANGER_Y(0), 'R');
	TextColor(TEXTCOLOR_GREEN);	PrintChar(E_PALETTE_COLORCHANGER_X, E_PALETTE_COLORCHANGER_Y(1), 'G');
	TextColor(TEXTCOLOR_BLUE);	PrintChar(E_PALETTE_COLORCHANGER_X, E_PALETTE_COLORCHANGER_Y(2), 'B');
	TextColor(TEXTCOLOR_WHITE);	PrintChar(E_PALETTE_COLORCHANGER_X, E_PALETTE_COLORCHANGER_Y(3), 'A');
	PrintText(E_PALETTE_COLORCHANGER_X + E_PALETTE_COLORCHANGER_W + 16, E_PALETTE_COLORCHANGER_Y(0), "%3i (%02X)", r, r);
	PrintText(E_PALETTE_COLORCHANGER_X + E_PALETTE_COLORCHANGER_W + 16, E_PALETTE_COLORCHANGER_Y(1), "%3i (%02X)", g, g);
	PrintText(E_PALETTE_COLORCHANGER_X + E_PALETTE_COLORCHANGER_W + 16, E_PALETTE_COLORCHANGER_Y(2), "%3i (%02X)", b, b);
	PrintText(E_PALETTE_COLORCHANGER_X + E_PALETTE_COLORCHANGER_W + 16, E_PALETTE_COLORCHANGER_Y(3), "%3i (%02X)", a, a);
}

bool Editor::PaletteEditor::_InputMouse(short x, short y, int button)
{
	return false;
}