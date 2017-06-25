#include "XeLevel.h"
#include <stdio.h>

const char *emptystring = "";

//////////////////////////////////////////////////////////////////////////
// Funzioni di caricamento del livello
void XeLevel::LoadStage(char *levelname)
{
	XeEngine::File f;
	int pos;
	byte size;
	char path[0x40];

	sprintf_s(path, "%s\\%s.%s", PATH_LEVEL, levelname, "STG");
	if (!f.Open(XeEngine::String(path)))
	{
		con.Log(DEBUG_LEVEL_ERROR, "XeLevel::LoadStage(%s)", path);
		return;
	}
	f.Read(&size, 1);
	f.Read(&stage.resolution, 1);
	f.Read(&stage.actcount, 1);
	f.Read(&stage.hidetilecard, 1);

	if (stage.act) delete[] stage.act;
	if (stage.name) delete[] stage.name;
	if (stage.suffix) delete[] stage.suffix;

	stage.act = new StageAct[stage.actcount];
	stage.name = new char[size];
	f.Read(stage.name, size);
	f.Read(&pos, 4);
	size = f.Position();
	stage.mem.Alloc(pos - size);
	f.Read(stage.mem.GetMemoryHandle(), stage.mem.Size());
	f.Seek(pos);

	for(int i=0; i<stage.actcount; i++)
	{
		for(int j=0; j<sizeof(StageAct)/sizeof(char*); j++)
		{
			unsigned short k;
			f.Read(&k, 2);
			if (k == 0xFFFF)
				((char**)&stage.act[i])[j] = (char*)emptystring;
			else
				((int*)&stage.act[i])[j] = k + (int)((char*)stage.mem.GetMemoryHandle() - size);

		}
	}
	size = XeEngine::StringLength(levelname) + 1;
	stage.suffix = new char[size];
	XeEngine::MemoryCopy(stage.suffix, levelname, size);

	LoadStageElements();
	return;
}
void XeLevel::LoadStageElements()
{
	char *path;
	LoadGFXResolution();

	LUT *lut = new LUT;
	path = MakePath(currentAct, STAGEFILE_LUT);
	if (lut->Load(path)) LoadLevelLUT(lut);
	else con.Log(DEBUG_LEVEL_ERROR, "LoadStageElements() %s", path);
	delete lut;

	BLK *blk = new BLK;
	path = MakePath(currentAct, STAGEFILE_BLK);
	if (blk->Load(path)) LoadLevelBLK(blk);
	else con.Log(DEBUG_LEVEL_ERROR, "LoadStageElements() %s", path);
	delete blk;

	HBX *hbx = new HBX;
	path = MakePath(currentAct, STAGEFILE_HBX);
	if (hbx->Load(path)) LoadLevelHBX(hbx);
	else con.Log(DEBUG_LEVEL_ERROR, "LoadStageElements() %s", path);
	delete hbx;

	CLI *cli = new CLI;
	path = MakePath(currentAct, STAGEFILE_CLI);
	if (cli->Load(path)) LoadLevelCLI(cli);
	else con.Log(DEBUG_LEVEL_ERROR, "LoadStageElements() %s", path);
	delete cli;

	path = MakePath(currentAct, STAGEFILE_MAP);
	if (!map.Load(path))
		con.Log(DEBUG_LEVEL_ERROR, "LoadStageElements() %s", path);

	path = MakePath(currentAct, STAGEFILE_OBP);
	if (!objectPlacement.Load(path))
		con.Log(DEBUG_LEVEL_ERROR, "LoadStageElements() %s", path);
}
void XeLevel::LoadGFXResolution()
{
	if (!stage.suffix) return;

	char filename[0x40];
	for(int i=depthResolution; i>0; i--)
	{
		sprintf_s(filename, "%s\\%s\\%s@%i.%s", PATH_LEVEL, stage.suffix, stage.act[currentAct].gfx, i, "GFX");
		if (XeEngine::File::Exist(XeEngine::String(filename)))
		{
			GFX gfx;
			if (gfx.Load(XeEngine::String(filename)))
			{
				texture.Create(&gfx);
				sprintf_s(filename, "%s\\%s\\%s@%i.%s", PATH_LEVEL, stage.suffix, stage.act[currentAct].dtl, i, "DTL");
				dynamicTiles.Load(filename);
				i = 0;
			}
			else continue;
		}
	}
}
char *XeLevel::MakePath(int act, STAGEFILE file)
{
	char path2[0x40];
	sprintf_s(path2, "%s%s%s%s", "LEVEL", "\\", stage.suffix, "\\");
	switch(file)
	{
	case STAGEFILE_GFX:
		for(int i=depthResolution; i>0; i--)
		{
			sprintf_s(path, "%s%s%s%i%s%s", path2, stage.act[act].clut, "@", i, ".", "GFX");
			if (XeEngine::File::Exist(XeEngine::String(path)))
			{
				return path;
			}
		}
		sprintf_s(path, "%s%s%s%s", path2, stage.act[act].gfx, ".", "GFX");
		break;
	case STAGEFILE_LUT:
		sprintf_s(path, "%s%s%s%s", path2, stage.act[act].clut, ".", "LUT");
		break;
	case STAGEFILE_CLI:
		sprintf_s(path, "%s%s%s%s", path2, stage.act[act].cli, ".", "CLI");
		break;
	case STAGEFILE_HBX:
		sprintf_s(path, "%s%s%s%s", path2, stage.act[act].hbx, ".", "HBX");
		break;
	case STAGEFILE_MAP:
		sprintf_s(path, "%s%s%s%s", path2, stage.act[act].map, ".", "MAP");
		break;
	case STAGEFILE_BLK:
		sprintf_s(path, "%s%s%s%s", path2, stage.act[act].blk, ".", "BLK");
		break;
	case STAGEFILE_RNG:
		sprintf_s(path, "%s%s%s%s", path2, stage.act[act].rng, ".", "RNG");
		break;
	case STAGEFILE_OBP:
		sprintf_s(path, "%s%s%s%s", path2, stage.act[act].obp, ".", "OBP");
		break;
	case STAGEFILE_DEF:
		sprintf_s(path, "%s%s%s%s", path2, stage.act[act].def, ".", "DEF");
		break;
	case STAGEFILE_DTL:
		for(int i=depthResolution; i>0; i--)
		{
			sprintf_s(path, "%s%s%s%i%s%s", path2, stage.act[act].clut, "@", i, ".", "GFX");
			if (XeEngine::File::Exist(XeEngine::String(path)))
			{
				sprintf_s(path, "%s%s%s%i%s%s", path2, stage.act[act].clut, "@", i, ".", "DTL");
				return path;
			}
		}
		sprintf_s(path, "%s%s%s%s", path2, stage.act[act].dtl, ".", "DTL");
		break;
	case STAGEFILE_DPL:
		sprintf_s(path, "%s%s%s%s", path2, stage.act[act].tpl, ".", "DPL");
		break;
	case STAGEFILE_CRD:
		sprintf_s(path, "%s%s%s%s", path2, stage.act[act].crd, ".", "CRD");
		break;
	case STAGEFILE_BGM:
		sprintf_s(path, "%s%s%s%s", path2, stage.act[act].bgm, ".", "BGM");
		break;
	}
	return path;
}

