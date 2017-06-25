#include "ChunkEditor.h"
#include "MainEditor.h"
#include "ChunkSelector.h"

#define E_CHUNKED_FILEINFO_X 0
#define E_CHUNKED_FILEINFO_Y 16
#define E_CHUNKED_SELECTOR_X 0
#define E_CHUNKED_SELECTOR_Y 48
#define E_CHUNKED_SELECTOR_WIDTH (getEditorWidth() - 128 - 32 - E_CHUNKED_SELECTOR_X)
#define E_CHUNKED_SELECTOR_HEIGHT (getEditorHeight() - E_CHUNKED_SELECTOR_Y)

Editor::ChunkEditor::ChunkEditor(MainEditor *e) : Control(e)
{
	selectedChunk = 0;
	m_chunkSelector = new ChunkSelector(e, this, 0, 48, 0, 0);
	AddControl(m_chunkSelector);
}

void Editor::ChunkEditor::_Draw()
{
	CtrlSize size;
	size.width = E_CHUNKED_SELECTOR_WIDTH;
	size.height = E_CHUNKED_SELECTOR_HEIGHT;
	m_chunkSelector->setSize(size);

	PrintText(E_CHUNKED_FILEINFO_X, E_CHUNKED_FILEINFO_Y, "File: %s", getLevel()->MakePath(getLevel()->currentAct, STAGEFILE_BLK));
	PrintText(E_CHUNKED_FILEINFO_X, E_CHUNKED_FILEINFO_Y+16, "Chunk %04X on %04X", m_chunkSelector->getChunkSelected(), m_chunkSelector->getChunkMouse());



	XeEffect::SetClutDepth(1, CLUT_COUNT);
	DrawChunk(E_CHUNKED_SELECTOR_WIDTH + 16, E_CHUNKED_SELECTOR_Y, m_chunkSelector->getChunkSelected());
}
bool Editor::ChunkEditor::_InputKeyb(int key)
{
	return false;
}
bool Editor::ChunkEditor::_InputMouse(short x, short y, int button)
{
	return false;
}