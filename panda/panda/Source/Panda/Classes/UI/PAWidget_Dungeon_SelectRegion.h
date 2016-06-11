// Fill out your copyright notice in the Description page of Project Settings.
//
//  PAWidget_Dungeon_SelectRegion.h
//  Panda
//  Dungeon Select Region UI.
//  Created by White.tian on 2016-05-12 19:23:44.
//  Copyright (c) 2016年 White.tian All rights reserved.
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

	/* 数据更新 */
	void UpdateCurrentNeedData();
	/* 界面更新 LR = Left And Right */
	/* 界面更新 TB = Top And Bottom */
	void UpdateCurrentInterfaceLR();
	void UpdateCurrentInterfaceTB();
	
	// 中间区域ID 和 中间区域信息_Client
	TMap<int32, FsPADungeonCenterAreaData> m_DungeonCenterAreaData;

	// 副本组ID 和 副本组信息_Client
	TMap<int32, FsPADungeonGroupData> m_CurrentDungeonGroupData;
public:

	/*
	*	UI Controllers
	*/

	/* Parse UI Controllers */
	void ParseUIControllers();

	// 背景图_图片
	UImage* Image_background_1;
	// 背景图_图片
	UImage* Image_background_2;
	// 按键提示_图片
	UImage* Image_KeyTips;

	// 副本名称1_文本 (Mirkwood   LV.15)
	UTextBlock* TextBlock_11;
	// 副本名称2_文本 (Mirkwood   LV.15)
	UTextBlock* TextBlock_12;
	// 副本名称3_文本 (Mirkwood   LV.15)
	UTextBlock* TextBlock_13;
	// 副本名称4_文本 (Mirkwood   LV.15)
	UTextBlock* TextBlock_14;
	// 副本名称5_文本 (Mirkwood   LV.15)
	UTextBlock* TextBlock_15;

	// Region dungeons
	UTextBlock* TextBlock_5;

	// 中间区域List_滚动条
	UScrollBox* ScrollBox_RegionList_Left;

	// 中间区域List_滚动条
	UScrollBox* ScrollBox_RegionList_Right;

	// 名称_文本
	UTextBlock* TextBlock_TipsName;
};