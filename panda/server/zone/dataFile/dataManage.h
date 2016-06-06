// --------------------------------------------------------
//
// --------------------------------------------------------
#ifndef _Data_Manage_h_
#define _Data_Manage_h_
#include "CommonDefine.h"
class DataManage{
public:
	DataManage();
	void LoadItmeData();
	const dm_itemData* getItemInfo(size_t itemId);
private:
	keye::csv_file	m_config;

	std::map<size_t, dm_itemData> m_ItemDBs;
};
// --------------------------------------------------------
#endif // _DB_Manage_h_
