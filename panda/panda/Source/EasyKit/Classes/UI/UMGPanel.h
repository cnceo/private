//
// GameData.h
//
// ���ݱ� ���ݵ�Ԫ
//
// Created by  EasyKit Team's Geometry Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
//

#pragma once



// WidgetWindow�����ݽṹ
class EASYKIT_API FUMGPanel
{

public:

	FUMGPanel();
	~FUMGPanel();

	virtual void Init();

	// WidgetWindow ·��
	FString sWidgetPath;

	// WidgetWindow ������
	FString sWidgetName;

	bool bAotoGC;

	// ���⼶�� ͬ������л��� (��ʱ ��ͬ���𲻻��⣩
	int nMutexLevel;

	// WidgetWindow ����
	class UUserWidget* Window;


};


