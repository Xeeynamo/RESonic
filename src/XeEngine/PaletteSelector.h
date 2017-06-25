#pragma once
#include "MainEditor.h"

namespace Editor
{
	class PaletteSelector : public Control
	{
	private:
		short zoom;
		float zoomf;

		byte colorIndex;
		byte lutIndex;
		byte depthIndex;

		byte real_colorIndex;
	protected:
		virtual void _Draw();
		virtual bool _InputKeyb(int key);
		virtual bool _InputMouse(short x, short y, int button);
	public:
		PaletteSelector(MainEditor*, Control*, short x, short y, short size);
		// Funzioni proprie
		Color getColor();
		void setColor(Color);
		byte getColorIndex();
		void setColorIndex(byte index);
		byte getLutIndex();
		void setLutIndex(byte index);
		byte getDepthIndex();
		void setDepthIndex(byte index);
		// Funzioni derivate
		virtual void setSize(CtrlSize size);
		virtual void setFocus(bool focus);
	};
}