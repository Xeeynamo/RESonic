#include "MainEditor.h"


namespace Editor
{
	class PaletteSelector;
	class Slidebar;
	class PaletteEditor : public Control
	{
	private:
		Color prev;
		PaletteSelector *palSelector;
		Slidebar *slideR;
		Slidebar *slideG;
		Slidebar *slideB;
		Slidebar *slideA;
	protected:
		virtual void _Draw();
		//virtual bool _InputKeyb(int key);
		virtual bool _InputMouse(short x, short y, int button);
	public:
		PaletteEditor(MainEditor*);
		~PaletteEditor();

		Color getColor();
		void setColor(Color);
		void WriteColor(Slidebar*);
	};
}