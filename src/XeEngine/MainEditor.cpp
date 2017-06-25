#include "MainEditor.h"
#include "Preview.h"
#include "MapEditor.h"
#include "PaletteEditor.h"
#include "TextureEditor.h"
#include "ChunkEditor.h"
#include "XeMath.h"

Editor::MainEditor::MainEditor(Game *g) : Control(NULL)
{
#ifndef REMOVE_EDITOR
	m_name = "MainEditor";
#else
	m_name = "PLS";
#endif
	pointerColor = XeEngine::ColorHSV(0.0f, 0.75f, 0.75f);

	this->g = g;
	this->l = &g->level;
	this->font = g->GetFont();
	UpdateCollisions();
	eWidth = LOWORD(getGame()->scene->GetCameraSize());
	eHeight = HIWORD(getGame()->scene->GetCameraSize());

	wheely = 0;
	showGuide = false;
	doubleres = false;
	mode = 0;
	ctrl = alt = shift = false;
	ZeroMemory(controls, sizeof(controls));
	controls[0] = new Preview(this);
#ifndef REMOVE_EDITOR
	controls[1] = NULL;
	controls[2] = NULL;
	controls[3] = new MapEditor(this);
	controls[4] = NULL;
	controls[5] = new PaletteEditor(this);
	controls[6] = new TextureEditor(this);
	controls[7] = new ChunkEditor(this);
	controls[8] = NULL;
	controls[9] = NULL;
#endif
}
Editor::MainEditor::~MainEditor()
{

}

Editor::Control *Editor::MainEditor::GetControlMode()
{
	return controls[mode];
}
int Editor::MainEditor::GetMode()
{
	return this->mode;
}
void Editor::MainEditor::SetMode(int mode)
{
	if (controls[this->mode]) controls[this->mode]->setFocus(false);
	this->mode = mode;
	if (controls[this->mode]) controls[this->mode]->setFocus(true);
}
bool Editor::MainEditor::getDoubleView()
{
	return this->doubleres;
}
void Editor::MainEditor::setDoubleView(bool doubleview)
{
	this->doubleres = doubleview;
}
bool Editor::MainEditor::getShowFps()
{
	return this->showfps;
}
void Editor::MainEditor::setShowFps(bool showfps)
{
	this->showfps = showfps;
}
short Editor::MainEditor::getFpsCount()
{
	return this->fps;
}

//////////////////////////////////////////////////////////////////////////
// Funzioni proprie
void Editor::MainEditor::RefreshPalette()
{
	if (getGame()->levelLUT.GetID() == -1)
		getGame()->levelLUT.Create(256, 256, CLUT_COUNT, XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_RGBA8888, getLevel()->palette);
	else
		getGame()->levelLUT.Upload(0, 0, 256, 256, 0, CLUT_COUNT, getLevel()->palette);
	XeEffect::SetClutTexture(getGame()->levelLUT.GetID());
	XeEffect::SetTexture();
}
void Editor::MainEditor::UpdateTiles()
{
	getLevel()->dynamicTiles.Tick(&getLevel()->texture);
}
void Editor::MainEditor::UpdateCollisions()
{
	con.Log(DEBUG_LEVEL_WARNING, "Editor::MainEditor::UpdateCollisions() not implemented yet");
}
void Editor::MainEditor::ShowGuide()
{
	PrintText(0,  16, "[0] Game");
	PrintText(0,  24, "[1] -");
	PrintText(0,  32, "[2] -");
	PrintText(0,  40, "[3] Layout editor");
	PrintText(0,  48, "[4] Object placement");
	PrintText(0,  56, "[5] Palette editor");
	PrintText(0,  64, "[6] Tile viewer");
	PrintText(0,  72, "[7] Chunk editor");
	PrintText(0,  80, "[8] Hit box editor");
	PrintText(0,  88, "[9] -");
	PrintText(0,  96, "[*] 2x resolution");
	PrintText(0, 104, "[F1] Show this guide");
	PrintText(0, 112, "[F4] Save");

	XeEffect::SetFadeFactor(0.2f);
	XeEffect::SetSaturation(0.8f);
}

Game *Editor::MainEditor::getGame()
{
	return g;
}
XeLevel *Editor::MainEditor::getLevel()
{
	return l;
}
short Editor::MainEditor::getEditorWidth()
{
	return eWidth;
}
short Editor::MainEditor::getEditorHeight()
{
	return eHeight;
}
Editor::CtrlPosition Editor::MainEditor::getMouseCoord()
{
	CtrlPosition pos;
	pos.x = mouseX;
	pos.y = mouseY;
	return pos;
}
XeScene *Editor::MainEditor::getScene()
{
	return &scene;
}
XeTexture *Editor::MainEditor::getTextureCollision()
{
	return &texCollision;
}
bool Editor::MainEditor::isCtrlPressed()
{
	return ctrl;
}
bool Editor::MainEditor::isAltPressed()
{
	return alt;
}
bool Editor::MainEditor::isShiftPressed()
{
	return shift;
}

