#pragma once
#include "Control.h"

namespace Editor
{
	class EXPORT Preview : public Control
	{
	private:
	protected:
		bool debug;
		int m_cursor[8];
		int m_menu[8];
		int m_menustack;

		virtual void _Draw();
		virtual bool _InputKeyb(int key, bool up);
		virtual bool _InputKeyb(int key);
	public:
		Preview(MainEditor*);
		~Preview();

	};
}