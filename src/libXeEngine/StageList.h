#pragma once
#include "XeBase.h"

namespace XeEngine
{
	typedef u16 StageID;

	struct StageEntry
	{
		StageID id;
		char name[0x0E];
	};
	struct StageProperties
	{
		StageID id;
		u8 stageActCountList;
		u8 padding;
		char stageNameList[0x3C];
	};

	class String;
	class EXPORT StageList
	{
	public:
		StageList();
		~StageList();

		//! \brief Open a stage list from a filename
		bool Open(String&);

		//! \brief Get the stage count from the opened file
		//! \returns Returns 0 if the file was not opened
		u16 Count() const;

		//! \brief Select a stage from its stage ID
		void Select(StageID);

		//! \brief Select a stage from its index (usually used by debug functins
		void SelectIndex(u16);

		//! \brief Get the stage properties
		//! \returns Returns false if no stage is currently open
		//! \details If it returns false, the param will be not modified
		bool GetName(char*&);

		//! \brief Get the stage properties
		//! \returns Returns false if no stage is currently open
		//! \details If it returns false, the param will be not modified
		bool GetProperties(StageProperties*&) const;
	private:
		StageEntry* m_entry;
		StageProperties* m_properties;
		u16 m_count;
		u16 m_selected;

		void Close();
	};
}