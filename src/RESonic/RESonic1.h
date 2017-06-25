#include "..\libXeEngine\Game.h"
#include "..\libXeEngine\Model.h"
#include "..\libXeEngine\Path.h"

class RESonic1 : public XeEngine::Game
{
	enum GameState
	{
		GameState_INIT		= 0,
		GameState_LOOP		= 1,
		GameState_END		= 2,
	};
	enum GameSection
	{
		GameSection_NONE		= 0,
		GameSection_INTRO		= 1,
		GameSection_TITLE		= 2,
		GameSection_LEVEL		= 3,
		GameSection_SHUTDOWN	= 255,
	};
private:
	//! \brief Temporaney string
	XeEngine::String str;
	GameState m_state;
	GameSection m_section;
	GameSection m_sectionPending;
public:
	RESonic1();
	~RESonic1();

	//! \brief Execute the main game's core
	void Run();
	//! \brief Change the section
	void ChangeSection(GameSection);
	//! \brief Tells that the initialization is finished
	void InitOk();
	//! \brief Tells that the destruction is finished
	void DestrOk();

	//! \brief Test method
	void Test();
	//! \brief Handle the title screen
	void TitleScreen();
};