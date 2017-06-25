#include "MainEditor.h"

namespace Editor
{
	class Slidebar : public Control
	{
	private:
		float mod;
		virtual bool _InputMouse(short x, short y, int button);
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

		virtual void setSize(CtrlSize size);
	public:
		void (*eChangeValue)(Slidebar*, Control *parent, int value);
	};
}