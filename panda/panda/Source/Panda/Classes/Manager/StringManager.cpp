//
//  StringManger.cpp
//  demo003
//
//  Created by White.tian on 16-2-24.
//  Copyright (c) 2016年 White.tian All rights reserved.
//

#include "panda.h"
#include "StringManager.h"
#include <set>
#include <string>

//#define _CRT_SECURE_NO_WARNINGS
static StringManager *s_pSharedStringManagerManger = NULL;

StringManager::StringManager()
{
}

StringManager::~StringManager()
{
}

bool StringManager::init()
{
    return true;
}

StringManager * StringManager::sharedStringManager()
{
    if(!s_pSharedStringManagerManger)
    {
		s_pSharedStringManagerManger = new StringManager();
		s_pSharedStringManagerManger->init();
    }
    
    return s_pSharedStringManagerManger;
}

void StringManager::purgedStringManager()
{
    //CC_SAFE_RELEASE_NULL(s_pSharedStringManagerManger);
}

int StringManager::Token(const char* pSep, char* pStr, char** buf, std::set<char*>& refset)
{
	for (char* outer = strtok_s(pStr, pSep, buf); NULL != outer; outer = strtok_s(NULL, pSep, buf))
	{
		//printf("oken: %s\n", outer);
		refset.insert(outer);
	}
	return 0;
}

int StringManager::Token(int pSep, char* pStr, std::set<std::string>& refset)
{
	char* str = pStr;
	char* pSub = strchr(str, pSep);

	char subStrBuf[128] = { '\0' };
	while (NULL != pSub)
	{
		strncpy_s(subStrBuf, str, pSub - str);	// warning C4996: 'strncpy': This function or variable may be unsafe. Consider using strncpy_s instead.
		refset.insert(subStrBuf);
		//printf("oken: %s\n", subStrBuf);
		str = pSub + 1;
		pSub = strchr(str, pSep);
	}

	if (NULL == pSub && strlen(str)>0)
	{
		strncpy_s(subStrBuf, str, strlen(str));	// warning C4996: 'strncpy': This function or variable may be unsafe. Consider using strncpy_s instead.
		refset.insert(subStrBuf);
		//printf("oken: %s\n", subStrBuf);
	}


	return 0;
}

int StringManager::Token(char ch, char* pStr, std::set<std::string>& refset)
{
	std::string str = pStr;
	int pos = str.find(ch);
	std::string subStr;
	while (-1 != pos)
	{
		subStr = str.substr(0, pos);
		refset.insert(subStr);
		//printf("oken: %s\n", subStr.c_str());
		str = str.substr(pos + 1, str.size());
		pos = str.find(ch);
	}

	if (pos == -1 && str.size()>0)
	{
		refset.insert(str);
		//printf("oken: %s\n", str.c_str());
	}

	return 0;
}