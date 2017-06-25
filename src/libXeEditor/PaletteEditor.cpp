#include "PaletteEditor.h"
#include "PaletteSelector.h"
#include "Slidebar.h"
#include "FixedMenu.h"
#include "../libXeEngine/Level.h"
#include "../libXeEngine/Graphic.h"

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

#define E_PALETTEINFO_X	E_FILEINFO_Y
#define E_PALETTEINFO_Y	(E_FILEINFO_Y+3)
#define E_FILEINFO_ANIMPAL_X (E_FILEINFO_X+32+3)
#define E_FILEINFO_ANIMPAL_Y (E_FILEINFO_Y)
#define E_PALETTE_SIZE	16
#define E_PALETTE_SIZEF	(float)(E_PALETTE_SIZE)
#define E_PALETTE_COLORCHANGER_Y(i) (E_PALETTEINFO_Y + (i) * 2 + 3)
#define E_PALETTE_COLORCHANGER_W	72

void eChangeColor(Editor::Slidebar *o, Editor::Control *parent, int value)
{
	((Editor::PaletteEditor*)parent)->WriteColor(o);
}

Editor::PaletteEditor::PaletteEditor(MainEditor *e) : Control(e)
{
	u8 fontWidth = font->GetWidth();
	u8 fontHeight = font->GetHeight();
	m_name = "Palette editor";
	
	palSelector = new PaletteSelector(e, this, E_PALETTEINFO_X, E_PALETTE_COLORCHANGER_Y(0) * fontHeight, 256);
	slideR = new Slidebar(e, this, E_PALETTEINFO_X + palSelector->getSize().width + 3 * fontWidth, E_PALETTE_COLORCHANGER_Y(0) * fontHeight, E_PALETTE_COLORCHANGER_W);
	slideR->setMax(256);
	slideR->eChangeValue = eChangeColor;
	slideG = new Slidebar(e, this, E_PALETTEINFO_X + palSelector->getSize().width + 3 * fontWidth, E_PALETTE_COLORCHANGER_Y(1) * fontHeight, E_PALETTE_COLORCHANGER_W);
	slideG->setMax(256);
	slideG->eChangeValue = eChangeColor;
	slideB = new Slidebar(e, this, E_PALETTEINFO_X + palSelector->getSize().width + 3 * fontWidth, E_PALETTE_COLORCHANGER_Y(2) * fontHeight, E_PALETTE_COLORCHANGER_W);
	slideB->setMax(256);
	slideB->eChangeValue = eChangeColor;
	slideA = new Slidebar(e, this, E_PALETTEINFO_X + palSelector->getSize().width + 3 * fontWidth, E_PALETTE_COLORCHANGER_Y(3) * fontHeight, E_PALETTE_COLORCHANGER_W);
	slideA->setMax(256);
	slideA->eChangeValue = eChangeColor;
	lutFilesMenu = new FixedMenu(e, this, E_PALETTEINFO_X + palSelector->getSize().width + 1 * fontWidth, E_PALETTE_COLORCHANGER_Y(4) * fontHeight, 64);

	controlList.Add(palSelector);
	controlList.Add(slideR);
	controlList.Add(slideG);
	controlList.Add(slideB);
	controlList.Add(slideA);
	//controlList.Add(lutFilesMenu);
}
Editor::PaletteEditor::~PaletteEditor()
{

}

void Editor::PaletteEditor::setFocus(bool focus)
{
	/*if (focus == true)
	{
		XeEngine::LUTLoaded lut;
		XeEngine::List<XeEngine::LUTLoaded>* lutLoaded = getLevel()->lutLoaded;

		lutLoaded->MoveHead();
		for(int i=1; lutLoaded->Next(lut); i++)
		{
			lutFilesMenu->AddItem(lut.filename, i);
		}
	}
	else
	{
		lutFilesMenu->DeleteAllItems();
	}*/
}
XeEngine::Color32 Editor::PaletteEditor::getColor()
{
	return palSelector->getColor();
}
void Editor::PaletteEditor::setColor(XeEngine::Color32 color)
{
	return palSelector->setColor(color);
}

void Editor::PaletteEditor::WriteColor(Slidebar *s)
{
	XeEngine::Color32 color = getColor();
	XeEngine::Color32 value = XeEngine::Min(s->getValue(), 0xFF);
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
	u8 fontWidth = font->GetWidth();
	u8 fontHeight = font->GetHeight();

	XeEngine::Color32 c = getColor();
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

	XeEngine::String lutPath;
	XeEngine::String dplPath;
	getLevel()->BuildPath(lutPath, getLevel()->GetCurrentAct(), XeEngine::STAGEFILE_LUT);
	getLevel()->BuildPath(dplPath, getLevel()->GetCurrentAct(), XeEngine::STAGEFILE_DPL);

	PrintTextAligned(E_FILEINFO_X, E_FILEINFO_Y, "File: %s", lutPath.ToChar());
	/*PrintTextAligned(E_FILEINFO_X, E_FILEINFO_Y+1, "Format: %s", paletteeditor_formats[getGame()->levelLUT.Format()]);
	PrintTextAligned(E_FILEINFO_X, E_FILEINFO_Y+2, "Palette count: %i", levelLut.PaletteCount());
	PrintTextAligned(E_FILEINFO_X, E_FILEINFO_Y+3, "Colors per palette: %i", levelLut.ColorsPerPalette());
	PrintTextAligned(E_FILEINFO_X, E_FILEINFO_Y+4, "Destination: %i", levelLut.DestinationIndex());*/
	PrintTextAligned(E_PALETTEINFO_X, E_PALETTEINFO_Y + 0, "Current palette: %i/256 in %i/%i", palSelector->getLutIndex()+1, palSelector->getDepthIndex()+1, XeEngine::clutCount);
	PrintTextAligned(E_PALETTEINFO_X, E_PALETTEINFO_Y + 1, "Selected color: %02X", palSelector->getColorIndex());

	Position pos;
	pos = slideR->getPosition();
	TextColor(TEXTCOLOR_RED);	PrintChar(pos.x - (2 * fontWidth), pos.y, 'R');
	PrintText(slideR->getPosition().x + slideR->getSize().width, pos.y, "%3i (%02X)", r, r);
	pos = slideG->getPosition();
	TextColor(TEXTCOLOR_GREEN);	PrintChar(pos.x - (2 * fontWidth), pos.y, 'G');
	PrintText(slideG->getPosition().x + slideG->getSize().width, pos.y, "%3i (%02X)", g, g);
	pos = slideB->getPosition();
	TextColor(TEXTCOLOR_BLUE);	PrintChar(pos.x - (2 * fontWidth), pos.y, 'B');
	PrintText(slideB->getPosition().x + slideB->getSize().width, pos.y, "%3i (%02X)", b, b);
	pos = slideA->getPosition();
	TextColor(TEXTCOLOR_WHITE);	PrintChar(pos.x - (2 * fontWidth), pos.y, 'A');
	PrintText(slideA->getPosition().x + slideA->getSize().width, pos.y, "%3i (%02X)", a, a);


	PrintTextAligned(E_FILEINFO_ANIMPAL_X, E_FILEINFO_ANIMPAL_Y, "File: %s", dplPath.ToChar());
}

bool Editor::PaletteEditor::_InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
{
	return false;
}