#include "XeLevel.h"
#include "XeObject.h"
#include "ObjectList.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////
// Funzioni di iterazione con gli oggetti
char XeLevel::LoadObject(ushort id)
{
	int index = -1;
	for(int i=0; i<0x0E; i++)
	{
		if (objlist[i].id == id)
		{
			index = i;
			i = 0xFFFF;
		}
	}
	if (index == -1)
	{
		return 0;
	}

	if (SelectObject(id)) return 2;	// Controlla se l'oggetto è stato immesso in precedenza
	char path[0x40];
	for(int i=0; i<OBJECT_COUNT; i++)	// Inserisce l'oggetto nel primo spazio vuoto
	{
		if (!objcont[i].filled)
		{
			sprintf_s(path, "OBJECT\\%s\\%s.%s", objlist[index].name, objlist[index].name, "OBJ");
			if (!objcont[i].animation.LoadAnimation(path))
			{
				con.Log(DEBUG_LEVEL_WARNING, "OBJECT\\%s\\%s.%s", objlist[index].name, objlist[index].name, "OBJ");
				return false;
			}
			con.Log(DEBUG_LEVEL_INFO, "OBJECT\\%s\\%s.%s", objlist[index].name, objlist[index].name, "OBJ");

			int j;
			GFX gfx;
			for(j=2; j>0; j--)
			{
				sprintf_s(path, "OBJECT\\%s\\%s@%i.%s", objlist[index].name, objlist[index].name, j, "GFX");
				if (!gfx.Load(XeEngine::String(path)))
				{
					con.Log(DEBUG_LEVEL_WARNING, "OBJECT\\%s\\%s@%i.%s", objlist[index].name, objlist[index].name, j, "GFX");
					continue;
				}
				if (!objcont[i].texture.Create(&gfx))
				{
					con.Log(DEBUG_LEVEL_WARNING, "OBJECT\\%s\\%s@%i.%s", objlist[index].name, objlist[index].name, j, "GFX");
					continue;
				}
				j *= -1;
			}
			j = -j - 1;
			if (j == 0)
			{
				con.Log(DEBUG_LEVEL_ERROR, "OBJECT\\%s\\%s.%s", objlist[index].name, objlist[index].name, "GFX");
				return false;
			}
			con.Log(DEBUG_LEVEL_INFO, "OBJECT\\%s\\%s@%i.%s", objlist[index].name, objlist[index].name, j, "GFX");

			objcont[i].filled = 1;
			objcont[i].id = id;
			switch(gfx.GetFormat())
			{
			case XeEngine::XeTexturePixelFormat::XeTexturePixelFormat_A8:
				for(int j=0; j<0x200; j++)
				{
					if (palette[2][j][0] == 0xFFFFFFFF)
					{
						objcont[i].clut = (j>>8)+2;
						objcont[i].palette = j&0xFF;
						
						LUT lut;
						sprintf_s(path, "OBJECT\\%s\\%s.%s", objlist[index].name, objlist[index].name, "LUT");
						if (!lut.Load(path)) objcont[i].clut = 0xFF;
						_internal_LoadLUT(&lut, &palette[2][j]);
						return true;
					}
					continue;
				}
				break;
			}
			objcont[i].clut = 0xFF;
			return 1;
		}
		continue;
	}
	con.Log(DEBUG_LEVEL_ERROR, "ID %04 not found", id);
	return 0;
}
ObjectContainer *XeLevel::SelectObject(ushort id)
{
	for(int i=0; i<OBJECT_COUNT; i++)	// Controlla se l'oggetto è stato immesso in precedenza
	{
		if (objcont[i].filled)
		{
			if (objcont[i].id == id)
				return &objcont[i];
		}
	}
	return NULL;
}
void XeLevel::AttachEntity(XeObject *mainobject)
{
	this->mainobject = mainobject;
	mainobject->AttachLevel(this);
	return;
}
XeObject *XeLevel::GetAttachedObject()
{
	return mainobject;
}
void XeLevel::UpdateCamera()
{
	if (!mainobject) return;
	LayerProperties* layer = map.Layer(0);
	if (layer == NULL) return;

	PFloat screenWidth = resWidth<<16;
	PFloat screenHeight = resHeight<<16;
	PFloat levelWidth = layer->width<<24;
	PFloat levelHeight = layer->height<<24;

	levelWidth = border.right<<16;
	levelHeight = border.bottom<<16;

	// Camera X
	if (mainobject->x < screenWidth/2) cameraX = 0;			// Se l'oggetto è all'estrema sinistra, la telecamera X è posizionata a 0
	else if (mainobject->x > levelWidth-screenWidth/2)		// Se l'oggetto è posizionato all'estrema destra
	{
		cameraX = levelWidth-screenWidth;
	}
	else cameraX = mainobject->x - screenWidth/2;
	// Camera Y
	if (mainobject->y < screenHeight/2) cameraY = 0;			// Se l'oggetto è all'estrema sinistra, la telecamera X è posizionata a 0
	else if (mainobject->y > levelHeight-screenHeight/2)		// Se l'oggetto è posizionato all'estrema destra
	{
		cameraY = levelHeight-screenHeight;
	}
	else cameraY = mainobject->y - screenHeight/2;

	if ((cameraX>>16) < border.left)
		cameraX = border.left<<16;
	if ((cameraX>>16) + resWidth > border.right)
		cameraX = (border.right - resWidth) <<16;

	if ((cameraY>>16) < border.top)
		cameraY = border.top<<16;
	if ((cameraY>>16) + resHeight > border.bottom)
		cameraY = (border.bottom - resHeight) <<16;

	return;
}
void XeLevel::LockCamera()
{
	borderLock = border;
	border.left = cameraX>>16;
	border.top = cameraY>>16;
	border.right = border.left + resWidth;
	border.bottom = border.top + resHeight;
}
void XeLevel::UnlockCamera()
{
	border = borderLock;
}

