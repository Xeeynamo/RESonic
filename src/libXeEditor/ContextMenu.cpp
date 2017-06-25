#include "ContextMenu.h"
#include "MainEditor.h"

Editor::ContextMenu::ContextMenu(MainEditor* e, Control* c) : Control(e, c)
{
	menuwidth = 0;
	menuindex = 0;
	SetBackgroundColor(XeEngine::ColorARGB((u8)0x00, (u8)0x60, (u8)0xA0).ToColor32());
	Visible(false);
	Enable(false);

	eMenuClick = 0;
}
Editor::ContextMenu::~ContextMenu()
{
	DeleteMenu(&menu);
}

Editor::ContextMenuItem* Editor::ContextMenu::GetMenuItem(short id, XeEngine::List<ContextMenuItem*> *list)
{
	if (list == NULL) list = &menu;
	ContextMenuItem *item;
	list->MoveHead();
	while(list->Next(item))
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
void Editor::ContextMenu::DeleteMenu(XeEngine::List<ContextMenuItem*>* m)
{
	if (m == NULL) return;
	ContextMenuItem *item;
	m->MoveHead();
	while(m->Next(item))
	{
		DeleteMenu(item->submenu);
		delete item;
	}
	if (m != &menu) delete m;
}
void Editor::ContextMenu::AddItem(char *name, short id, short supermenu)
{
	if (name == NULL || id == 0) return;
	XeEngine::List<ContextMenuItem*> *dstmenu = &menu;;
	ContextMenuItem *superitem = 0;
	if (supermenu)
	{
		superitem = GetMenuItem(supermenu);
		if (superitem == 0) return;
		if (superitem->parent == 0)
		{
			superitem->parent = new XeEngine::List<ContextMenuItem*>;
		}
		dstmenu = superitem->parent;
	}
	Size size = getSize();
	ContextMenuItem *item = new ContextMenuItem;
	int strsize = (int)XeEngine::System::StringLength(name);
	if (menuwidth < strsize) menuwidth = strsize;
	item->name = new char[strsize + 1];
	item->enabled = true;
	item->submenu = NULL;
	item->dummy = 0;
	item->id = id;
	XeEngine::MemoryCopy(item->name, name, strsize + 1);
	dstmenu->Add(item);

	size.width = strsize *= font->GetWidth();
	size.height += font->GetHeight();
	setSize(size);
	return;
}
void Editor::ContextMenu::DeleteItem(short id)
{
	ContextMenuItem *item = GetMenuItem(id);
	if (item == NULL) return;
	DeleteMenu(item->submenu);
	item->parent->Remove(item);

	Size size = getSize();
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
void Editor::ContextMenu::SetBackgroundColor(XeEngine::Color32 color)
{
	backColor = color;
	backDarkColor = ((color&0xFF)>>1) | ((color&0xFF00)>>1) | ((color&0xFF0000)>>1) | 0xFF000000;
	borderColor = ((color&0xFF)>>2) | ((color&0xFF00)>>2) | ((color&0xFF0000)>>2) | backDarkColor;
}
void Editor::ContextMenu::ShowMenu()
{
	Position menuPosition = getMouseCoord();
	if (menuPosition.x + size.width >= parent->getPosition().x + parent->getSize().width)
		menuPosition.x -= size.width;
	if (menuPosition.y + size.height >= parent->getPosition().y + parent->getSize().height)
		menuPosition.y -= size.height;
	setPosition(menuPosition);
	Visible(true);
	Enable(true);
}
void Editor::ContextMenu::DrawMenu(XeEngine::List<ContextMenuItem*>* menu, short x, short y)
{
	u8 fontWidth = font->GetWidth();
	u8 fontHeight = font->GetHeight();

	x = position.x + x * fontWidth;
	y = position.y + y * fontHeight;

	XeEngine::Shape::SetColorArray(backColor, backColor, backDarkColor, backColor);
	XeEngine::Shape::FillRect(float(x), float(y), 1.0f, (float)size.width, (float)(menu->Count() * fontHeight));
	XeEngine::Shape::SetColorArray(borderColor, borderColor, borderColor, borderColor);
	XeEngine::Shape::DrawRect(float(x-1), float(y), 1.0f, float(menuwidth * fontWidth + 1), float(menu->Count() * fontHeight + 1));
	XeEngine::Shape::FillRect(float(position.x), float(position.y + menuindex * fontHeight), 1.0f, (float)size.width, (float)fontHeight);

	ContextMenuItem *item;
	menu->MoveHead();

	for(int i=0; menu->Next(item); i++)
	{
		if (i == menuindex)
		{
			TextColor(TEXTCOLOR_YELLOW);
			PrintText(x, y + i * fontHeight, item->name);
			TextColor(TEXTCOLOR_WHITE);
		}
		else PrintText(x, y + i * fontHeight, item->name);
	}
}

void Editor::ContextMenu::_Draw()
{
	DrawMenu(&this->menu);
}
bool Editor::ContextMenu::_InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
{
	if (!Enable()) return false;

	bool mouseIn = false;
	Position pos = getMouseCoord();
	if (pos.y >= position.y && pos.y < position.y + size.height)
	{
		menuindex = (pos.y - position.y) / font->GetHeight();
		mouseIn = true;
	}

	switch(button)
	{
	case XeEngine::MouseInput_LEFT:
		if (mouseIn == true)
		{
			ContextMenuItem *item = nullptr;
			menu.MoveHead();
			for(int i=0; i <= menuindex; i++)
			{
				menu.Next(item);
			}
			if (item != nullptr)
			{
				if (eMenuClick) eMenuClick(this, parent, item->id);
			}
		}
	case XeEngine::MouseInput_RIGHT:
	case XeEngine::MouseInput_MIDDLE:
		Visible(false);
		Enable(false);
		break;
	}
	return true;

	/*Position pos = getMouseCoord();
	if (pos.y >= position.y && pos.y < position.y + size.height)
	{
		menuindex = (pos.y - position.y) / 8;

		if (button == MK_LBUTTON)
		{
			MenuItem *item = nullptr;
			menu.MoveHead();
			for(int i=0; i <= menuindex; i++)
			{
				menu.Next(item);
			}
			if (item != nullptr)
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
	return true;*/
}