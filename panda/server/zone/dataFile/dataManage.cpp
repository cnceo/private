#include "stdafx.h"
#include "dataManage.h"
#include "ZoneServerFwd.h"
using namespace proto3;

DataManage::DataManage()
{
	LoadItmeData();
}
void DataManage::LoadItmeData()
{
	dm_itemData itemDb;
	itemDb.nID = 1001;
	itemDb.name = "danGao";
	m_ItemDBs.insert(std::make_pair(1001, itemDb));
}
const dm_itemData* DataManage::getItemInfo(size_t itemId)
{
	std::map<size_t, dm_itemData>::iterator it = m_ItemDBs.find(itemId);
	if (it != m_ItemDBs.end())
	{
		return &it->second;
	}
	return nullptr;
	
}