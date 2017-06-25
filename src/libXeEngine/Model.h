#pragma once
#include "String.h"
#include "Video.h"
#include "Geometry.h"

namespace XeEngine
{
	class Model
	{
	private:
		VertexPosition* position;
		VertexColor* color;
	protected:
	public:
		Model();
		~Model();

		void OpenObj(String&);
		void OpenX3D(String&);
		void SaveX3D(String&);
		void Render(const Point& position, const Size& scale, const Point& rotation);
	};
}
