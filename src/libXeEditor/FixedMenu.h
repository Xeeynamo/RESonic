#pragma once
#include "Control.h"

namespace Editor
{
	class MainEditor;

	struct FixedMenuItem
	{
		char *name;
		short id;
		unsigned char enabled;
		unsigned char dummy;
		XeEngine::List<FixedMenuItem*> *submenu;
		XeEngine::List<FixedMenuItem*> *parent;
	};

	class EXPORT FixedMenu : public Control
	{
	private:
		int menuindex;
		int menuwidth;
		XeEngine::List<FixedMenuItem*> menu;
		FixedMenuItem* GetMenuItem(short id, XeEngine::List<FixedMenuItem*> *list = 0);
		void DeleteMenu(XeEngine::List<FixedMenuItem*>*);
		void DrawMenu(XeEngine::List<FixedMenuItem*>*, short x = 0, short y = 0);
	protected:
		XeEngine::Color32 backColor, backDarkColor, borderColor;
		virtual void _Draw();
		virtual bool _InputKeyb(int button);
		virtual bool _InputMouse(u16 x, u16 y, XeEngine::MouseInput button);
	public:
		FixedMenu(MainEditor*, Control*, short x, short y, short width);
		~FixedMenu();

		void AddItem(char *name, short id, short supermenu = 0);
		void DeleteItem(short id);
		void DeleteAllItems();
		bool isEnabledItem(short id);
		void EnableItem(short id, bool enable);
		void SetBackgroundColor(XeEngine::Color32 color);
		void ShowMenu();

		void (*eMenuSelection)(FixedMenu*, Control*, short index);
	};
}