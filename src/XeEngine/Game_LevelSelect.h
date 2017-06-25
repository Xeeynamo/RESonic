#include "GameState.h"

class Game_LevelSelect : public GameState
{
private:
protected:
	struct StageListProperties
	{
		char *suffix;
		char name[0x20];
		unsigned char actcount;
	};
	struct StageList
	{
		StageListProperties stage;
		struct StageList *next;
	};

	unsigned short count;
	StageList *list;

	int selectedlevel;
	int selectedact;
	int actcount;

	void _internal_BuildStageList();
	void _internal_CheckInputError();
public:
	Game_LevelSelect(Game *game);
	~Game_LevelSelect();

	virtual void Do();
	virtual void Draw();
	virtual void Input(KeyInput);
};