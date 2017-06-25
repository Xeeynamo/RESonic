#pragma once
#include "Control.h"

namespace Editor
{
	class EXPORT TileSelector : public Control
	{
	private:
		int m_zoom;
		u16 m_preview;
		s16 m_depth;
		union
		{
			u16 m_tileSelected;
			struct 
			{
				u8 m_tileIndex;
				u8 m_depthIndex;
			};
		};
	public:
		TileSelector(MainEditor*, Control*, Position, int zoom);

		virtual void _Draw();
		virtual bool _InputKeyb(int key);
		virtual bool _InputMouse(u16 x, u16 y, XeEngine::MouseInput button);
		ushort GetTileSelected();

		u16 GetTilePreview() const;
		u16 GetTileSelected() const;
		void SetTileSelected(u16);

		void (*eTileSelected)(TileSelector*, Control*, int value);
	};
}