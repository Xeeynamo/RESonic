#include "Game_level.h"
#include "Game.h"

const unsigned int object_collision_debug_colors[12] =
{
	MAKEARGB(0x40, 0xFF, 0x00, 0x00),
	MAKEARGB(0x40, 0x00, 0xFF, 0x00),
	MAKEARGB(0x40, 0x00, 0x00, 0xFF),
	MAKEARGB(0x40, 0xFF, 0xFF, 0x00),
	MAKEARGB(0x40, 0xFF, 0x00, 0xFF),
	MAKEARGB(0x40, 0x00, 0xFF, 0xFF),
	MAKEARGB(0x40, 0xE0, 0x20, 0x20),
	MAKEARGB(0x40, 0x20, 0xE0, 0x20),
	MAKEARGB(0x40, 0x20, 0x20, 0xE0),
	MAKEARGB(0x40, 0xE0, 0xE0, 0x20),
	MAKEARGB(0x40, 0xE0, 0x20, 0xE0),
	MAKEARGB(0x40, 0x20, 0xE0, 0xE0),
};

Game_Level::Game_Level(Game *game) : GameState(game)
{
	level = &game->level;
}
Game_Level::~Game_Level()
{

}

void Game_Level::Do()
{
	level->StartStage();
	level->timelevel++;

	XeObject *player = level->GetAttachedObject();
	for(int i=0; i<OBJECT_COUNT; i++)
	{
		if (level->object[i])
		{
			if (player->Collide(level->object[i]))
			{
				player->CollisionObject(level->object[i]);
				level->object[i]->CollisionObject(player);
			}
		}
	}
}
void Game_Level::Draw()
{
	level->UpdateCamera();

	for(int i=0; i<level->map.properties.layerCount; i++)
	{
		game->LevelBlock(i);
		game->LevelDraw(i);
	}

	ObjectContainer *container;
	for(int i=0; i<OBJECT_COUNT; i++)
	{
		if(!level->object[i]) continue;

		container = level->SelectObject(level->object[i]->GetID());
		if (container->clut == 0xFF)
			XeEffect::SetProperties(0);
		else
		{
			XeEffect::SetProperties(1);
			XeEffect::SetClutDepth(container->clut, CLUT_COUNT);
			XeEffect::SetClutIndex(container->palette);
		}
		level->object[i]->Do();
		if(!level->object[i]) continue;
		level->object[i]->Draw();

#ifndef DEBUG
		continue;
#endif
		//////////////////////////////////////////////////////////////////////////
		// Collision debug
		XeEffect::SetProperties(0);
		ObjectHitboxRect collision = level->object[i]->collision;
		XeShape::SetColor(object_collision_debug_colors[i%12]);
		
		switch((level->object[i]->angle+0x20)&0xC0)
		{
		case 0x00:
			XeShape::FillRect(PFLOAT_TO_SHORT(level->object[i]->x - collision.left - level->cameraX), PFLOAT_TO_SHORT(level->object[i]->y - collision.top - level->cameraY),
				level->object[i]->z+0.5f, collision.Left() + collision.Right(), collision.Top() + collision.Bottom());
			break;
		case 0x40:
			XeShape::FillRect(PFLOAT_TO_SHORT(level->object[i]->x - collision.bottom - level->cameraX), PFLOAT_TO_SHORT(level->object[i]->y - collision.left - level->cameraY),
				level->object[i]->z+0.5f, collision.Top() + collision.Bottom(), collision.Left() + collision.Right());
			break;
		case 0x80:
			XeShape::FillRect(PFLOAT_TO_SHORT(level->object[i]->x - collision.right - level->cameraX), PFLOAT_TO_SHORT(level->object[i]->y - collision.bottom - level->cameraY),
				level->object[i]->z+0.5f, collision.Left() + collision.Right(), collision.Top() + collision.Bottom());
			break;
		case 0xC0:
			XeShape::FillRect(PFLOAT_TO_SHORT(level->object[i]->x - collision.top - level->cameraX), PFLOAT_TO_SHORT(level->object[i]->y - collision.right - level->cameraY),
				level->object[i]->z+0.5f, collision.Top() + collision.Bottom(), collision.Left() + collision.Right());
			break;
		}
		//////////////////////////////////////////////////////////////////////////
	}
}
void Game_Level::Input(KeyInput k)
{
	XeObject *o = level->GetAttachedObject();
	if (o) o->Input(k);
}