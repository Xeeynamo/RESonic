#include "GameState.h"
#include "GFX.h"
#include "XeTexture.h"

class Game_Tests : public GameState
{
private:
protected:
	int cameraX;
	XeTexture test;
	XeTexture parallax;

	float speed[224];

	// Software rendering tests
	int screen[400*256];
	char sprite[128*128];
	int palette[0x100];
public:
	Game_Tests(Game *game);
	~Game_Tests();

	virtual void Do();
	virtual void Draw();
	virtual void Input(KeyInput);
};