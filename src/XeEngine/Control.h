#pragma once
#include <windows.h>
#include "XeBase.h"

class Game;
class XeLevel;
class XeFont;
namespace Editor
{
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

	struct CtrlSize
	{
		short width;
		short height;
	};
	struct CtrlPosition
	{
		short x;
		short y;
	};

	class MainEditor;
	class Control
	{
	protected:
		char *m_name;
		MainEditor *e;
		Control *parent;
		List<Control*> controlList;

		bool enabled;
		bool visible;
		bool focus;
		CtrlPosition position;
		CtrlSize size;

		bool collisionview;
		int textColor;
		XeFont *font;

		bool fadeOnLoseFocus;
		float fadefactor;

		virtual void _Draw() = 0;
		virtual bool _InputKeyb(int key, bool up){ return false; }
		virtual bool _InputKeyb(int key){ return false; };
		virtual bool _InputChar(int character){ return false; };
		virtual bool _InputMouse(unsigned short x, unsigned short y, int button){ return false; };
		virtual bool _InputTouch(unsigned short x, unsigned short y, int button){ return false; };
	public:
		Control(MainEditor *e, Control *parent = 0, short x = 0, short y = 0, short width = 0, short height = 0);
		~Control()
		{
			Control *c;
			controlList.First();
			while(controlList.Next(&c)) delete c;
		}

		bool Enable() { return enabled & visible; }
		void Enable(bool enabled) { this->enabled = enabled; }
		bool Visible() { return visible; }
		void Visible(bool visible) { this->visible = visible; }
		CtrlPosition getPosition() { return position; }
		void setPosition(CtrlPosition position) { this->position = position; }
		virtual CtrlSize getSize();
		virtual void setSize(CtrlSize size);
		virtual bool getFocus();
		virtual void setFocus(bool focus);
		virtual void setFadeOnLoseFocus(bool);
		virtual CtrlPosition getMouseCoord();
		void AddControl(Control *c);
		// Funzioni strettamente legate al gioco
		virtual Game *getGame();
		virtual XeLevel *getLevel();
		virtual short getEditorWidth();
		virtual short getEditorHeight();
		virtual char *getName();
		virtual bool getCollisionView();
		virtual void setCollisionView(bool);
		// Funzioni strettamente legate all'editor
		bool isCtrlPressed();
		bool isAltPressed();
		bool isShiftPressed();

		// Stampa un singolo carattere
		void PrintChar(short x, short y, unsigned char c);
		// Stampa del testo in formato ASCII nelle coordinate specificate
		void PrintText(short x, short y, const char* format, ...);
		// Stampa del testo in formato ASCII nelle coordinate specificate
		void PrintTextAligned(short x, short y, const char* format, ...);
		// Cambia il colore del font
		void TextColor(TEXTCOLOR);
		
		void SolidPalette(bool);
		void DrawTile(short x, short y, short tile, byte palette, byte flipXY);
		void DrawChunk(short x, short y, short chunk);
		void DrawChunkCollision(short x, short y, short chunk);
		void DrawLevel(short x, short y, short screenWidth, short screenHeight, short layer);
		void DrawLevel256(short x, short y, short screenWidth, short screenHeight, short layer);

		// Funzioni virtuali
		void Draw();
		virtual short getWheelY();
		virtual void InputWheel(short wheely);
		virtual bool InputKeyb(int key, bool up);
		virtual bool InputKeyb(int key);
		virtual bool InputChar(int character);
		virtual bool InputMouse(short x, short y, int button);
	};
}