void XeLevel::PlaceObjects()
{
	ObjectContainer *container;
#ifdef DEBUG
	if (objectPlacement.header.count >= OBJECT_COUNT)
	{
		con.Log(DEBUG_LEVEL_ERROR, "objectcount (%03X) >= maximum obj count (%03X)", objectPlacement.header.count, OBJECT_COUNT);
		// Dopo di questo il gioco crasherà sicuro al 99%
	}
#endif
	for(int i=0; i<objectPlacement.header.count; i++)
	{
		OBPEntry *entry = &objectPlacement.entries[i];
		if (LoadObject(entry->id) != 0)
		{
			container = SelectObject(entry->id);
			object[i] = CreateObject(entry->id);
			object[i]->AttachLevel(this);
			object[i]->SetTexture(&container->texture);
			object[i]->x = entry->x<<16;
			object[i]->y = entry->y<<16;
			object[i]->z = entry->priority ? 2.5f : 0.5f;
			object[i]->sizeWidth = entry->width;
			object[i]->sizeHeight = entry->height;
			object[i]->Animation.SetAnimation(&container->animation);
			object[i]->Animation.SetAnimationIndex(0x0000);

			if (i == 0)
				object[i]->TakeLevelControl();
		}
	}

	if (objectPlacement.header.count == 0)
	{
		// Se non c'è alcun oggetto, ne carica uno di default (DEBUG ONLY)
		const ushort defaultobj = 0x000F;
		con.Log(DEBUG_LEVEL_WARNING, "objectcount == 0. Loading default object %04X.", defaultobj);
		if (LoadObject(defaultobj))
		{
			container = SelectObject(defaultobj);
			object[0] = CreateObject(defaultobj);
			object[0]->AttachLevel(this);
			object[0]->SetTexture(&container->texture);
			object[0]->x = 0x0060<<16;
			object[0]->y = 0x0290<<16;
			object[0]->sizeWidth = 16;
			object[0]->sizeHeight = 16;
			object[0]->Animation.SetAnimation(&container->animation);
			object[0]->Animation.SetAnimationIndex(0x0000);
			object[0]->TakeLevelControl();
		}
	}
}
void XeLevel::DestroyObject(XeObject *o)
{
	for(int i=0; i<OBJECT_COUNT; i++)
	{
		if (object[i] == o)
		{
			if (mainobject == o)
			{
				mainobject = NULL;
			}
			delete object[i];
			object[i] = NULL;
			return;
		}
	}
}