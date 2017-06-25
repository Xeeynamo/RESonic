#pragma once
#include "XeEngineLV2.h"
#include "XeEngine.h"
#include "XeLevel.h"
#include "XeObject.h"

enum TEXTCOLOR
{
	TEXTCOLOR_WHITE,
	TEXTCOLOR_RED,
	TEXTCOLOR_GREEN,
	TEXTCOLOR_BLUE,
	TEXTCOLOR_YELLOW,
	TEXTCOLOR_MAGENTA,
	TEXTCOLOR_CYAN,
	TEXTCOLOR_GRAY
};

class GameState;
struct GameList 
{
	ushort id;
	char name[0xE];
};
class Game
{
private:
	ushort stageListCount;
	GameList *stageList;
	int textColor;
	void _internal_LoadStageList();
public:
	GameState *state;
	XeScene *scene;	// Gestione della scena
	XeTexture texFont;
	XeFont debugFont;

public:
	short _gameresWidth;
	short _gameresHeight;
	short _gameblockWidth;
	short _gameblockHeight;
	XeEngine::Memory memTileCache;
	TileEntry *tilecache;

	PFloat cameraX, cameraY;

	int _framecount;
	int _prevTime;	// Utile per i FPS
	float _prevfps;
public:
	XeTexture levelLUT;
	XeEffect effect;
	XeLevel level;

	Game();
	~Game();

	//////////////////////////////////////////////////////////////////////////
	// Imposta uno stato di gioco
	void SetGameState(GameState*);
	// Imposta il motore di rendering
	void SetScene(XeScene *render);
	// Imposta una risoluzione fissa
	void SetResolution(short width, short height);
	// Imposta una sequenza di tasti premuti
	void Input(KeyInput k);

	//////////////////////////////////////////////////////////////////////////
	// Imposta il font di debug
	bool LoadGFXFont(LPSTR);
	// Imposta la palette per il font di debug
	void LoadGFXCLUT(LPSTR);
	// blabla
	XeFont *GetFont();
	// Stampa del testo in formato ASCII nelle coordinate specificate
	void PrintText(short x, short y, const char* format, ...);
	// Cambia il colore del font
	void TextColor(TEXTCOLOR);
	// Ottiene il valore di FPS
	float GetFPS();

	//////////////////////////////////////////////////////////////////////////
	// Ottiene il numero totale di stages presenti nel gioco
	ushort StageListCount();
	// Ottiene il nome dello stage in base all'ID selezionato
	char *StageName(ushort id);
	// Ottiene il nome dello stage in base all'indice
	char *StageNameIndex(ushort id);

	//////////////////////////////////////////////////////////////////////////
	// Esegue la logica del gioco
	void Do();
	// Stampa il contenuto del gioco
	void Draw();

	//////////////////////////////////////////////////////////////////////////
	// Assembla un layer in blocchi
	void LevelBlock(int layerindex);
	// Stampa un layer
	void LevelDraw(int layerindex);
};