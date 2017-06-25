#include "ChunkEditor.h"
#include "MainEditor.h"
#include "ChunkSelector.h"
#include "ChunkTileSelector.h"
#include "TileSelector.h"
#include "PaletteSelector.h"

#define E_CHUNKED_FILEINFO_X 0
#define E_CHUNKED_FILEINFO_Y 2
#define E_CHUNKED_SELECTOR_X 0
#define E_CHUNKED_SELECTOR_Y 6
#define E_CHUNKED_SELECTOR_WIDTH (getEditorWidth() - 128 - 32 - E_CHUNKED_SELECTOR_X)
#define E_CHUNKED_SELECTOR_HEIGHT (getEditorHeight() - E_CHUNKED_SELECTOR_Y * 8)

void Editor::ChunkEditor::eChunkSelected(ChunkSelector* chunkSelector, Control *parent, int value)
{
	ChunkEditor* p_chunkEditor = ((ChunkEditor*)parent);
	p_chunkEditor->m_chunkTileSelector->setChunkIndex(value);
}
void Editor::ChunkEditor::eChunkTileSelected(ChunkTileSelector* chunkTileSelector, Control *parent, int value)
{
	ChunkEditor* p_chunkEditor = ((ChunkEditor*)parent);
	p_chunkEditor->m_tileSelected = value;
	p_chunkEditor->m_tileSelector->SetTileSelected(p_chunkEditor->GetTileEntry().Tile);
}
void Editor::ChunkEditor::eTileSelected(TileSelector* chunkTileSelector, Control *parent, int value)
{
	ChunkEditor* p_chunkEditor = ((ChunkEditor*)parent);
	XeEngine::TileEntry TileEntry = p_chunkEditor->GetTileEntry();
	TileEntry.Tile = value;
	p_chunkEditor->SetTileEntry(TileEntry);
}

Editor::ChunkEditor::ChunkEditor(MainEditor *e) : Control(e)
{
	m_name = "Chunk Editor";
	selectedChunk = 0;
	m_tileSelected = 0;
	m_editMode = -1;
	m_chunkSelector = new ChunkSelector(e, this, 20 * font->GetWidth(), 5 * font->GetHeight(), 0, 0);
	m_chunkSelector->eChunkSelected = eChunkSelected;
	m_chunkTileSelector = new ChunkTileSelector(e, this, (20 * font->GetWidth() - XeEngine::chunkSizeAbsolute) / 2, 5 * font->GetHeight());
	m_chunkTileSelector->eChunkTileSelected = eChunkTileSelected;
	m_tileSelector = new TileSelector(e, this, m_chunkSelector->getPosition(), 1);
	m_tileSelector->Visible(false);
	m_tileSelector->eTileSelected = eTileSelected;
	m_paletteSelector = new PaletteSelector(e, this, m_chunkSelector->getPosition().x,  m_chunkSelector->getPosition().y, 256);
	m_paletteSelector->Visible(false);
	AddControl(m_chunkSelector);
	AddControl(m_chunkTileSelector);
	AddControl(m_tileSelector);
	AddControl(m_paletteSelector);
	chunkPreviewDetailsPosition = Position(1, (m_chunkTileSelector->getPosition().y + XeEngine::chunkSizeAbsolute + font->GetHeight() + XeEngine::tileSize * 3) / font->GetHeight());
}

