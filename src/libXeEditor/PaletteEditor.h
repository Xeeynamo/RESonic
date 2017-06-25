#include "MainEditor.h"


namespace Editor
{
	class PaletteSelector;
	class Slidebar;
	class FixedMenu;
	class EXPORT PaletteEditor : public Control
	{
	private:
		XeEngine::Color32 prev;
		PaletteSelector *palSelector;
		Slidebar *slideR;
		Slidebar *slideG;
		Slidebar *slideB;
		Slidebar *slideA;
		FixedMenu* lutFilesMenu;
	protected:
		virtual void _Draw();
		//virtual bool _InputKeyb(int key);
		virtual bool _InputMouse(u16 x, u16 y, XeEngine::MouseInput button);
	public:
		PaletteEditor(MainEditor*);
		~PaletteEditor();

		XeEngine::Color32 getColor();
		void setColor(XeEngine::Color32);
		void WriteColor(Slidebar*);

		// DERIVATE
		virtual void setFocus(bool focus);
	};
}