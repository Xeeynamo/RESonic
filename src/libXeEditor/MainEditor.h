#pragma once
#include "Control.h"

#define E_FILEINFO_X 0
#define E_FILEINFO_Y 1

namespace Editor
{
	class EXPORT MainEditor : public Control
	{
	private:
		XeEngine::ColorHSV pointerColor[4];
		short mouseX, mouseY;

		int prevkey;
		bool continuekeypress;
		int mode;
		bool doubleres;
		bool showGuide;
		bool showfps;
		float fps;
		TEXTCOLOR textColorIndex;

		bool ctrl, alt, shift;
		short wheely;

		short eWidth;
		short eHeight;

		XeEngine::Video* video;
		XeEngine::Font *debugFont;
		XeEngine::Texture texCollision;
		XeEngine::Texture texFont;
		XeEngine::Font fontEditor;
		XeEngine::XInput* input;
		XeEngine::Color32* lutEditor;
		XeEngine::Texture collisionTexture;

		//! \brief Holds the current fps
		u32 frame;
		u32 prevtime;


		virtual void _Draw();
		virtual void CalculateFPS();
	protected:
		XeEngine::Game* g;
		XeEngine::Level* l;
		Control *controls[11];
	public:
		MainEditor(XeEngine::Game*);
		~MainEditor();

		//! \brief Initialize the editor's stuff
		void Initialize();
		//! \brief Run the editor
		//! \return Returns FALSE if the editor is turned off
		bool Run();

		//! \brief Get the control of the current editing mode
		Control *GetControlMode();
		//! \brief Get the index of the current editing mode
		int GetMode();
		//! \brief Set the index of the current editing mode
		void SetMode(int);
		//! \brief Set the render size of the editor
		void SetRenderSize(short width, short height);
		//! \brief Check if the zoom mode is enabled
		bool getDoubleView();
		//! \brief Set the zoom mode
		void setDoubleView(bool);
		//! \brief Checks if the FPS count is displayed
		bool getShowFps() const;
		//! \brief Set if the FPS count should be displayed
		void setShowFps(bool);
		//! \brief Get the FPS count
		float getFpsCount() const;
		//! \brief Get the texture collision
		XeEngine::Texture* getTextureCollision();
		//! \brief Get the LUT of the editro
		XeEngine::Color32* GetLutEditor() { return lutEditor; }

		// Funzioni proprie
		void RefreshPalette();
		void UpdateTiles();
		void UpdateCollisions();
		void ShowGuide();

		// Funzioni virtuali dell'editor principali
		virtual XeEngine::Game *getGame();
		virtual XeEngine::Level *getLevel();
		virtual short getEditorWidth();
		virtual short getEditorHeight();
		virtual Position getMouseCoord();
		bool isCtrlPressed();
		bool isAltPressed();
		bool isShiftPressed();
		//! \brief Change font's color
		//! \param The color to set
		virtual void TextColor(TEXTCOLOR);

		void CollisionFloor(u8* memory, u8 fill);
		void CollisionWall(u8* memory, u8 fill);
		void Floor2Image(u8* memory, u8 index, u8 fill);
		void Wall2Image(u8* memory, u8 index, u8 fill);
		XeEngine::Texture* GetCollisionTexture();
		void DrawCollision(u8 index, u8 verse, XeEngine::Point, XeEngine::Size = XeEngine::Size(16.0f, 16.0f));

		// Funzioni principali di controllo
		virtual short getWheelY();
		virtual void InputWheel(short wheely);
		virtual bool _InputKeyb(XeEngine::InputButton key, bool up);
		virtual bool _InputKeyb(XeEngine::InputButton key);
		virtual bool _InputChar(XeEngine::InputButton character);
		virtual bool _InputMouse(u16 x, u16 y, XeEngine::MouseInput button);
	};
}