XeEngine::TileEntry Editor::ChunkEditor::GetTileEntry()
{
	return getLevel()->chunk[m_chunkTileSelector->getChunkIndex()][m_tileSelected];
}
void Editor::ChunkEditor::SetTileEntry(XeEngine::TileEntry TileEntry)
{
	m_chunkTileSelector->WriteTileEntry(TileEntry);
}
void Editor::ChunkEditor::_Draw()
{
	m_chunkSelector->setSize(Size(E_CHUNKED_SELECTOR_WIDTH, E_CHUNKED_SELECTOR_HEIGHT));
	m_chunkSelector->setChunkSelected(m_chunkTileSelector->getChunkIndex());
	XeEngine::TileEntry TileEntry = GetTileEntry();
	u8 colPath1 = getLevel()->collisionIndex[0][TileEntry.Tile % XeEngine::tileCount];
	u8 colPath2 = getLevel()->collisionIndex[1][TileEntry.Tile % XeEngine::tileCount];

	XeEngine::String chunkPath;
	getLevel()->BuildPath(chunkPath, getLevel()->GetCurrentAct(), XeEngine::STAGEFILE_BLK);

	PrintTextAligned(E_CHUNKED_FILEINFO_X, E_CHUNKED_FILEINFO_Y + 0, "File: %s", chunkPath.ToChar());
	if (m_chunkSelector->getFocus())
		PrintTextAligned(E_CHUNKED_FILEINFO_X, E_CHUNKED_FILEINFO_Y + 1, "Chunk %04X on %04X", m_chunkSelector->getChunkSelected(), m_chunkSelector->getChunkMouse());
	else
		PrintTextAligned(E_CHUNKED_FILEINFO_X, E_CHUNKED_FILEINFO_Y + 1, "Chunk %04X", m_chunkSelector->getChunkSelected());

	XeEngine::Point pImage = XeEngine::Point((float)(chunkPreviewDetailsPosition.x * font->GetWidth()), (float)((chunkPreviewDetailsPosition.y * font->GetHeight() - XeEngine::tileSize * 3)));
	//XeEngine::Video::Get()->Scale(2.0f, 2.0f, 1.0f);
	DrawTile(((short)pImage.x + 0) / 2, (short)pImage.y / 2, TileEntry.Tile, TileEntry.palette, 0);
	DrawTile(((short)pImage.x + 48) / 2, (short)pImage.y / 2, TileEntry.Tile, TileEntry.palette, 0);
	DrawTile(((short)pImage.x + 96) / 2, (short)pImage.y / 2, TileEntry.Tile, TileEntry.palette, 0);
	//XeEngine::Video::Get()->Scale(0.5f, 0.5f, 1.0f);

	//eff->Push();
	//eff->SetFadeFactor(0.5f);
	e->DrawCollision(colPath1, 0, XeEngine::Point(pImage.x + 48, pImage.y), XeEngine::Size(32.0f, 32.0f));
	e->DrawCollision(colPath2, 0, XeEngine::Point(pImage.x + 96, pImage.y), XeEngine::Size(32.0f, 32.0f));
	//eff->Pop();

	if (m_editMode == 0) TextColor(TEXTCOLOR_YELLOW); else TextColor(TEXTCOLOR_WHITE);
	PrintTextAligned(chunkPreviewDetailsPosition.x, chunkPreviewDetailsPosition.y + 0, "%04X Tile index", TileEntry.Tile);
	if (m_editMode == 1) TextColor(TEXTCOLOR_YELLOW); else TextColor(TEXTCOLOR_WHITE);
	PrintTextAligned(chunkPreviewDetailsPosition.x, chunkPreviewDetailsPosition.y + 1, "%02X Palette index", TileEntry.palette);
	if (m_editMode == 2) TextColor(TEXTCOLOR_YELLOW); else TextColor(TEXTCOLOR_WHITE);
	PrintTextAligned(chunkPreviewDetailsPosition.x, chunkPreviewDetailsPosition.y + 2, "%02X %02X Hitbox", colPath1, colPath2);
	TextColor(TEXTCOLOR_WHITE);
	PrintTextAligned(chunkPreviewDetailsPosition.x, chunkPreviewDetailsPosition.y + 3, "%c Flip", TileEntry.flip ? 0xE1 : 0xE0);
	PrintTextAligned(chunkPreviewDetailsPosition.x, chunkPreviewDetailsPosition.y + 4, "%c Mirror", TileEntry.mirror ? 0xE1 : 0xE0);
	PrintTextAligned(chunkPreviewDetailsPosition.x, chunkPreviewDetailsPosition.y + 5, "%c Depth level", TileEntry.depth ? 0xE1 : 0xE0);
}
bool Editor::ChunkEditor::_InputKeyb(int key)
{
	return false;
}
bool Editor::ChunkEditor::_InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
{
	switch (button)
	{
	case XeEngine::MouseInput_LEFT:
		if (x >= chunkPreviewDetailsPosition.x && x < m_chunkSelector->getPosition().x)
		{
			XeEngine::TileEntry* TileEntry = &getLevel()->chunk[m_chunkTileSelector->getChunkIndex()][m_chunkTileSelector->getTileSelected()];

			int editMode = y / font->GetHeight() - chunkPreviewDetailsPosition.y;
			if (editMode == m_editMode)
			{
				m_editMode = -1;
				m_chunkSelector->Visible(true);
				m_tileSelector->Visible(false);
				m_paletteSelector->Visible(false);
				return true;
			}

			switch(editMode)
			{
			case 0:
				m_chunkSelector->Visible(false);
				m_tileSelector->Visible(true);
				m_paletteSelector->Visible(false);
				m_editMode = 0;
				m_tileSelector->SetTileSelected(GetTileEntry().Tile);
				return true;
			case 1:
				m_chunkSelector->Visible(false);
				m_tileSelector->Visible(false);
				m_paletteSelector->Visible(true);
				m_editMode = 1;
				return true;
			case 2:
				m_chunkSelector->Visible(false);
				m_tileSelector->Visible(false);
				m_paletteSelector->Visible(false);
				m_editMode = 2;
				return true;
			case 3:
				TileEntry->flip ^= 1;
				return true;
			case 4:
				TileEntry->mirror ^= 1;
				return true;
			case 5:
				TileEntry->depth ^= 1;
				return true;
			}
		}
		break;
	}
	return false;
}