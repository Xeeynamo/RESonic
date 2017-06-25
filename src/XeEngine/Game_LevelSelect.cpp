#include "Game_LevelSelect.h"
#include "Game_Level.h"
#include "Game.h"
#include <stdio.h>

#define LEVELSELECT_POSX	16
#define LEVELSELECT_POSY	16

Game_LevelSelect::Game_LevelSelect(Game *game) : GameState(game)
{
	selectedlevel = 0;
	selectedact = 0;

	_internal_BuildStageList();
	return;
}
Game_LevelSelect::~Game_LevelSelect()
{

}

void Game_LevelSelect::_internal_BuildStageList()
{
	char *name;
	char path[0x40];

	count = 0;
	StageList *l;
	for(int i=0; i<game->StageListCount(); i++)
	{
		name = game->StageNameIndex(i);
		sprintf_s(path, "%s\\%s.%s", "LEVEL", name, "STG");

		XeEngine::File f;
		if (f.Open(XeEngine::String(path)))
		{
			if (count == 0)
			{
				list = new StageList;
				l = list;
				l->next = NULL;
			}
			else
			{
				l->next = new StageList;
				l = l->next;
				l->next = NULL;
			}

			byte length;
			f.Read(&length, 1);
			f.Seek(1, XeEngine::FILESEEK_CUR);
			f.Read(&l->stage.actcount, 1);
			f.Seek(1, XeEngine::FILESEEK_CUR);
			f.Read(l->stage.name, length);
			f.Close();
			l->stage.suffix = name;
			count++;
		}
	}
}

void Game_LevelSelect::Do()
{

}
void Game_LevelSelect::Draw()
{
	StageList *l = list;
	for(int i=0; i<count; i++)
	{
		if (i == selectedlevel)
			game->TextColor(TEXTCOLOR_YELLOW);
		else game->TextColor(TEXTCOLOR_WHITE);
		game->PrintText(LEVELSELECT_POSX + 0, LEVELSELECT_POSY + i*16, "%s", l->stage.name);

		game->TextColor(TEXTCOLOR_WHITE);
		game->PrintText(LEVELSELECT_POSX + 32, LEVELSELECT_POSY + i*16 + 8, "ACT", l->stage.name);

		for(int j=0; j<l->stage.actcount; j++)
		{
			if (j == selectedact && i == selectedlevel) game->TextColor(TEXTCOLOR_YELLOW);
			else game->TextColor(TEXTCOLOR_WHITE);
			game->PrintText(LEVELSELECT_POSX + 64 + j*16, LEVELSELECT_POSY + i*16 + 8, "%i", j+1);
		}
		l = l->next;
	}
	game->TextColor(TEXTCOLOR_WHITE);
}
void Game_LevelSelect::_internal_CheckInputError()
{
	StageList *l = list;
	for(int i=0; i<count; i++)
	{
		if (i == selectedlevel)
		{
			actcount = l->stage.actcount;
			i = count;
			continue;
		}
		l = l->next;
	}

	if (selectedlevel < 0)
		selectedlevel = count - 1;
	else if (selectedlevel >= count)
		selectedlevel = 0;
	if (selectedact < 0)
		selectedact = actcount - 1;
	else if (selectedact >= actcount)
			selectedact = 0;
}
void Game_LevelSelect::Input(KeyInput k)
{
	if (k.up)
	{
		selectedlevel--;
		_internal_CheckInputError();
	}
	if (k.down)
	{
		selectedlevel++;
		_internal_CheckInputError();
	}
	if (k.left)
	{
		selectedact--;
		_internal_CheckInputError();
	}
	if (k.right)
	{
		selectedact++;
		_internal_CheckInputError();
	}

	if (k.start)
	{
		StageList *l = list;
		for(int i=0; i<selectedlevel; i++)
		{
			l = l->next;
		}
		game->level.currentAct = selectedact;
		game->level.LoadStage(l->stage.suffix);
		game->SetGameState(new Game_Level(game));
	}
}