#pragma once
#include "MainEditor.h"

namespace Editor
{
	class XeEngine::Texture;
	class EXPORT PaletteSelector : public Control
	{
	private:
		XeEngine::Texture* texPaletteView;

		short zoom;
		float zoomf;

		byte colorIndex;
		byte lutIndex;
		byte depthIndex;

		byte real_colorIndex;
	protected:
		virtual void _Draw();
		virtual bool _InputKeyb(int key);
		virtual bool _InputMouse(u16 x, u16 y, XeEngine::MouseInput button);
	public:
		PaletteSelector(MainEditor*, Control*, short x, short y, short size);
		~PaletteSelector();
		// Funzioni proprie
		XeEngine::Color32 getColor();
		void setColor(XeEngine::Color32);
		byte getColorIndex() const;
		void setColorIndex(byte index);
		byte getLutIndex() const;
		void setLutIndex(byte index);
		byte getDepthIndex() const;
		void setDepthIndex(byte index);
		// Funzioni derivate
		virtual void setSize(Size size);
		virtual void setFocus(bool focus);
	};
}