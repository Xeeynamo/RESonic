#pragma once
#include "Control.h"
#include "Game.h"
#include "XeLevel.h"
#include "XeScene.h"

#define E_FILEINFO_X 0
#define E_FILEINFO_Y 8

namespace Editor
{
	class MainEditor : public Control
	{
	private:
		XeEngine::ColorHSV pointerColor;
		short mouseX, mouseY;

		int prevkey;
		bool continuekeypress;
		int mode;
		bool doubleres;
		bool showGuide;
		bool showfps;
		short fps;
		char textColorIndex;

		bool ctrl, alt, shift;
		short wheely;

		short eWidth;
		short eHeight;
		XeScene scene;
		XeFont *debugFont;
		XeTexture texCollision;

		virtual void _Draw();
	protected:
		Game *g;
		XeLevel *l;
		Control *controls[10];
	public:
		MainEditor(Game*);
		~MainEditor();

		// Funzioni get/set
		Control *GetControlMode();
		int GetMode();
		void SetMode(int);
		bool getDoubleView();
		void setDoubleView(bool);
		bool getShowFps();
		void setShowFps(bool);
		short getFpsCount();
		XeScene *getScene();
		XeTexture *getTextureCollision();


		// Funzioni proprie
		void RefreshPalette();
		void UpdateTiles();
		void UpdateCollisions();
		void ShowGuide();

		// Funzioni virtuali dell'editor principali
		virtual Game *getGame();
		virtual XeLevel *getLevel();
		virtual short getEditorWidth();
		virtual short getEditorHeight();
		virtual CtrlPosition getMouseCoord();
		bool isCtrlPressed();
		bool isAltPressed();
		bool isShiftPressed();
		// Funzioni principali di controllo
		virtual short getWheelY();
		virtual void InputWheel(short wheely);
		virtual bool _InputKeyb(int key, bool up);
		virtual bool _InputKeyb(int key);
		virtual bool _InputChar(int character);
		virtual bool _InputMouse(short x, short y, int button);
	};
}