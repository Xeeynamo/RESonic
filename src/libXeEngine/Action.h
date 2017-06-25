#pragma once

namespace XeEngine
{
	class Node;
	class Action
	{
	protected:
		Node* node;
	public:
		virtual ~Action(){}

		//! \brief Execute an action until its end
		//! \return Returns false if the action was concluded
		virtual bool Do() = 0;

		virtual void AttachNode(Node* node)
		{
			this->node = node;
		}
	};
}