short Editor::MainEditor::getWheelY()
{
	return this->wheely;
}
void Editor::MainEditor::InputWheel(short wheely)
{
	this->wheely = wheely;
	InputKeyb(-1);
	this->wheely = 0;
}
void Editor::MainEditor::_Draw()
{
	pointerColor.h += 1.0f;
	if (pointerColor.h >= 360.0f)
		pointerColor.h -= 360.0f;
	getLevel()->palette[0][0][0xF] = XeEngine::Color::Convert(pointerColor).ToColor32();
	RefreshPalette();
	UpdateTiles();

	getScene()->OnPaintBegin();
#ifndef REMOVE_EDITOR
	eWidth = LOWORD(getGame()->scene->GetCameraSize());
	eHeight = HIWORD(getGame()->scene->GetCameraSize());
	if (mode != 0 && doubleres)
	{
		eWidth /= 2;
		eHeight /= 2;
		XeScene::SetCameraSize(eWidth, eHeight);
		XeScene::SetScale(2.0f, 2.0f);
	}

	getScene()->OnPaintBegin();
	//glColorMask(1.0, 1.0, 1.0, 1.0);
	if (GetMode() != 0)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	XeEffect::UseProgram(true);
	XeEffect::SetProperties(PROPERTIES_CLUT);
	XeEffect::SetEffect(0);
	XeEffect::SetClutIndex(0);
	XeEffect::SetClutDepth(0, CLUT_COUNT);
	XeEffect::SetFadeFactor(1.0f);
	
	if (showGuide) ShowGuide();

	if (GetControlMode())
	{

		if (GetMode() != 0 ? getLevel()->stage.act != NULL : 1)
		{
			PrintText(0, 0, "Mode: %s", GetControlMode()->getName());
			GetControlMode()->Draw();
		}
		else
		{
			PrintText(0, 0, "No level loaded.");
		}
	}
	else
	{
		PrintText(0, 0, "Mode %i not implemented.", mode);
	}

	XeEffect::SetFadeFactor(1.0);
	XeEffect::SetSaturation(0.0);
	XeEffect::SetClutDepth(0, CLUT_COUNT);
	XeEffect::SetClutIndex(0);
	if (getShowFps())
		PrintText(0, getEditorHeight()-8, "FPS %f", g->GetFPS());

	if (GetMode() != 0)
		PrintChar(mouseX, mouseY, 0xFF);

	if (getDoubleView())
		g->scene->SetCameraSize(getEditorWidth()*2, getEditorHeight()*2);
#else
	GetControlMode()->Draw();
#endif
	getScene()->OnPaintEnd();
}

bool Editor::MainEditor::_InputKeyb(int key, bool up)
{
	switch(key)
	{
	case VK_F1:
		showGuide = !up;
		break;
	}
	ctrl = GetKeyState(VK_CONTROL) < 0;
	alt = GetKeyState(VK_CONTROL) < 0;
	shift = GetKeyState(VK_CONTROL) < 0;
	if (GetControlMode()) GetControlMode()->InputKeyb(key, up);
	return _InputKeyb(up ? 0 : key);
}
bool Editor::MainEditor::_InputKeyb(int key)
{
	bool result = false;
	if (key == 0)
	{
		prevkey = 0;
		continuekeypress = false;
	}
	else if (prevkey != key || continuekeypress)
	{
		if (GetControlMode()) result = GetControlMode()->InputKeyb(key);
		if (prevkey != key)
		{
			prevkey = key;
			continuekeypress = false;
		}
	}
	else continuekeypress = true;
	return result;
}
bool Editor::MainEditor::_InputChar(int character)
{
#ifndef REMOVE_EDITOR
	switch(character)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		SetMode(character - '0');
		return true;
	case '*':
		setDoubleView(getDoubleView()^1);
		return true;
	}
#endif
	if (GetControlMode()) GetControlMode()->InputChar(character);
	return true;
}
bool Editor::MainEditor::_InputMouse(short x, short y, int button)
{
	if (getDoubleView())
	{
		x /= 2;
		y /= 2;
	}
	mouseX = x;
	mouseY = y;
	if (GetControlMode()) GetControlMode()->InputMouse(x, y, button);
	return true;
}
