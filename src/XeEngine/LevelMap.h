#pragma once
#include "Control.h"

class MAP;
struct LayerProperties;
namespace Editor
{
	class LevelMap : public Control
	{
	private:
		struct LevelMapUndo 
		{
			short chunk;
			short layer;
			short *address;
		};
		Stack<LevelMapUndo> undo;

		byte m_selectedLayer;
		short keyX, keyY;
		short mapwidth, mapheight;
		short *mapblock;

		bool editor;
		short chunkSelected;
		short chunkX, chunkY;

		LayerProperties *layerProp;
		CtrlPosition mapposition;
		bool mousedrag;
		CtrlPosition mousedragpos;

		virtual void _Draw();
		virtual bool _InputKeyb(int key, bool up);
		virtual bool _InputKeyb(int key);
		virtual bool _InputMouse(short x, short y, int button);
	protected:
		MAP *map;
	public:
		LevelMap(MainEditor*, Control*);

		bool getEditorEnabled();
		void setEditorEnabled(bool);
		short getEditorChunk();
		void setEditorChunk(short);
		short getMouseChunk();
		void setMouseChunk(short);
		MAP *getMap();
		void setMap(MAP*);
		byte getLayer();
		void setLayer(char layer);
		CtrlPosition getMapPosition();
		void setMapPosition(CtrlPosition);

		virtual CtrlSize getSize();
	};
}