#include "MainEditor.h"
#include "Preview.h"
#include "MapEditor.h"
#include "PaletteEditor.h"
#include "TextureEditor.h"
#include "ChunkEditor.h"
#include "LevelSelect.h"
#include "HitboxEditor.h"
#include "../libXeEngine/Window.h"
#include "../libXeEngine/Graphic.h"
#include <stdio.h>

namespace Editor
{
	static MainEditor* maineditor;
	void cbInputKeyb(XeEngine::InputButton key, bool up)
	{
		maineditor->_InputKeyb(key, up);
	}
	void cbInputChar(XeEngine::InputButton character)
	{
		maineditor->_InputChar(character);
	}
	void cbInputMouse(u16 x, u16 y, XeEngine::MouseInput button)
	{
		maineditor->_InputMouse(x, y, button);
	}
	void cbInputTouch(u16 x, u16 y, XeEngine::TouchInput button)
	{

	}
}

Editor::MainEditor::MainEditor(XeEngine::Game *g) : Control(NULL)
{
	//con.Log(DEBUG_LEVEL_INFO, "Initializing MainEditor...");
	maineditor = this;
	m_name = "MainEditor";
	pointerColor[0] = XeEngine::ColorHSV(0.0f, 1.0f, 1.0f);
	pointerColor[1] = XeEngine::ColorHSV(90.0f, 1.0f, 1.0f);
	pointerColor[2] = XeEngine::ColorHSV(180.0f, 1.0f, 1.0f);
	pointerColor[3] = XeEngine::ColorHSV(270.0f, 1.0f, 1.0f);

	this->g = g;
	this->l = g->GetLevel();
	eWidth = 800;
	eHeight = 512;
	mouseX = mouseY = 0;
	font = &fontEditor;

	wheely = 0;
	showGuide = false;
	doubleres = false;
	mode = 0;
	ctrl = alt = shift = false;
	textColorIndex = TEXTCOLOR_WHITE;
	input = nullptr;
	ZeroMemory(controls, sizeof(controls));

	setShowFps(true);
	//con.Log(DEBUG_LEVEL_INFO, "MainEditor initialized");
}
Editor::MainEditor::~MainEditor()
{
	for(int i=0; i<10; i++)
		SAFE_DELETE(controls[i]);
}

void Editor::MainEditor::Initialize()
{
	lutEditor = XeEngine::Graphic::lut[3];
	texFont.Create(XeEngine::String("FONT\\DOS_8x12.GFX"));
	//texFont.Create(XeEngine::String("FONT\\DOS_12x16.GFX"));
	//texFont.Create(XeEngine::String("FONT\\S2@1.GFX"));
	fontEditor.SetTexture(texFont);
	fontEditor.SetPalette(0, 3);

	XeEngine::Graphic::LoadPalette(XeEngine::String("FONT\\S2.LUT"), 0, 3);

	collisionTexture.Create(nullptr, XeEngine::VideoPixelFormat_A8, 256, 512);
	UpdateCollisions();

	input = (XeEngine::XInput*)XeEngine::XInput::Get();
	input->InputKeyb = cbInputKeyb;
	input->InputChar = cbInputChar;
	input->InputMouse = cbInputMouse;
	input->InputTouch = cbInputTouch;

	controls[0] = new Preview(this);
	controls[1] = NULL;
	controls[2] = NULL;
	controls[3] = new MapEditor(this);
	controls[4] = NULL;
	controls[5] = new PaletteEditor(this);
	controls[6] = new TextureEditor(this);
	controls[7] = new ChunkEditor(this);
	controls[8] = new HitboxEditor(this);
	controls[9] = NULL;
	controls[10] = new LevelSelect(this);
}
bool Editor::MainEditor::Run()
{
	/*XeEngine::Input* joypadInput = XeEngine::Input::Get();
	XeEngine::Keys k = joypadInput->PeekNoRepeat();

	if (k & XeEngine::InputKey_BACK)
	{
		SetMode((GetMode() + 1) % 10);
	}
	int mlx = joypadInput->GetLX();
	int mly = joypadInput->GetLY();
	if (mlx >= 32767 || mlx <= -32768) mlx *= 2;
	if (mly >= 32767 || mly <= -32768) mly *= 2;
	mouseX += (mlx / 4096);
	mouseY -= (mly / 4096);
	if (mouseX < 0) mouseX = 0;
	else if (mouseX > eWidth) mouseX = eWidth;
	if (mouseY < 0) mouseY = 0;
	else if (mouseY > eHeight) mouseY = eHeight;
	XeEngine::MouseInput input = XeEngine::MouseInput_MOVE;
	switch(k)
	{
	case XeEngine::InputKey_START:
		SetMode(0);
		break;
	case XeEngine::InputKey_CROSS:
		input = XeEngine::MouseInput_LEFT;
		break;
	case XeEngine::InputKey_CIRCLE:
		input = XeEngine::MouseInput_RIGHT;
		break;
	case XeEngine::InputKey_SQUARE:
		input = XeEngine::MouseInput_MIDDLE;
		break;
	}
	_InputMouse(mouseX, mouseY, input);*/

	Draw();
	CalculateFPS();
	return GetMode() != 0;
}
void Editor::MainEditor::CalculateFPS()
{
	static int fps_frameCounter = 0;

	fps_frameCounter++;
	u32 time = XeEngine::System::GetTimer();
	if ((time - prevtime) >= 1000)
	{
		fps = (float)fps_frameCounter / (float)(time - prevtime) * 1000.0f;
		prevtime = time;
		fps_frameCounter = 0;
	}
	printf("\r%.3f", fps);
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
	UpdateCollisions();
}
void Editor::MainEditor::SetRenderSize(short width, short height)
{
	eWidth = width;
	eHeight = height;
}
bool Editor::MainEditor::getDoubleView()
{
	return this->doubleres;
}
void Editor::MainEditor::setDoubleView(bool doubleview)
{
	this->doubleres = doubleview;
}
bool Editor::MainEditor::getShowFps() const
{
	return this->showfps;
}
void Editor::MainEditor::setShowFps(bool showfps)
{
	this->showfps = showfps;
}
float Editor::MainEditor::getFpsCount() const
{
	return this->fps;
}

