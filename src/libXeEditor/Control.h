#pragma once
#include <windows.h>
#include "XeControl.h"
#include "..\libXeEngine\XeBase.h"
#include "..\libXeEngine\List.h"
#include "..\libXeEngine\Stack.h"
#include "..\libXeEngine\Font.h"
#include "..\libXeEngine\Math.h"
#include "..\libXeEngine\Video.h"
#include "..\libXeEngine\Input.h"
#include "..\libXeEngine\XInput.h"
#include "..\libXeEngine\Color.h"
#include "..\libXeEngine\Texture.h"
#include "..\libXeEngine\Game.h"
#include "..\libXeEngine\Level.h"
#include "..\libXeEngine\Font.h"
#include "..\libXeEngine\Geometry.h"
#include "..\libXeEngine\Entity.h"
#include "..\libXeEngine\File.h"
#include "..\libXeEngine\Shape.h"
#include "..\libXeEngine\Graphic.h"

namespace XeEngine
{
	class Level;
	class Game;
}

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

	class MainEditor;
	class EXPORT Control
	{
	private:
	protected:
		char *m_name;

		MainEditor *e;
		Control *parent;
		XeEngine::List<Control*> controlList;

		bool enabled;
		bool visible;
		bool m_highPriority;
		bool focus;
		Position position;
		Size size;

		bool collisionview;
		XeEngine::Font *font;

		bool fadeOnLoseFocus;
		float fadefactor;

		virtual void _Draw() = 0;
		virtual bool _InputKeyb(int key, bool up){ return false; }
		virtual bool _InputKeyb(int key){ return false; };
		virtual bool _InputChar(int character){ return false; };
		virtual bool _InputMouse(u16 x, u16 y, XeEngine::MouseInput button){ return false; };
	public:
		//! \brief Create a control
		//! \param A pointer to the master control
		//! \param A pointer to the parent control
		//! \param Control's position
		//! \param Control's size
		Control(MainEditor*, Control *parent = 0, Position = Position(0, 0), Size = Size(0, 0));

		//! \brief Destroy a control
		virtual ~Control();

		//! \brief Check if the control is enabled
		//! \details Both visibility and enable need to be true to get a positive value
		bool Enable() const { return enabled & visible; }

		//! \brief Enable or disable a control
		//! \param TRUE if the control is enabled, FALSE if it is not
		void Enable(bool enabled) { this->enabled = enabled; }

		//! \brief Check if the control is visible
		bool Visible() const { return visible; }

		//! \brief Make a control visible or not
		//! \param TRUE if the control is visible, FALSE if it is not
		void Visible(bool visible) { this->visible = visible; }

		//! \brief Check if the Control has a high priority
		//! \detail A control with high priority means that it can handle every input, also if it hasn't the focus
		bool IsHighPriority() const { return m_highPriority; }

		//! \brief Set the high priority on a control
		//! \param TRUE if the control is in high priority, FALSE if it is not
		void SetHighPriority(bool highPriority) { m_highPriority = highPriority; }

		Position getPosition() { return position; }
		void setPosition(Position position) { this->position = position; }
		virtual Size getSize();
		virtual void setSize(Size size);
		virtual bool getFocus();
		virtual void setFocus(bool focus);
		virtual void setFadeOnLoseFocus(bool);
		virtual Position getMouseCoord();
		void AddControl(Control *c);

		// Funzioni strettamente legate al gioco
		virtual XeEngine::Game* getGame();
		virtual XeEngine::Level* getLevel();
		virtual short getEditorWidth();
		virtual short getEditorHeight();
		virtual char *getName();
		virtual bool getCollisionView();
		virtual void setCollisionView(bool);
		virtual XeEngine::Effect* GetControlEffect();
		virtual XeEngine::Effect* GetLevelEffect();

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
		//! \brief Change font's color
		//! \param The color to set
		virtual void TextColor(TEXTCOLOR);
		
		void SolidPalette(bool);
		void DrawTile(short x, short y, short tile, byte palette, byte flipXY);
		void DrawChunk(short x, short y, short chunk);
		void DrawChunkCollision(short x, short y, short chunk);
		void DrawLevel(short x, short y, short screenWidth, short screenHeight, XeEngine::MapLayer*);
		void DrawLevel256(short x, short y, short screenWidth, short screenHeight, short layer);

		// Funzioni virtuali
		void Draw();
		virtual short getWheelY();
		virtual void InputWheel(short wheely);
		virtual bool InputKeyb(int key, bool up);
		virtual bool InputKeyb(int key);
		virtual bool InputChar(int character);
		virtual bool InputMouse(u16 x, u16 y, XeEngine::MouseInput button);
	};
}