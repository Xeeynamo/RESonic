#include "Game_tests.h"
#include "Game_Level.h"
#include "Game.h"
#include <stdio.h>

#include "GFX.h"
#include "XeString.h"
#include "XeSystem.h"

Game_Tests::Game_Tests(Game *game) : GameState(game)
{
	cameraX = 0;

	GFX gfx;
	gfx.Load(XeEngine::String("TEST\\TEST_32.GFX"));
	test.Create(&gfx);

	for(int i=0; i<sizeof(speed) / sizeof(float); i++)
		speed[i] = 1.0f;
	parallax.Create(1, sizeof(speed) / sizeof(float), 1, XeEngine::XeTexturePixelFormat_FLOAT, speed);
}
Game_Tests::~Game_Tests()
{

}

void Game_Tests::Do()
{
	for(int i=0; i<112; i++)
		speed[i] = .2f;
	for(int i=112; i<128; i++)
		speed[i] = .6f;
	for(int i=128; i<144; i++)
		speed[i] = .8f;
	for(int i=144; i<224; i++)
		speed[i] = (i-144) * (1.0f / (224-144));

	parallax.Upload(0, 0, 1, sizeof(speed) / sizeof(float), 0, 1, speed);
}
void Game_Tests::Draw()
{
	XeEffect::SetCameraX(cameraX);
	XeEffect::SetParallaxTexture(parallax.GetID(), test.GetWidth());

	XeEffect::SetProperties(0);
	XeEffect::SetTexture();
	test.Draw();
}
void Game_Tests::Input(KeyInput k)
{
	if (k.left)
	{
		cameraX--;
	}
	if (k.right)
	{
		cameraX++;
	}
}