//////////////////////////////////////////////////////////////////////////
// Funzioni di caricamento delle varie parti del livello
void XeLevel::_internal_LoadLUT(LUT *lut, Palette *pal)
{
	if (!lut) return;
	int count = lut->PaletteCount();
	int dest = lut->DestinationIndex();
	int colors = lut->ColorsPerPalette();
	for(int i=0; i<count; i++)
	{
		if (dest + i >= PALETTE_COUNT) continue;
		pal[dest+i][0] = 0;
		for(int j=0; j<colors; j++)
		{
			pal[dest+i][j] = lut->UnpackColor(j, i);
		}
	}
}
void XeLevel::LoadLevelGFX(GFX *gfx)
{
	if (!gfx) return;
	texture.Create(gfx);
}
void XeLevel::LoadLevelLUT(LUT *lut)
{
	_internal_LoadLUT(lut, palette[1]);
}
void XeLevel::LoadSharedLUT(LUT *lut)
{
	_internal_LoadLUT(lut, palette[0]);
}
void XeLevel::LoadLevelBLK(BLK *blk)
{
	blk->SetData(chunk);
}
void XeLevel::LoadLevelHBX(HBX *hitbox)
{
	XeEngine::MemoryCopy(collision, hitbox->hitbox, sizeof(collision));
	XeEngine::MemoryCopy(collisionAngle, hitbox->angle, sizeof(collisionAngle));
}
void XeLevel::LoadLevelCLI(CLI *cli)
{
	cli->SetData(collisionIndex);
}
