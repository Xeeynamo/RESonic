#include "LevelSelect.h"
#include "MainEditor.h"

Editor::LevelSelect::LevelSelect(MainEditor* e) : Control(e)
{
	m_name = "Level select";
	m_level = 0;
	m_act = 0;
}


void Editor::LevelSelect::_Draw()
{
	const int draw_x = 1;
	const int draw_y = 3;

	int maximumStageSelectable = MIN(getEditorHeight() / font->GetHeight() - 5, getGame()->GetStageCount() - m_level);
	if (m_level > 0)
	{
		PrintTextAligned(draw_x, draw_y - 1, "...");
	}
	for(int i = 0; i < maximumStageSelectable; i++)
	{
		XeEngine::StageProperties stage;
		getGame()->GetStageIndexProperties(stage, i + m_level);

		if (i == 0) TextColor(TEXTCOLOR_YELLOW);
		else TextColor(TEXTCOLOR_WHITE);
		PrintTextAligned(draw_x, draw_y + i, "%04X - %s", stage.id, stage.stageNameList);

		for(int j = 0; j < stage.stageActCountList; j++)
		{
			if (i == 0 && j == m_act) TextColor(TEXTCOLOR_YELLOW);
			else TextColor(TEXTCOLOR_WHITE);
			PrintTextAligned(draw_x + 32 + j * 2, draw_y + i, "%X", j + 1);
		}
	}
	TextColor(TEXTCOLOR_WHITE);
	if (maximumStageSelectable < getGame()->GetStageCount() - m_level)
		PrintTextAligned(draw_x, draw_y + maximumStageSelectable, "...");
}
bool Editor::LevelSelect::_InputKeyb(int key)
{
	switch(key)
	{
	case VK_UP:
		if (m_level > 0)
			m_level--;
		break;
	case VK_DOWN:
		if (m_level < getGame()->GetStageCount() - 1)
			m_level++;
		break;
	case VK_LEFT:
		if (m_act > 0)
			m_act--;
		break;
	case VK_RIGHT:
		{
			XeEngine::StageProperties stage;
			getGame()->GetStageIndexProperties(stage, m_level);
			if (m_act < stage.stageActCountList - 1)
				m_act++;
		}
		break;
	case VK_RETURN:
		{
			XeEngine::StageProperties stage;
			getGame()->GetStageIndexProperties(stage, m_level);
			getGame()->LoadLevel(stage.id, m_act);
			e->SetMode(0);
		}
		break;
	}
	return true;
}
bool Editor::LevelSelect::_InputChar(int character)
{
	return true;
}
bool Editor::LevelSelect::_InputMouse(u16 x, u16 y, XeEngine::MouseInput button)
{
	return true;
}