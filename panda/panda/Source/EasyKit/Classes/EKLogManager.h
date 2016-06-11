//
// EKLogManager.h
//
// ��־��������������־�ĵȼ� �������ʽ�������͹���
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

	//����־���͡���־�ڴ桡������ɫ����־�ȼ�
	void Log(EKLog::LogType inType, FString inStr, EKLog::LogLevel inLevel = EKLog::LogLevel::Debug, FColor inColor = FColor(255, 255, 255));

	// ��ʾ���� �������� ������������ ������ɫ �����С��
	void SetDisplay();

	static FEKLogManager* Instance();
private:
	FEKLogManager();

	void OutPutDisplay(){};

	// ����һ����־����ʾ�б� �Զ����е���һ��
	void AddLogToList(FString inStr){};

	/* ��־**/
	void LogofDebug(EKLog::LogType inType, FString inStr, FColor inColor);
	void LogofEasyKit(EKLog::LogType inType, FString inStr, FColor inColor);
	void LogofReleaes(EKLog::LogType inType, FString inStr, FColor inColor);
	void LogofShopping(EKLog::LogType inType, FString inStr, FColor inColor);

	static FEKLogManager* g_pLogManager;
};
