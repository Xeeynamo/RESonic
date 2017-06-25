#include "ContextMenu.h"
#include "MainEditor.h"

Editor::ContextMenu::ContextMenu(MainEditor* e, Control* c) : Control(e, c)
{
	menuwidth = 0;
	menuindex = 0;
	SetBackgroundColor(MAKERGB(0x00, 0x60, 0xA0));
	Visible(false);
	Enable(false);

	eMenuClick = 0;
}
Editor::ContextMenu::~ContextMenu()
{
	DeleteMenu(&menu);
}

Editor::ContextMenuItem* Editor::ContextMenu::GetMenuItem(short id, List<ContextMenuItem*> *list)
{
	if (list == NULL) list = &menu;
	ContextMenuItem *item;
	list->First();
	while(list->Next(&item))
	{
		if (item->id == id)
			return item;
		if (item->submenu)
		{
			if (item = GetMenuItem(id, item->submenu))
				return item;
		}
	}
	return NULL;
}
void Editor::ContextMenu::DeleteMenu(List<ContextMenuItem*>* m)
{
	if (m == NULL) return;
	ContextMenuItem *item;
	m->First();
	while(m->Next(&item))
	{
		DeleteMenu(item->submenu);
		delete item;
	}
	if (m != &menu) delete m;
}
void Editor::ContextMenu::AddItem(char *name, short id, short supermenu)
{
	if (name == NULL || id == 0) return;
	List<ContextMenuItem*> *dstmenu = &menu;;
	ContextMenuItem *superitem = 0;
	if (supermenu)
	{
		superitem = GetMenuItem(supermenu);
		if (superitem == 0) return;
		if (superitem->parent == 0)
		{
			superitem->parent = new List<ContextMenuItem*>;
		}
		dstmenu = superitem->parent;
	}
	CtrlSize size = getSize();
	ContextMenuItem *item = new ContextMenuItem;
	int strsize = strlen(name);
	if (menuwidth < strsize) menuwidth = strsize;
	item->name = new char[strsize + 1];
	item->enabled = true;
	item->submenu = NULL;
	item->dummy = 0;
	item->id = id;
	strcpy_s(item->name, strsize + 1, name);
	dstmenu->Add(item);

	size.width = strsize *= 8;
	size.height += 8;
	setSize(size);
	return;
}
void Editor::ContextMenu::DeleteItem(short id)
{
	ContextMenuItem *item = GetMenuItem(id);
	if (item == NULL) return;
	DeleteMenu(item->submenu);
	item->parent->Remove(item);

	CtrlSize size = getSize();
	size.height -= 8;
	setSize(size);
	delete item;
}
bool Editor::ContextMenu::isEnabledItem(short id)
{
	ContextMenuItem *item = GetMenuItem(id);
	if (item == NULL) return false;
	return item->enabled == 1;
}
void Editor::ContextMenu::EnableItem(short id, bool enable)
{
	ContextMenuItem *item = GetMenuItem(id);
	if (item == NULL) return;
	item->enabled = enable;
}
void Editor::ContextMenu::SetBackgroundColor(Color color)
{
	backColor = color;
	backDarkColor = ((color&0xFF)>>1) | ((color&0xFF00)>>1) | ((color&0xFF0000)>>1) | 0xFF000000;
	borderColor = ((color&0xFF)>>2) | ((color&0xFF00)>>2) | ((color&0xFF0000)>>2) | backDarkColor;
}
void Editor::ContextMenu::ShowMenu()
{
	CtrlPosition pos;
	pos.x = getMouseCoord().x;
	pos.y = getMouseCoord().y;
	setPosition(pos);
	Visible(true);
	Enable(true);
}
void Editor::ContextMenu::DrawMenu(List<ContextMenuItem*>* menu, short x, short y)
{
	x = position.x + x*8;
	y = position.y + y*8;

	XeEffect::SetProperties(0);
	XeShape::SetColorArray(backColor, backColor, backDarkColor, backColor);
	XeShape::FillRect(x, y, 1.0f, getSize().width, menu->Count()*8);
	XeShape::SetColorArray(borderColor, borderColor, borderColor, borderColor);
	XeShape::DrawRect(x-1, y, 1.0f, menuwidth*8+1, menu->Count()*8+1);
	XeShape::FillRect(position.x, position.y + menuindex*8, 1.0f, getSize().width, 8);

	XeEffect::SetProperties(1);
	XeEffect::SetClutDepth(0, CLUT_COUNT);
	ContextMenuItem *item;
	menu->First();

	TextColor(TEXTCOLOR_WHITE);
	for(int i=0; menu->Next(&item); i++)
	{
		if (i == menuindex)
		{
			TextColor(TEXTCOLOR_YELLOW);
			PrintText(x, y + i*8, item->name);
			TextColor(TEXTCOLOR_WHITE);
		}
		else PrintText(x, y + i*8, item->name);
	}
}

void Editor::ContextMenu::_Draw()
{
	DrawMenu(&this->menu);
}
bool Editor::ContextMenu::_InputMouse(short, short, int button)
{
	if (!Enable()) return false;

	CtrlPosition pos = getMouseCoord();
	if (pos.y >= position.y && pos.y < position.y + size.height)
	{
		menuindex = (pos.y - position.y) / 8;

		if (button == MK_LBUTTON)
		{
			ContextMenuItem *item = NULL;
			menu.First();
			for(int i=0; i<=menuindex; i++)
			{
				menu.Next(&item);
			}
			if (item != NULL)
			{
				if (eMenuClick) eMenuClick(this, parent, item->id);
			}
			Visible(false);
			Enable(false);
		}
	}
	else if (button == MK_LBUTTON)
	{
		Visible(false);
		Enable(false);
	}
	return true;
}