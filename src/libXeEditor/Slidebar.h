#include "MainEditor.h"

namespace Editor
{
	class EXPORT Slidebar : public Control
	{
	private:
		float mod;
		virtual bool _InputMouse(u16 x, u16 y, XeEngine::MouseInput button);
	protected:
		int min, max, value;

		virtual void _Draw();
		virtual bool _InputKeyb(int key);
	public:
		Slidebar(MainEditor*, Control *parent, short x, short y, short width);

		int  getMin();
		void setMin(int);
		int  getMax();
		void setMax(int);
		int  getValue();
		void setValue(int);

		virtual void setSize(Size size);
	public:
		void (*eChangeValue)(Slidebar*, Control *parent, int value);
	};
}