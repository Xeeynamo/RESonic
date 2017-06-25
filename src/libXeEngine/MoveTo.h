#pragma once
#include "Geometry.h"
#include "Action.h"

namespace XeEngine
{
	class Node;
	namespace Actions
	{
		//! \brief Move from a pointer to another
		class MoveTo : public Action
		{
		private:
			Point cur;
			Point dst;
			float speed;
			float speedX;
			float speedY;
			short frameCurrent;
			short frameTotal;
		public:
			//! \param Destionation point
			//! \param The speed. More the value is high, more slow will be the action. 1.0 means one second
			MoveTo(Point&, float speed);

			bool Do();
			void AttachNode(Node*);
		};
	}
}