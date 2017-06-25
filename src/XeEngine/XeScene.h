#pragma once
#include "XeEngine.h"
#include "OGL.h"

#define FLOAT_COLOR_8BIT(c)	((float)((1.0/255.0)*(float)(c)))

class XeScene
{
private:
	COLORREF _clearColor;

	int bind;
protected:
public:
	XeScene();
	~XeScene();

	// Inizializza i valori dell'OpenGL
	void Initialize();

	void OnPaintBegin();
	void OnPaintEnd();

	static void MatrixMode(ushort matrix);
	static void Push();
	static void Pop();
	static void Identity();

	static void SetViewPort(int width, int height);
	static void SetProjection(int width, int height, float depth);

	int  GetRenderSize();
	void SetRenderSize(short width, short height);
	int  GetCameraSize();
	static void SetCameraSize(short width, short height);
	COLORREF GetClearColor();
	void SetClearColor(COLORREF);

	static void MovePosition(short x, short y);
	static void MovePosition(short x, short y, float depth);
	static void SetPosition(short x, short y);
	static void SetPosition(short x, short y, float depth);
	static void SetRotation(float angle);
	static void SetScale(float x, float y);

	static void Bind2DTexture(int id);
	static void Bind3DTexture(int id);
};