#include "Model.h"

XeEngine::Model::Model()
{
	position = nullptr;
	color = nullptr;
	// DEBUG
	position = new VertexPosition[8];
	position[0] = VertexPosition(+100.0, -100.0, -100.0);
	position[1] = VertexPosition(+100.0, -100.0, +100.0);
	position[2] = VertexPosition(-100.0, -100.0, +100.0);
	position[3] = VertexPosition(-100.0, -100.0, -100.0);
	position[4] = VertexPosition(+100.0, +100.0, -100.0);
	position[5] = VertexPosition(+100.0, +100.0, +100.0);
	position[6] = VertexPosition(-100.0, +100.0, +100.0);
	position[7] = VertexPosition(-100.0, +100.0, -100.0);
	color = new VertexColor[8];
	color[0] = VertexColor(1.0f, 1.0f, 1.0f, 1.0f);
	color[1] = VertexColor(1.0f, 1.0f, 1.0f, 1.0f);
	color[2] = VertexColor(1.0f, 1.0f, 1.0f, 1.0f);
	color[3] = VertexColor(1.0f, 1.0f, 1.0f, 1.0f);
	color[4] = VertexColor(1.0f, 1.0f, 1.0f, 1.0f);
	color[5] = VertexColor(1.0f, 1.0f, 1.0f, 1.0f);
	color[6] = VertexColor(1.0f, 1.0f, 1.0f, 1.0f);
	color[7] = VertexColor(1.0f, 1.0f, 1.0f, 1.0f);
}
XeEngine::Model::~Model()
{
	SAFE_ADELETE(position);
	SAFE_ADELETE(color);
}

void XeEngine::Model::OpenObj(String& filename)
{

}
void XeEngine::Model::OpenX3D(String& filename)
{

}
void XeEngine::Model::SaveX3D(String& filename)
{

}
void XeEngine::Model::Render(const Point& pos, const Size& scale, const Point& rotation)
{

}