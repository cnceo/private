//
// GameData.h
//
// 数据表 数据单元
//
// Created by  EasyKit Team's Geometry Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma once



// WidgetWindow的数据结构
class EASYKIT_API FUMGPanel
{

public:

	FUMGPanel();
	~FUMGPanel();

	virtual void Init();

	// WidgetWindow 路径
	FString sWidgetPath;

	// WidgetWindow 窗口名
	FString sWidgetName;

	bool bAotoGC;

	// 互斥级别 同级别进行互斥 (暂时 不同级别不互斥）
	int nMutexLevel;

	// WidgetWindow 对象
	class UUserWidget* Window;


};


