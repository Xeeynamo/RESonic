#pragma once
#include "Control.h"

namespace Editor
{
	class Preview : public Control
	{
	private:
	protected:
		KeyInput k;
		bool debug;

		virtual void _Draw();
		virtual bool _InputKeyb(int key, bool up);
		virtual bool _InputKeyb(int key);
	public:
		Preview(MainEditor*);
		~Preview();

	};
}