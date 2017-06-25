#include "GameState.h"

class XeLevel;
class Game_Level : public GameState
{
private:
protected:
	XeLevel *level;
public:
	Game_Level(Game *game);
	~Game_Level();

	void Do();
	void Draw();
	virtual void Input(KeyInput);
};