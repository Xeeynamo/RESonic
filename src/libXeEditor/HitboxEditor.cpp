#include "HitboxEditor.h"
#include "MainEditor.h"
#include "HitboxShape.h"

Editor::HitboxEditor::HitboxEditor(MainEditor* e) : Control(e)
{
	m_name = "Hitbox editor";

	posCollisionTexture = XeEngine::Point((float)font->GetWidth(), (float)(font->GetHeight() * 5));
	hitboxShape = new HitboxShape(e, this, 256 + font->GetWidth() * 3, font->GetHeight() * 5, MAX(font->GetWidth() * 16, font->GetHeight() * 16));
	AddControl(hitboxShape);
}

void Editor::HitboxEditor::_Draw()
{
	e->UpdateCollisions();
	XeEngine::String mapPath;
	getLevel()->BuildPath(mapPath, getLevel()->GetCurrentAct(), XeEngine::STAGEFILE_HBX);

	PrintTextAligned(0, 1, "File: %s", mapPath.ToChar());
	PrintTextAligned(0, 2, "Collision verse: %s", hitboxShape->GetVerse() ? "Wall" : "Floor");
	PrintTextAligned(0, 3, "Collision ID %02X ", hitboxShape->GetIndex());

	e->GetCollisionTexture()->Draw(posCollisionTexture, hitboxShape->GetVerse() ? 1 : 0);

	const char* text = "0123465789ABCDEF";
	Position cpos = hitboxShape->getPosition();
	Size csize = hitboxShape->getSize();
	Position cdst1;
	Position cdst2;
	u8 space = csize.width / 16;

	cdst1 = Position(cpos.x, cpos.y - font->GetHeight() - 2);
	cdst2 = Position(cpos.x, cpos.y + csize.height + 2);
	for(u8 i = 0; i < 16; i++)
	{
		PrintChar(cdst1.x + i * space, cdst1.y, text[i]);
		PrintChar(cdst2.x + i * space, cdst2.y, text[i]);
	}
	cdst1 = Position(cpos.x - font->GetWidth() - 2, cpos.y);
	cdst2 = Position(cpos.x + csize.width + 2, cpos.y);
	for(u8 i = 0; i < 16; i++)
	{
		PrintChar(cdst1.x, cdst1.y + i * space, text[i]);
		PrintChar(cdst2.x, cdst2.y + i * space, text[i]);
	}
}
bool Editor::HitboxEditor::_InputKeyb(int key)
{
	return false;
}
bool Editor::HitboxEditor::_InputChar(int character)
{
	return false;
}
bool Editor::HitboxEditor::_InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
{
	switch(button)
	{
	case XeEngine::MouseInput_LEFT:
		{
			u16 hbxSelectorX = x - (u16)posCollisionTexture.x;
			u16 hbxSelectorY = y - (u16)posCollisionTexture.y;
			if (hbxSelectorX >= 0 && hbxSelectorX < 256 &&
				hbxSelectorY >= 0 && hbxSelectorY < 256)
			{
				hitboxShape->SetIndex((hbxSelectorX / 16) | (hbxSelectorY & 0xF0));
				return true;
			}
		}
		break;
	}
	return false;
}