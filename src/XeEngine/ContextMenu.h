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
		List<ContextMenuItem*> *submenu;
		List<ContextMenuItem*> *parent;
	};

	class ContextMenu : public Control
	{
	private:
		int menuindex;
		int menuwidth;
		List<ContextMenuItem*> menu;
		ContextMenuItem* GetMenuItem(short id, List<ContextMenuItem*> *list = 0);
		void DeleteMenu(List<ContextMenuItem*>*);
		void DrawMenu(List<ContextMenuItem*>*, short x = 0, short y = 0);
	protected:
		Color backColor, backDarkColor, borderColor;
		virtual void _Draw();
		virtual bool _InputMouse(short x, short y, int button);
	public:
		ContextMenu(MainEditor*, Control*);
		~ContextMenu();

		void AddItem(char *name, short id, short supermenu = 0);
		void DeleteItem(short id);
		bool isEnabledItem(short id);
		void EnableItem(short id, bool enable);
		void SetBackgroundColor(Color color);
		void ShowMenu();

		void (*eMenuClick)(ContextMenu*, Control*, short index);
	};
}