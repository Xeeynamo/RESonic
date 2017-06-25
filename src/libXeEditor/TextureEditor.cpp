#include "TextureEditor.h"

Editor::TextureEditor::TextureEditor(MainEditor *e) : Control(e)
{
	m_name = "Texture Editor";
}

void Editor::TextureEditor::_Draw()
{
	getLevel()->gfxLevel.Draw(XeEngine::Point(4.0f, 32.0f));
}