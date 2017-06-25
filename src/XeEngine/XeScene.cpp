#include "XeEngineLV2.h"

short xescene_renderwidth;
short xescene_renderheight;
short xescene_camerawidth;
short xescene_cameraheight;

XeScene::XeScene()
{
	xescene_renderwidth = xescene_renderheight = 1;
	xescene_camerawidth = xescene_cameraheight = 1;
	_clearColor = 0;
}
XeScene::~XeScene()
{

}

void XeScene::Initialize()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_NOTEQUAL, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);

	xglInit();
}

void XeScene::OnPaintBegin()
{
	GLfloat m[4][4];

	SetViewPort(xescene_renderwidth, xescene_renderheight);
	SetProjection(xescene_camerawidth, xescene_cameraheight, 16.0f);
	glGetFloatv(GL_PROJECTION_MATRIX, *m);
	glGetFloatv(GL_VIEWPORT, *m);
	glMatrixMode(GL_MODELVIEW);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void XeScene::OnPaintEnd()
{
	//glFlush();
	//glFinish();
}

void XeScene::MatrixMode(ushort matrix = GL_MODELVIEW)
{
	glMatrixMode(matrix);
}
void XeScene::Push()
{
	glPushMatrix();
}
void XeScene::Pop()
{
	glPopMatrix();
}
void XeScene::Identity()
{
	glLoadIdentity();
}

void XeScene::SetViewPort(int width, int height)
{
	glMatrixMode(GL_VIEWPORT);
	glLoadIdentity();
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}
void XeScene::SetProjection(int width, int height, float depth)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, (GLdouble)width, (GLdouble)height, 0, (GLdouble)-depth, (GLdouble)+depth);
}
int XeScene::GetRenderSize()
{
	return xescene_renderwidth | (xescene_renderheight<<16);
}
void XeScene::SetRenderSize(short width, short height)
{
	xescene_renderwidth = width;
	xescene_renderheight = height;
}
int XeScene::GetCameraSize()
{
	return xescene_camerawidth | (xescene_cameraheight<<16);
}
void XeScene::SetCameraSize(short width, short height)
{
	xescene_camerawidth = width;
	xescene_cameraheight = height;
}
COLORREF XeScene::GetClearColor()
{
	return _clearColor;
}
void XeScene::SetClearColor(COLORREF color)
{
	_clearColor = color;
	glClearColor(FLOAT_COLOR_8BIT(_clearColor&0xFF), FLOAT_COLOR_8BIT((_clearColor>>8)&0xFF), FLOAT_COLOR_8BIT((_clearColor>>16)&0xFF), 0.0f);
}

void XeScene::SetRotation(float angle)
{
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
}
void XeScene::SetScale(float x, float y)
{
	glScalef(x, y, 1.0f);
}

void XeScene::MovePosition(short x, short y)
{
	glTranslatef((float)x, (float)y, 0.0f);
}
void XeScene::MovePosition(short x, short y, float depth)
{
	glTranslatef((float)x, (float)y, depth);
}
void XeScene::SetPosition(short x, short y)
{
	glLoadIdentity();
	glTranslatef((float)x, (float)y, 0.0f);
}
void XeScene::SetPosition(short x, short y, float depth)
{
	glLoadIdentity();
	glTranslatef((float)x, (float)y, depth);
}
int xescene_bind;
void XeScene::Bind2DTexture(int id)
{
	if (xescene_bind != id)
	{
		glBindTexture(GL_TEXTURE_2D, id);
		xescene_bind = id;
	}
}
void XeScene::Bind3DTexture(int id)
{
	if (xescene_bind != id)
	{
		glBindTexture(GL_TEXTURE_3D, id);
		xescene_bind = id;
	}
}