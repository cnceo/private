//
// EK_HUD_Manager.h
//
// ��Ϸͨ�üܹ��� HUD������ �������� UMG �ȸ��� С�������
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

	// ���� ���WindgetWindow
	bool Init();

	// ���� ���WindgetWindow
	bool Init(TArray<FUMGPanel*>& inHUDTableTArry);

	// ��ʾһ������ ���û�м����ȼ���
	// ����2������ǻ��ⴰ�� �Զ�ж��
	bool ShowWindow(FString inWindosName, bool inAotuGC = true);
	void DestroyWindow();

	// �õ��ƶ������Ƿ���ʾ
	bool GetWindowIsVisible(FString inWindosName);


	// ����һ������ 
	// ����2���Ƿ�ж��
	bool HideWindow(FString inWindowName, bool bDestroy = false);

	// �������д��ڴ��� 
	// ����2�����ش���ĳ���������ϵ�  Ĭ��Ϊ0 ȫ������
	void HideAllWindow(int nLevel = 0);

	// ʵ����һ������
	UUserWidget* InstancdeUMGwidget(UObject* inObject);

	// ���ӵ����ⴰ��
	bool AddMutexUMGWidget(class UUserWidget* inWidget);
	bool AddMutexUMGWidget(class UUserWidget* inWidget, bool isShow = false);

	// ��鴴���Ƿ񻥳� �������ر���������
	bool CheckMutexUMGWidget(FUMGPanel* inWindow);

	// ��ô���
	UUserWidget* GetUMGWidget(FString inWindowName);

	// ��ô���
	FUMGPanel* GetCurrentWidget();

	// ��õ�ǰ���� �Ӵ���
	class UWidget* GetCurrentWindowChild(FString inChildName);
	// ��õ�ǰ���� �����Ӵ���
	void GetCurrentWindowAllUWidget(TArray<class UWidget*>& inWindosList);

	// ��õ�ǰ�������� �Ӵ���
	bool GetCurrentWindowAllChild(TArray<class UWidget*>& inWindosList);

	// ���ָ������ �Ӵ���
	class UWidget* GetWindowChildByName(UUserWidget* inRoot, FString inChildName);
	// ���ָ���������� �Ӵ���
	bool GetWindowAllChild(UUserWidget* inRoot, TArray<class UWidget*>& inWindosList);

	bool SetWidgetEnable(FString &, bool);

private:

	// ����һ��UMG widget
	UObject* LoadUMGwidget(FString inPath);


	// ���ⴰ���б�
	TMap<FString, FUMGPanel*> m_UMGWidgeMutextList;

	// ȫ���Ĵ����б�
	TMap<FString, FUMGPanel*> m_UMGWidgetAll;

	// ��ǰ����
	FString CurrentWindowsName;
	FUMGPanel* CurrentWindows;
};