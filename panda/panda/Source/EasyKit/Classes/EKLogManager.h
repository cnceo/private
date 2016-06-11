//
// EKLogManager.h
//
// 日志管理器用来对日志的等级 输入的形式做调整和管理
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma once

#include "EasyKit.h"

namespace EKLog
{
	enum LogType
	{
		Warning,
		Error,
		OutPut,
		Listening
	};

	enum LogLevel
	{
		Debug,
		Releaes,
		EasyKit,
		Shopping
	};
}


class EASYKIT_API FEKLogManager
{
public:
	~FEKLogManager();

	bool Init(){ return true; };

	//　日志类型　日志内存　字体颜色　日志等级
	void Log(EKLog::LogType inType, FString inStr, EKLog::LogLevel inLevel = EKLog::LogLevel::Debug, FColor inColor = FColor(255, 255, 255));

	// 显示类型 自上向下 还是自下向上 字体颜色 字体大小等
	void SetDisplay();

	static FEKLogManager* Instance();
private:
	FEKLogManager();

	void OutPutDisplay(){};

	// 增加一条日志到显示列表 自动排列到下一行
	void AddLogToList(FString inStr){};

	/* 日志**/
	void LogofDebug(EKLog::LogType inType, FString inStr, FColor inColor);
	void LogofEasyKit(EKLog::LogType inType, FString inStr, FColor inColor);
	void LogofReleaes(EKLog::LogType inType, FString inStr, FColor inColor);
	void LogofShopping(EKLog::LogType inType, FString inStr, FColor inColor);

	static FEKLogManager* g_pLogManager;
};
