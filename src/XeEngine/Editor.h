#pragma once
#include "Game.h"
#include "OtherEngines.h"
#include "XeFormats.h"
#include "XeObjectAnimation.h"


class XeEditor
{
private:
	Game *g;
	XeLevel *level;
	XeScene *_scene;

	XeTexture texWhite;

	bool keyCtrl;
	byte mousebutton;
	short mousex, mousey;
	signed short _wheel;
	short editorWidth, editorHeight;

	int framecount;
	byte _editor_submode;

	// Mode 1 sub 1
	size_t _charpos;
	// Mode 5
	byte _texselected;
	byte _palselected;
	ushort _blockselected;
	ushort _blockpreview;
	ushort _subblockselected;
	ushort _subblockpreview;
	byte _tileblockselected;
	byte _tileblockpreview;
	byte _collblockselected;
	byte _collblockpreview;
	byte _rightclickf;
	byte _rightclickmod;
	short _rightclickx;
	short _rightclicky;

	bool _showguide;
	bool _showfps;
	bool _double;

	LUT levelLut;
	char name_levelGfx[0x20];
	GFX levelGfx;
	char name_levelLut[0x20];
	BLK levelBlock;
	char name_levelblock[0x20];
	MAP *levelMap;
	HBX levelHitbox;
	char name_levelHitbox[0x20];
	CLI levelColIndex;
	char name_levelColIndex[0x20];

	XeTexture texCollision;
protected:
	void _internal_DrawLevel(short layer, short posx, short posy);
	void _internal_CollisionTexture();
	void _internal_CollisionBlockToRaw(unsigned char *raw, char *collision, unsigned char emptyvalue);
	void _internal_CollisionSheetToRaw(unsigned char *raw, Collision *c, unsigned char emptyvalue);
	void _internal_DrawBlock(int blockindex);
	void _internal_DrawBlockCollision(int blockindex);
protected:
	// Modalità 0 - Preview
	KeyInput k;
	bool hudDebug;
	void init_Preview();
	void draw_Preview();
	void input_Preview(WPARAM key, bool keyup);
	void char_Preview(WPARAM character);
	void mouse_Preview(short x, short y, WPARAM button);
	// Modalità 3 - Layout
	float _mapLeftBarFade;
	char _layoutselected;
	short _mapposx;
	short _mapposy;
	short _mapmovemousex;
	short _mapmovemousey;
	short _mapblockscroll;
	short _mapblockselected;
	bool _mapMouseOnMap;
	bool _mapOnLeftBar;
	short _mapCursorX;
	short _mapCursorY;
	void init_Map();
	void draw_Map();
	void input_Map(WPARAM key, bool keyup);
	void char_Map(WPARAM character);
	void mouse_Map(short x, short y, WPARAM button);
	int GetMapBlockEditorSize(short width, short height);
	// Modalità 4 - Object
	XeObjectAnimation objanim[0x200];
	ushort _objectViewIndex;					// Indice del menu a destra dove c'è la selezione degli oggetti
	ushort _selectedobj;
	byte _onmouseobjsCount;						// Quanti oggetti sono sotto il puntatore del mouse in quel momento (MASSIMO 6)
	ushort _onmouseobjs[6];						// Quali oggetti sono sotto il puntatore del mouse in quel momento (MASSIMO 6)
	void init_Object();
	void draw_Object();
	void input_Object(WPARAM key, bool keyup);
	void char_Object(WPARAM character);
	void mouse_Object(short x, short y, WPARAM button);
	void DrawObjectStatus(OBPEntry *e, ushort position);
	// Modalità 5 - Texture
	// Modalità 6 - Palette
	int _palDepthSelected;
	void init_Lut();
	void draw_Lut();
	void input_Lut(WPARAM key, bool keyup);
	void char_Lut(WPARAM character);
	void mouse_Lut(short x, short y, WPARAM button);
	// Modalità 7 - Blocchi
	bool _collisionmode;
	short _blockscroll;
	void init_Block();
	void draw_Block();
	void input_Block(WPARAM key, bool keyup);
	void char_Block(WPARAM character);
	void mouse_Block(short x, short y, WPARAM button);
	void BlockED_Draw_Tilemenu();
	bool BlockED_Input_Tilemenu();
	bool BlockED_Mouse_Tilemenu();
	void BlockED_Draw_Collisionmenu();
	bool BlockED_Mouse_Collisionmenu();
	// Modalità 8 - Collisioni
	byte _colverse;
	byte _colselected;
	byte _colpreview;
	void init_Collision();
	void draw_Collision();
	void input_Collision(WPARAM key, bool keyup);
	void char_Collision(WPARAM character);
	void mouse_Collision(short x, short y, WPARAM button);

public:
	byte EditorMode;
	void *hWnd;

	XeEditor();
	~XeEditor();

	void AttachGame(Game*);
	void AttachScene(XeScene*);
	void Draw();
	void InputKey(WPARAM key, bool keyup);
	void InputChar(WPARAM character);
	void InputMouse(short x, short y, WPARAM button);
	void InputWheel(signed short wheel);

	void ShowFPS(bool enabled);
};