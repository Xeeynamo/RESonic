#include "StageList.h"
#include "String.h"
#include "File.h"
#include "Path.h"

XeEngine::StageList::StageList()
{
	m_entry = nullptr;
	m_properties = nullptr;
	m_count = 0;
	m_selected = 0xFFFF;
}
XeEngine::StageList::~StageList()
{
	Close();
}

void XeEngine::StageList::Close()
{
	SAFE_ADELETE(m_entry);
	SAFE_ADELETE(m_properties);
}
bool XeEngine::StageList::Open(String& filename)
{
	File file;
	if (file.Open(filename) == false)
		return false;

	Close();
	file.Read(&m_count, sizeof(m_count));
	m_entry = new StageEntry[m_count];
	file.Read(m_entry, m_count * sizeof(StageList));

	m_properties = new StageProperties[m_count];
	for(int i = 0; i < m_count; i++)
	{
		File fStageFile;
		String strStageFile(pathLevel);
		strStageFile += String(m_entry[i].name);
		strStageFile += String(extStg);
		if (fStageFile.Open(strStageFile) == true)
		{
			u8 s;
			fStageFile.Read(&s, 1);
			fStageFile.Seek(2, FILESEEK_SET);
			fStageFile.Read(&m_properties[i].stageActCountList, 2);
			fStageFile.Seek(4, FILESEEK_SET);
			fStageFile.Read(m_properties[i].stageNameList, s);
			fStageFile.Close();
		}
		else
		{
			StringCopy(m_properties[i].stageNameList, m_entry[i].name);
			m_properties[i].stageActCountList = 0;
		}
		m_properties[i].id = m_entry[i].id;
	}
	file.Close();
	return true;
}

u16 XeEngine::StageList::Count() const
{
	return m_count;
}

void XeEngine::StageList::Select(StageID stageid)
{
	if (m_entry == nullptr)
		return;

	int low, high, mid;
	low = 0;
	high = Count() - 1;

	while(low <= high)
	{
		mid = (low + high) / 2;

		if (m_entry[mid].id > stageid)
		{
			high = mid - 1;
		}
		else if (m_entry[mid].id < stageid)
		{
			low = mid + 1;
		}
		else
		{
			m_selected = mid;
			return;
		}
	}
	m_selected = 0xFFFF;
}
void XeEngine::StageList::SelectIndex(u16 index)
{
	m_selected = index >= Count() ? 0xFFFF : index;
}

bool XeEngine::StageList::GetName(char*& name)
{
	if (m_properties == nullptr)
		return false;
	if (m_selected == 0xFFFF)
		return false;
	name = m_entry[m_selected].name;
	return true;
}
bool XeEngine::StageList::GetProperties(StageProperties*& properties) const
{
	if (m_properties == nullptr)
		return false;
	if (m_selected == 0xFFFF)
		return false;
	properties = &m_properties[m_selected];
	return true;
}