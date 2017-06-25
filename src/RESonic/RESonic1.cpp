#include "RESonic1.h"
#include "../libXeEngine/Geometry.h"
#include "../libXeEngine/Shape.h"
#include "../libXeEngine/Input.h"

RESonic1::RESonic1()
{
	m_section = GameSection_NONE;
	ChangeSection(GameSection_TITLE);
}
RESonic1::~RESonic1()
{
	ChangeSection(GameSection_SHUTDOWN);
	do 
	{
		Run();
	} while (m_section != GameSection_SHUTDOWN);
}

void RESonic1::Run()
{
	Do();
	switch (m_section)
	{
	case RESonic1::GameSection_NONE:
		DestrOk();
		break;
	case RESonic1::GameSection_INTRO:
		break;
	case RESonic1::GameSection_TITLE:
		TitleScreen();
		break;
	case RESonic1::GameSection_LEVEL:
		break;
	default:
		break;
	}
	End();
}
void RESonic1::ChangeSection(GameSection section)
{
	m_sectionPending = section;
	m_state = GameState_END;
}
void RESonic1::InitOk()
{
	m_state = GameState_LOOP;
}
void RESonic1::DestrOk()
{
	m_state = GameState_INIT;
	m_section = m_sectionPending;
}