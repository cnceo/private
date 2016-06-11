//
// EK_HUD_Manager.h
//
// 游戏通用架构类 HUD管理器 用来负责 UMG 等各种 小组件管理
//
// Created by  EasyKit Team's Geometry Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma  once

#include "UMGPanel.h"


class EASYKIT_API FEKHUDManager
{

public:

	FEKHUDManager();
	virtual ~FEKHUDManager();

	// 读表 填充WindgetWindow
	bool Init();

	// 读表 填充WindgetWindow
	bool Init(TArray<FUMGPanel*>& inHUDTableTArry);

	// 显示一个窗口 如果没有加载先加载
	// 参数2：如果是互斥窗口 自动卸载
	bool ShowWindow(FString inWindosName, bool inAotuGC = true);
	void DestroyWindow();

	// 得到制定窗口是否显示
	bool GetWindowIsVisible(FString inWindosName);


	// 隐藏一个窗口 
	// 参数2：是否卸载
	bool HideWindow(FString inWindowName, bool bDestroy = false);

	// 隐藏所有窗口窗口 
	// 参数2：隐藏大于某个级别以上的  默认为0 全部隐藏
	void HideAllWindow(int nLevel = 0);

	// 实例化一个窗口
	UUserWidget* InstancdeUMGwidget(UObject* inObject);

	// 增加到互斥窗口
	bool AddMutexUMGWidget(class UUserWidget* inWidget);
	bool AddMutexUMGWidget(class UUserWidget* inWidget, bool isShow = false);

	// 检查创建是否互斥 如果互斥关闭其他窗口
	bool CheckMutexUMGWidget(FUMGPanel* inWindow);

	// 获得窗口
	UUserWidget* GetUMGWidget(FString inWindowName);

	// 获得窗口
	FUMGPanel* GetCurrentWidget();

	// 获得当前窗口 子窗口
	class UWidget* GetCurrentWindowChild(FString inChildName);
	// 获得当前窗口 所有子窗口
	void GetCurrentWindowAllUWidget(TArray<class UWidget*>& inWindosList);

	// 获得当前窗口所以 子窗口
	bool GetCurrentWindowAllChild(TArray<class UWidget*>& inWindosList);

	// 获得指定窗口 子窗口
	class UWidget* GetWindowChildByName(UUserWidget* inRoot, FString inChildName);
	// 获得指定窗口所以 子窗口
	bool GetWindowAllChild(UUserWidget* inRoot, TArray<class UWidget*>& inWindosList);

	bool SetWidgetEnable(FString &, bool);

private:

	// 加载一个UMG widget
	UObject* LoadUMGwidget(FString inPath);


	// 互斥窗口列表
	TMap<FString, FUMGPanel*> m_UMGWidgeMutextList;

	// 全部的窗口列表
	TMap<FString, FUMGPanel*> m_UMGWidgetAll;

	// 当前窗口
	FString CurrentWindowsName;
	FUMGPanel* CurrentWindows;
};