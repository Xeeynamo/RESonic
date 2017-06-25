#pragma once
#include "XeBase.h"
#include "List.h"

namespace XeEngine
{
	class Node
	{
	public:
		Node();
		~Node();

		void Draw();
		virtual void SelfDraw();
		
		short& PositionX();
		short& PositionY();
		float& RotationX();
		float& RotationY();
		float& RotationZ();
		float& ScaleX();
		float& ScaleY();
	protected:
		UID m_id;
		short m_zOrder;
		float m_rotx, m_roty, m_rotz;
		float m_scalex, m_scaley;
		short x, y;
		List<Node*> m_childLx;
		List<Node*> m_childRx;
	private:
	};
}