//
//  StringManger.h
//  demo003
//
//  Created by White.tian on 16-2-24.
//  Copyright (c) 2016年 White.tian All rights reserved.
//

#ifndef __STRING_SPLITE__
#define __STRING_SPLITE__

#include <set>
#include <string>
#include "CCPlatformMacros.h"

#define PANDA_StringManager (StringManager::sharedStringManager())


class StringManager
{    
public:   
	StringManager();
    ~StringManager();
    bool init();
    
    static StringManager * sharedStringManager();
    static void purgedStringManager();

public:
	/*
	*	@breif 字符串拆分的三种实现方式
	*/
	int Token(const char* pSep, char* pStr, char** buf, std::set<char*>& refset); //windows，这个函数将剩余的字符串储存在buf变量中，而不是静态变量中，从而保证了安全性。
	int Token(int pSep, char* pStr, std::set<std::string>& refset);
	int Token(char ch, char* pStr, std::set<std::string>& refset);
};

#endif /* defined(__STRING_SPLITE__) */