//////////////////////////////////////////////////////////////////////////
// Funzioni proprie
void Editor::MainEditor::RefreshPalette()
{
	getLevel()->RefreshPalette();
}
void Editor::MainEditor::UpdateTiles()
{
	//getLevel()->dynamicTiles.Tick(&getLevel()->texture);
}
void Editor::MainEditor::UpdateCollisions()
{
	XeEngine::Memory memtmp;
	memtmp.Alloc(256 * 256);
	CollisionFloor((u8*)memtmp.GetMemoryHandle(), 1);
	collisionTexture.Upload((u8*)memtmp.GetMemoryHandle(), 0, 0, 256, 256);
	CollisionWall((u8*)memtmp.GetMemoryHandle(), 1);
	collisionTexture.Upload((u8*)memtmp.GetMemoryHandle(), 0, 256, 256, 256);
}
void Editor::MainEditor::ShowGuide()
{
	int index = 0;
	PrintTextAligned(0, index++, "[0] Game");
	PrintTextAligned(0, index++, "[1] Map assembly (NA)");
	PrintTextAligned(0, index++, "[2] Parallax editor (NA)");
	PrintTextAligned(0, index++, "[3] Layout editor");
	PrintTextAligned(0, index++, "[4] Object placement");
	PrintTextAligned(0, index++, "[5] Palette editor");
	PrintTextAligned(0, index++, "[6] Tile viewer");
	PrintTextAligned(0, index++, "[7] Chunk editor");
	PrintTextAligned(0, index++, "[8] Hit box editor");
	PrintTextAligned(0, index++, "[9] Object editor (NA)");
	PrintTextAligned(0, index++, "[9] Object editor (NA)");
	PrintTextAligned(0, index++, "[*] 2x resolution");
	PrintTextAligned(0, index++, "[F1] Show this guide");
	PrintTextAligned(0, index++, "[F2] Level select");
	PrintTextAligned(0, index++, "[F4] Save");

	/*XeEngine::Video::Get()->UseProgram(fontEffect->GetID());
	fontEffect->SetFadeFactor(0.1f);
	fontEffect->SetSaturation(0.8f);
	XeEngine::Video::Get()->UseProgram(l->effLevel->GetID());
	getLevel()->effLevel->SetSaturation(0.2f);
	getLevel()->effLevel->SetFadeFactor(0.8f);*/
}

XeEngine::Game* Editor::MainEditor::getGame()
{
	return g;
}
XeEngine::Level* Editor::MainEditor::getLevel()
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
Editor::Position Editor::MainEditor::getMouseCoord()
{
	Position pos;
	pos.x = mouseX;
	pos.y = mouseY;
	return pos;
}
XeEngine::Texture* Editor::MainEditor::getTextureCollision()
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
void Editor::MainEditor::TextColor(TEXTCOLOR color)
{
	textColorIndex = color;
}

