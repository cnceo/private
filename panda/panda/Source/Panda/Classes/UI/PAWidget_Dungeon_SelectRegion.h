// Fill out your copyright notice in the Description page of Project Settings.
//
//  PAWidget_Dungeon_SelectRegion.h
//  Panda
//  Dungeon Select Region UI.
//  Created by White.tian on 2016-05-12 19:23:44.
//  Copyright (c) 2016�� White.tian All rights reserved.
//
#pragma once

#include "UI/PandaWidget.h"
#include "PADungeonData.h"
#include "PAWidget_Dungeon_SelectRegion.generated.h"

/**
 * 
 */
UCLASS()
class PANDA_API UPAWidget_Dungeon_SelectRegion : public UPandaWidget
{
	GENERATED_BODY()

public:
	/*
	*	Key Down
	*/
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void UpdateSelf(float deltaTime) override;

	// Exit
	virtual void OnCross() override;
	// Enter
	virtual void OnCircle() override;
	// left, right, up, down
	virtual void OnLeft() override;
	virtual void OnRight() override;
	virtual void OnUp() override;
	virtual void OnDown() override;
public:

	/*
	*	Data
	*/

	void InitData();

	/* left or right target */
	bool m_bLeft;
	bool m_bRight;
	/* Left Index */
	int32 m_nCurrentLeftIdx;
	/* Right Index */
	int32 m_nCurrentRightIdx;

	/* Init current inferface */
	void InitCurrentInterface(int32 nDungeonGroupID);

	/* ���ݸ��� */
	void UpdateCurrentNeedData();
	/* ������� LR = Left And Right */
	/* ������� TB = Top And Bottom */
	void UpdateCurrentInterfaceLR();
	void UpdateCurrentInterfaceTB();
	
	// �м�����ID �� �м�������Ϣ_Client
	TMap<int32, FsPADungeonCenterAreaData> m_DungeonCenterAreaData;

	// ������ID �� ��������Ϣ_Client
	TMap<int32, FsPADungeonGroupData> m_CurrentDungeonGroupData;
public:

	/*
	*	UI Controllers
	*/

	/* Parse UI Controllers */
	void ParseUIControllers();

	// ����ͼ_ͼƬ
	UImage* Image_background_1;
	// ����ͼ_ͼƬ
	UImage* Image_background_2;
	// ������ʾ_ͼƬ
	UImage* Image_KeyTips;

	// ��������1_�ı� (Mirkwood   LV.15)
	UTextBlock* TextBlock_11;
	// ��������2_�ı� (Mirkwood   LV.15)
	UTextBlock* TextBlock_12;
	// ��������3_�ı� (Mirkwood   LV.15)
	UTextBlock* TextBlock_13;
	// ��������4_�ı� (Mirkwood   LV.15)
	UTextBlock* TextBlock_14;
	// ��������5_�ı� (Mirkwood   LV.15)
	UTextBlock* TextBlock_15;

	// Region dungeons
	UTextBlock* TextBlock_5;

	// �м�����List_������
	UScrollBox* ScrollBox_RegionList_Left;

	// �м�����List_������
	UScrollBox* ScrollBox_RegionList_Right;

	// ����_�ı�
	UTextBlock* TextBlock_TipsName;
};