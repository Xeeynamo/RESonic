#pragma once
#include "XeBase.h"

class Game;
class GameState
{
protected:
	Game *game;
public:
	GameState(Game *game)
	{
		this->game = game;
	}

	virtual void Do()
	{

	}
	virtual void Draw()
	{

	}
	virtual void Input(KeyInput)
	{

	}
};