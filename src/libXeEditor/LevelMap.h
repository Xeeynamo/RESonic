#pragma once
#include "Control.h"

class MAP;
struct LayerProperties;
namespace Editor
{
	class EXPORT LevelMap : public Control
	{
	private:
		struct LevelMapUndo 
		{
			u16 x, y;
			u16 chunk;
			u8 layer;
			u8 room;
		};
		XeEngine::Stack<LevelMapUndo> undo;

		byte m_selectedLayer;
		short keyX, keyY;
		short mapwidth, mapheight;
		short *mapblock;

		bool editor;
		short chunkSelected;
		short chunkX, chunkY;

		LayerProperties *layerProp;
		Position mapposition;
		bool mousedrag;
		Position mousedragpos;

		virtual void _Draw();
		virtual bool _InputKeyb(int key, bool up);
		virtual bool _InputKeyb(int key);
		virtual bool _InputMouse(u16 x, u16 y, XeEngine::MouseInput button);
	protected:
		XeEngine::Map *map;
	public:
		LevelMap(MainEditor*, Control*);

		bool getEditorEnabled();
		void setEditorEnabled(bool);
		short getEditorChunk();
		void setEditorChunk(short);
		short getMouseChunk();
		void setMouseChunk(short);
		Position getMapPosition();
		void setMapPosition(Position);

		virtual Size getSize();


		//! \brief Get the current selected layer
		//! \return The layer index
		u8 GetCurrentLayer();
		//! \brief Get the current selected layer
		//! \return The layer index
		void SetCurrentLayer(u8);
		//! \brief Get the room properties
		XeEngine::MapRoom* GetMapRoom();
		//! \brief Set the current room
		//! \warning This will load a new room inside the game
		void SetMapRoom(u8 index);
		//! \brief Get the layer properties
		XeEngine::MapLayer* GetMapLayer();
		//! \brief Set the current layer
		void SetMapLayer(u8 index);
	};
}