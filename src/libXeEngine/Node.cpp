#include "Node.h"

namespace XeEngine
{
	Node::Node()
	{
		x = y = 0;
		m_rotx = m_roty = m_rotz = 0.0f;
		m_scalex = m_scaley = 1.0f;
	}
	Node::~Node()
	{
	}

	void Node::Draw()
	{
		Node* n;

		m_childLx.MoveHead();
		while(m_childLx.Next(n) == true)
			n->Draw();

		SelfDraw();

		m_childRx.MoveHead();
		while(m_childRx.Next(n) == true)
			n->Draw();
	}
	void Node::SelfDraw()
	{
	}
	
	short& Node::PositionX()
	{
		return x;
	}
	short& Node::PositionY()
	{
		return y;
	}
	float& Node::RotationX()
	{
		return m_rotx;
	}
	float& Node::RotationY()
	{
		return m_roty;
	}
	float& Node::RotationZ()
	{
		return m_rotz;
	}
	float& Node::ScaleX()
	{
		return m_scalex;
	}
	float& Node::ScaleY()
	{
		return m_scaley;
	}
}