#include "Game.h"
#include "XeSystem.h"
#include "XeAnimation.h"
#include "XeObject.h"
#include "ObjectList.h"
#include <stdio.h>

// Gamestate list
#include "Game_tests.h"
#include "Game_Level.h"
#include "Game_LevelSelect.h"

#define SPEED_TO_FLOAT(i) (float(i)/256.0f)

extern XeAnimation anim;
Game::Game()
{
	_internal_LoadStageList();

	state = NULL;
	scene = NULL;
	textColor = 0;

	_framecount = 0;
	SetResolution(320, 240);
	XeShape::Initialize();
	cameraX = cameraY = 0;
	
	effect.MakeProgram(effect.CompileShader(GL_VERTEX_SHADER, "shader.vp.gsls"),
		effect.CompileShader(GL_FRAGMENT_SHADER, "shader.fp.gsls"));
}
Game::~Game()
{
	delete[] stageList;
}

void Game::_internal_LoadStageList()
{
	XeEngine::File f;
	stageListCount = 0;
	char path[0x40];

	sprintf_s(path, "%s\\%s.%s", "LEVEL", "LEVEL", "BIN");
	f.Open(XeEngine::String(path));
	f.Read(&stageListCount, 2);
	stageList = new GameList[stageListCount];
	f.Read(stageList, sizeof(GameList) * stageListCount);
	f.Close();
}

//////////////////////////////////////////////////////////////////////////
void Game::SetGameState(GameState *state)
{
	if (this->state) delete this->state;
	this->state = state;
}
void Game::SetScene(XeScene *scene)
{
	this->scene = scene;
	this->scene->SetClearColor(0x202018);
}
void Game::SetResolution(short width, short height)
{
	if (!scene) return;
	level.SetResolution(width, height);
	_gameresWidth = LOWORD(level.GetResolution());
	_gameresHeight = HIWORD(level.GetResolution());
	_gameblockWidth = level.chunkWidth;
	_gameblockHeight = level.chunkHeight;
	tilecache = level.tilecache;
	scene->SetCameraSize(_gameresWidth, _gameresHeight);
}

//////////////////////////////////////////////////////////////////////////
bool Game::LoadGFXFont(LPSTR filename)
{
	XeEngine::XeImage *gfxFont = new GFX;
	gfxFont->Load(XeEngine::String(filename));
	texFont.Create(gfxFont);
	delete gfxFont;
	debugFont.SetTexture(&texFont);
	return true;
}
void Game::LoadGFXCLUT(LPSTR filename)
{
	LUT lut;
	lut.Load(filename);
	level.LoadSharedLUT(&lut);
}
XeFont *Game::GetFont()
{
	return &debugFont;
}
void Game::PrintText(short x, short y, const char* format, ...)
{
	char str[0x100];
	va_list args;
	va_start(args, format);
	vsprintf_s(str, format, args);
	XeEffect::SetClutIndex(textColor);
	debugFont.SetXY(x, y);
	debugFont.PrintText(str);
	va_end(args);
}
void Game::TextColor(TEXTCOLOR color)
{
	textColor = color;
}
float Game::GetFPS()
{
	int currentTime;
	int intervalTime;
	_framecount++;
	currentTime = XeEngine::System::GetTimer(); // Equivalente di GetTickCount
	intervalTime = currentTime - _prevTime;
	if (intervalTime > 1000)
	{
		_prevfps = (float)_framecount / ((float)intervalTime / 1000.0f);
		_prevTime = currentTime;
		_framecount = 0;
	}
	return _prevfps;
}

//////////////////////////////////////////////////////////////////////////
ushort Game::StageListCount()
{
	return stageListCount;
}
char *Game::StageName(ushort id)
{
	for(int i=0; i<stageListCount; i++)
	{
		if (stageList[i].id == id)
			return stageList[i].name;
	}
	return NULL;
}
char *Game::StageNameIndex(ushort index)
{
	return stageList[index].name;
}
void Game::Input(KeyInput k)
{
	if (state) state->Input(k);
}

//////////////////////////////////////////////////////////////////////////
void Game::Do()
{
	//if (!state) SetGameState(new Game_Tests(this));
	if (!state) SetGameState(new Game_LevelSelect(this));
	state->Do();
}
void Game::Draw()
{
	scene->SetCameraSize(_gameresWidth, _gameresHeight);
	scene->OnPaintBegin();
	//glColorMask(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	state->Draw();

	XeEffect::SetProperties(0);
	XeShape::SetColor(0xFF000000);
	XeShape::FadeEffect();
	scene->OnPaintEnd();
}
void Game::LevelBlock(int layerindex)
{
	short *layer = layer = level.map.GetLayer(layerindex);
	byte stride = level.map.Layer(layerindex)->width;
	byte height = level.map.Layer(layerindex)->height;
	short layerCameraX = int(level.cameraX * SPEED_TO_FLOAT(level.map.Layer(layerindex)->speedX))>>20;
	short layerCameraY = int(level.cameraY * SPEED_TO_FLOAT(level.map.Layer(layerindex)->speedY))>>20;
	short blockWidth = _gameblockWidth;
	short blockHeight = _gameblockHeight;

	for(int j=layerCameraY; j<blockHeight+layerCameraY; j++)
	{
		for(int i=layerCameraX; i<blockWidth+layerCameraX; i++)
		{
			tilecache[i-layerCameraX + (j-layerCameraY)*blockWidth] = level.GetBlock(i, j, stride, height, layer);
		}
	}
}
void Game::LevelDraw(int layerindex)
{
	short prevPalette = -1;
	TileEntry tileblock;
	effect.UseProgram(true);
	effect.SetProperties(1);
	effect.SetClutDepth(1, CLUT_COUNT);
	scene->SetPosition(-(HIWORD(level.cameraX * SPEED_TO_FLOAT(level.map.Layer(layerindex)->speedX))&15),
		-(HIWORD(level.cameraY * SPEED_TO_FLOAT(level.map.Layer(layerindex)->speedY))&15), level.map.Layer(layerindex)->priority);
	for(int j=0; j<_gameblockHeight; j++)
	{
		for(int i=0; i<_gameblockWidth; i++)
		{
			tileblock = tilecache[i + j*_gameblockWidth];
			if (tileblock.palette != prevPalette)
			{
				prevPalette = tileblock.palette;
				effect.SetClutIndex(prevPalette);
			}
			level.texture.SetPosition(0, 0, 0.0f);

			XeScene::Push();
			XeScene::MovePosition(i<<4, j<<4);
			scene->MovePosition(+8, +8, tileblock.depth ? 2.0f : 0);
			scene->SetScale(tileblock.mirror ? -1.0f : 1.0f, tileblock.flip ? -1.0f : 1.0f);
			scene->MovePosition(-8, -8, tileblock.depth ? 0.0f : 0);

			level.texture.Draw((tileblock.tile&0xF)<<4, tileblock.tile&0xF0, 16, 16, tileblock.texture, NULL);
			XeScene::Pop();
		}
	}
}