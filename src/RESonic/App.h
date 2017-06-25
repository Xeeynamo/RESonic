#pragma once
#include "..\libXeEngine\Application.h"
#include "..\libXeEngine\Game.h"
#include "..\libXeEditor\MainEditor.h"

class RESonic1;
class RESonic1App : public XeEngine::Application
{
private:
	float appWidth;
	float appHeight;
protected:
	RESonic1* s1;
	Editor::MainEditor* editor;
public:
	RESonic1App();
	~RESonic1App();

	void OnExecute();
	void OnInitialize();
	void OnDestroy();
	void OnBackground();
	void OnForeground();
	void OnResize(short, short, float zoom = 1.0f);
	bool OnClose();
};