void Editor::MainEditor::CollisionFloor(u8* memory, u8 fill)
{
	unsigned char colblock[16*16];
	for(int i=0; i<0x100; i++)
	{
		Floor2Image(colblock, i, fill);
		for(int j=0; j<16; j++)
		{
			XeEngine::MemoryCopy(&memory[j*256 + ((i>>4)*256*16) + ((i&0xF)*16)], &colblock[j*16], 16);
		}
	}
}
void Editor::MainEditor::CollisionWall(u8* memory, u8 fill)
{
	unsigned char colblock[16*16];
	for(int i=0; i<0x100; i++)
	{
		Wall2Image(colblock, i, fill);
		for(int j=0; j<16; j++)
		{
			XeEngine::MemoryCopy(&memory[j*256 + ((i>>4)*256*16) + ((i&0xF)*16)], &colblock[j*16], 16);
		}
	}
}
void Editor::MainEditor::Floor2Image(u8* memory, u8 index, u8 fill)
{
	XeEngine::MemoryFill(memory, 16 * 16);
	s8* c = getLevel()->hitboxFloor[index];
	for(int i=0; i<16; i++)
	{
		memory[i] = 0;
		if ((unsigned char)c[i] > 0x80)
		{
			for(int j=0; j<(unsigned char)(~c[i]+1); j++)
			{
				if (j >= 16) continue;
				memory[j*16+i] = 0x01;
			}
		}
		else
		{
			for(int j=0; j<c[i]; j++)
			{
				memory[(0xF-j)*16 +i] = 0x01;
			}
		}
	}
}
void Editor::MainEditor::Wall2Image(u8* memory, u8 index, u8 fill)
{
	XeEngine::MemoryFill(memory, 16 * 16);
	s8* c = getLevel()->hitboxWall[index];
	for(int i=0; i<16; i++)
	{
		memory[i] = 0;
		if ((unsigned char)c[i] > 0x80)
		{
			for(int j=0; j<(unsigned char)(~c[i]+1); j++)
			{
				memory[j*16+i] = 0x01;
			}
		}
		else
		{
			for(int j=0; j<c[i]; j++)
			{
				memory[(0xF-j)*16 +i] = 0x01;
			}
		}
	}
}
XeEngine::Texture* Editor::MainEditor::GetCollisionTexture()
{
	return &collisionTexture;
}
void Editor::MainEditor::DrawCollision(u8 index, u8 verse, XeEngine::Point point, XeEngine::Size size)
{
	XeEngine::Point psrc((float)((index & 0xF) << 4), (float)(index & 0xF0));
	XeEngine::Size ssrc(16, 16);
	GetCollisionTexture()->Draw(point, size, psrc, ssrc, verse ? 1 : 0);
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
	//video->SetSaturation(0.0f);
	//video->SetFadeFactor(1.0f);
	//video->SetClutDepth(3, XeEngine::clutCount);
	//video->SetClutIndex(0);

	for(int i = 0; i < 4; i++)
	{
		pointerColor[i].h += 2.0f;
		if (pointerColor[i].h >= 360.0f)
			pointerColor[i].h -= 360.0f;

		lutEditor[0x000F - i] = XeEngine::Color::Convert(pointerColor[i]).ToColor32();
	}
	getLevel()->UpdatePalette();

	if (GetMode() != 0 && getDoubleView())
	{
		eWidth /= 2;
		eHeight /= 2;
		//video->LineWidth(2.0f);
	}
	XeEngine::Graphic::SetProjection2D(eWidth, eHeight);
	
	if (showGuide) ShowGuide();

	if (GetControlMode())
	{
		if (GetMode() != 0 ? getLevel()->stage.act != NULL : 1)
		{
			PrintTextAligned(0, 0, "Mode: %s", GetControlMode()->getName());
			GetControlMode()->Draw();
		}
		else
		{
			PrintTextAligned(0, 0, "No level loaded.");
		}
	}
	else
	{
		PrintTextAligned(0, 0, "Mode %i not implemented.", mode);
	}

	if (getShowFps())
		PrintText(0, getEditorHeight() - font->GetHeight(), "FPS %f", getFpsCount());

	if (GetMode() != 0)
		PrintChar(mouseX, mouseY, 0xFF);

	if (GetMode() != 0 && getDoubleView())
	{
		eWidth *= 2;
		eHeight *= 2;
		XeEngine::Graphic::SetProjection2D(eWidth, eHeight);
		//video->LineWidth(1.0f);
	}
}

bool Editor::MainEditor::_InputKeyb(XeEngine::InputButton key, bool up)
{
	switch(key)
	{
	case VK_F1:
		showGuide = !up;
		break;
	case VK_F2:
		SetMode(10);
		break;
	}
	ctrl = GetKeyState(VK_CONTROL) < 0;
	alt = GetKeyState(VK_CONTROL) < 0;
	shift = GetKeyState(VK_CONTROL) < 0;
	if (GetControlMode()) GetControlMode()->InputKeyb(key, up);
	return _InputKeyb(up ? 0 : key);
}
bool Editor::MainEditor::_InputKeyb(XeEngine::InputButton key)
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
bool Editor::MainEditor::_InputChar(XeEngine::InputButton character)
{
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
	if (GetControlMode()) GetControlMode()->InputChar(character);
	return true;
}
bool Editor::MainEditor::_InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
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
