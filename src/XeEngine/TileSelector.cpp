#include "TileSelector.h"
#include "MainEditor.h"

Editor::TileSelector::TileSelector(MainEditor *e, Control *c) : Control(e, c)
{

}

void Editor::TileSelector::_Draw()
{
	getLevel()->texture.Draw();
	return;
}
bool Editor::TileSelector::_InputKeyb(int key)
{
	return false;
}
bool Editor::TileSelector::_InputMouse(short x, short y, short button)
{
	return false;
}