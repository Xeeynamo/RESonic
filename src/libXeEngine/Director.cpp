#include "Director.h"

#define DEFAULT_FPS		60.0f

XeEngine::Director::Director()
{
	SetInterval(DEFAULT_FPS);
}
XeEngine::Director::~Director()
{

}

void XeEngine::Director::Initialize()
{

}

float XeEngine::Director::GetInterval() const
{
	return 1.0f / drawInterval;
}
void XeEngine::Director::SetInterval(float interval)
{
	drawInterval = 1.0f / interval;
}
float XeEngine::Director::GetFPS()
{
	return 0.0f;
}