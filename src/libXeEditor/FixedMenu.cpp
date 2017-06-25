#include "FixedMenu.h"
#include "MainEditor.h"

Editor::FixedMenu::FixedMenu(MainEditor* e, Control* c, short x, short y, short width) : Control(e, c, Position(x, y), Size(width, 0))
{
	menuwidth = 0;
	menuindex = 0;
	eMenuSelection = nullptr;
	SetBackgroundColor(XeEngine::ColorARGB((u8)0x00, (u8)0x00, (u8)0x00, (u8)0x00).ToColor32());
}
Editor::FixedMenu::~FixedMenu()
{
	DeleteMenu(&menu);
}

Editor::FixedMenuItem* Editor::FixedMenu::GetMenuItem(short id, XeEngine::List<FixedMenuItem*> *list)
{
	if (list == NULL) list = &menu;
	FixedMenuItem *item;
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
void Editor::FixedMenu::DeleteMenu(XeEngine::List<FixedMenuItem*>* m)
{
	if (m == NULL) return;
	FixedMenuItem *item;
	m->MoveHead();
	while(m->Next(item))
	{
		DeleteMenu(item->submenu);
		delete item;
	}
	if (m != &menu) delete m;
}
void Editor::FixedMenu::AddItem(char *name, short id, short supermenu)
{
	if (name == NULL || id == 0) return;
	XeEngine::List<FixedMenuItem*> *dstmenu = &menu;;
	FixedMenuItem *superitem = 0;
	if (supermenu)
	{
		superitem = GetMenuItem(supermenu);
		if (superitem == 0) return;
		if (superitem->parent == 0)
		{
			superitem->parent = new XeEngine::List<FixedMenuItem*>;
		}
		dstmenu = superitem->parent;
	}
	Size size = getSize();
	FixedMenuItem *item = new FixedMenuItem;
	int strsize = XeEngine::System::StringLength(name);
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
void Editor::FixedMenu::DeleteItem(short id)
{
	FixedMenuItem *item = GetMenuItem(id);
	if (item == NULL) return;
	DeleteMenu(item->submenu);
	item->parent->Remove(item);

	Size size = getSize();
	size.height -= font->GetHeight();
	setSize(size);
	delete item;
}
void Editor::FixedMenu::DeleteAllItems()
{
	DeleteMenu(&menu);
}
bool Editor::FixedMenu::isEnabledItem(short id)
{
	FixedMenuItem *item = GetMenuItem(id);
	if (item == NULL) return false;
	return item->enabled == 1;
}
void Editor::FixedMenu::EnableItem(short id, bool enable)
{
	FixedMenuItem *item = GetMenuItem(id);
	if (item == NULL) return;
	item->enabled = enable;
}
void Editor::FixedMenu::SetBackgroundColor(XeEngine::Color32 color)
{
	backColor = color;
	backDarkColor = ((color&0xFF)>>1) | ((color&0xFF00)>>1) | ((color&0xFF0000)>>1) | (color & 0xFF000000);
	borderColor = ((color&0xFF)>>2) | ((color&0xFF00)>>2) | ((color&0xFF0000)>>2) | backDarkColor;
}
void Editor::FixedMenu::DrawMenu(XeEngine::List<FixedMenuItem*>* menu, short x, short y)
{
	u8 fontWidth = font->GetWidth();
	u8 fontHeight = font->GetHeight();

	x = position.x + x * fontWidth;
	y = position.y + y * fontHeight;

	XeEngine::Shape::SetColorArray(backColor, backColor, backDarkColor, backColor);
	XeEngine::Shape::FillRect(float(x), float(y), 1.0f, (float)getSize().width, (float)(menu->Count() * fontHeight));
	XeEngine::Shape::SetColorArray(borderColor, borderColor, borderColor, borderColor);
	XeEngine::Shape::FillRect(float(position.x), float(position.y + menuindex * fontHeight), 1.0f, (float)getSize().width, (float)fontHeight);

	FixedMenuItem *item;
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

void Editor::FixedMenu::_Draw()
{
	DrawMenu(&this->menu);
}
bool Editor::FixedMenu::_InputKeyb(int button)
{
	switch(button)
	{
	case VK_UP:
		menuindex--;
		if (menuindex < 0)
			menuindex = size.height / font->GetHeight() - 1;
		return true;
	case VK_DOWN:
		menuindex++;
		if (menuindex >= size.height / font->GetHeight())
			menuindex = 0;
		return true;
	case VK_RETURN:
		FixedMenuItem *item = nullptr;
		menu.MoveHead();
		for(int i=0; i <= menuindex; i++)
		{
			menu.Next(item);
		}
		if (item != nullptr)
		{
			if (eMenuSelection) eMenuSelection(this, parent, item->id);
		}
		return true;
	}
	return false;
}
bool Editor::FixedMenu::_InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
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
			FixedMenuItem *item = nullptr;
			menu.MoveHead();
			for(int i=0; i <= menuindex; i++)
			{
				menu.Next(item);
			}
			if (item != nullptr)
			{
				if (eMenuSelection) eMenuSelection(this, parent, item->id);
			}
		}
		break;
	}
	return true;
}