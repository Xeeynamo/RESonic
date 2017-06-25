#pragma once
#include "Control.h"

namespace Editor
{
	class ChunkSelector;
	class ChunkTileSelector;
	class TileSelector;
	class PaletteSelector;
	class MainEditor;
	class EXPORT ChunkEditor : public Control
	{
		static void eChunkSelected(ChunkSelector*, Control*, int);
		static void eChunkTileSelected(ChunkTileSelector*, Control*, int);
		static void eTileSelected(TileSelector*, Control*, int);
	private:
		Position chunkPreviewDetailsPosition;
		ChunkSelector *m_chunkSelector;
		ChunkTileSelector *m_chunkTileSelector;
		TileSelector *m_tileSelector;
		PaletteSelector *m_paletteSelector;
		int selectedChunk;
		u8 m_tileSelected;
		int m_editMode;

		virtual void _Draw();
		virtual bool _InputKeyb(int key);
		virtual bool _InputMouse(u16 x, u16 y, XeEngine::MouseInput button);
	protected:
		XeEngine::TileEntry GetTileEntry();
		void SetTileEntry(XeEngine::TileEntry);
	public:
		ChunkEditor(MainEditor*);
	};
}