#pragma once
#include "Control.h"

namespace Editor
{
	class MainEditor;

	struct ContextMenuItem
	{
		char *name;
		short id;
		unsigned char enabled;
		unsigned char dummy;
		XeEngine::List<ContextMenuItem*> *submenu;
		XeEngine::List<ContextMenuItem*> *parent;
	};

	class EXPORT ContextMenu : public Control
	{
	private:
		int menuindex;
		int menuwidth;
		XeEngine::List<ContextMenuItem*> menu;
		ContextMenuItem* GetMenuItem(short id, XeEngine::List<ContextMenuItem*> *list = 0);
		void DeleteMenu(XeEngine::List<ContextMenuItem*>*);
		void DrawMenu(XeEngine::List<ContextMenuItem*>*, short x = 0, short y = 0);
	protected:
		XeEngine::Color32 backColor, backDarkColor, borderColor;
		virtual void _Draw();
		virtual bool _InputMouse(u16 x, u16 y, XeEngine::MouseInput button);
	public:
		ContextMenu(MainEditor*, Control*);
		~ContextMenu();

		void AddItem(char *name, short id, short supermenu = 0);
		void DeleteItem(short id);
		bool isEnabledItem(short id);
		void EnableItem(short id, bool enable);
		void SetBackgroundColor(XeEngine::Color32 color);
		void ShowMenu();

		void (*eMenuClick)(ContextMenu*, Control*, short index);
	};
}