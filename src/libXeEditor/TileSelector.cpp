#include "TileSelector.h"
#include "MainEditor.h"

#define CHUNKSELECTED_COLOR1	0xFFFF8040
#define CHUNKSELECTED_COLOR2	0xFF4080FF

Editor::TileSelector::TileSelector(MainEditor *e, Control *c, Position pos, int zoom) : Control(e, c, pos, Size(XeEngine::tileSize * 16 * zoom, XeEngine::tileSize * 16 * zoom))
{
	m_zoom = zoom;
	m_preview = 0;
	m_depth = 0;
	eTileSelected = nullptr;
}

void Editor::TileSelector::_Draw()
{
	//video->SetClutDepth(0, XeEngine::clutCount);
	//video->SetClutIndex(0);
	getLevel()->gfxLevel.Draw(XeEngine::Point(position.x, position.y), m_depth);
	if (m_depth == m_depthIndex)
	{
		XeEngine::Shape::SetColorArray(e->GetLutEditor()[0x0F], e->GetLutEditor()[0x0E], e->GetLutEditor()[0x0D], e->GetLutEditor()[0x0C]);
		XeEngine::Shape::DrawRect(float(position.x + (m_tileIndex % XeEngine::tileSize) * XeEngine::tileSize),
			float(position.y + (m_tileIndex / XeEngine::tileSize * XeEngine::tileSize)), 1.0f, (float)XeEngine::tileSize, (float)XeEngine::tileSize);
	}
	//video->SetClutDepth(3, XeEngine::clutCount);
	//video->SetClutIndex(0);
	return;
}
bool Editor::TileSelector::_InputKeyb(int key)
{
	bool ret = false;
	switch(key & 0xFFFF)
	{
	case VK_UP:
		m_depth--;
		ret = true;
		break;
	case VK_DOWN:
		m_depth++;
		ret = true;
		break;
	case 0xE001:
		m_depth -= (key >> 16);
		ret = true;
		break;
	}
	if (m_depth < 0) m_depth = getLevel()->gfxLevel.GetHeight() / 256 - 1;
	else if (m_depth >= getLevel()->gfxLevel.GetHeight() / 256) m_depth = 0;
	return ret;
}
bool Editor::TileSelector::_InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
{
	x = x / m_zoom / XeEngine::tileSize;
	y = y / m_zoom / XeEngine::tileSize;
	m_preview = (x + (y << 4)) | (m_depth << 8);
	if (button == XeEngine::MouseInput_LEFT)
	{
		m_tileSelected = GetTilePreview();
		if (eTileSelected) eTileSelected(this, parent, m_tileSelected);
	}
	return false;
}

u16 Editor::TileSelector::GetTilePreview() const
{
	return m_preview;
}
u16 Editor::TileSelector::GetTileSelected() const
{
	return m_tileSelected;
}
void Editor::TileSelector::SetTileSelected(u16 tile)
{
	m_tileSelected = tile;
	m_depth = m_depthIndex;
}