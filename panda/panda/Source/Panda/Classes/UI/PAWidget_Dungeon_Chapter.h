// Fill out your copyright notice in the Description page of Project Settings.
//
//  PAWidget_Dungeon_Chapter.h
//  Panda
//  Dungeon ACT UI.
//  Created by White.tian on 2016-05-12 19:23:44.
//  Copyright (c) 2016年 White.tian All rights reserved.
//
#pragma once

#include "UI/PandaWidget.h"
#include "PADungeonData.h"
#include "PAWidget_Dungeon_Chapter.generated.h"

namespace proto3 {
	class ChapterData;
	class StageData;
	class StageLootRewardData;
};

using namespace proto3;

/**
 * 
 */
UCLASS()
class PANDA_API UPAWidget_Dungeon_Chapter : public UPandaWidget
{
	GENERATED_BODY()

public:

	/*
	*	Key Down
	*/

	UPAWidget_Dungeon_Chapter();
	UPAWidget_Dungeon_Chapter(int32 nDungeonGroupID);
	~UPAWidget_Dungeon_Chapter();

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
	*	UI Controllers
	*/

	/* Parse UI Controllers */
	void ParseUIControllers();

	// 章节的背景图_图片
	UImage* Image_background_1;
	// 右下角的章节介绍图_图片
	UImage* Image_background_2;

	// 副本1_按钮
	UImage* Image_1;
	UImage* Image_2;
	// 副本2_按钮
	UImage* Image_3;
	UImage* Image_4;
	// 副本3_按钮
	UImage* Image_5;
	UImage* Image_6;
	// 副本4_按钮
	UImage* Image_7;
	UImage* Image_8;
	// 副本5_按钮
	UImage* Image_9;
	UImage* Image_10;

	// 副本难度Easy_按钮
	UImage* Image_difficulty_1;
	UImage* Image_difficulty_2;
	// 副本难度Normal_按钮
	UImage* Image_difficulty_3;
	UImage* Image_difficulty_4;
	// 副本难度Hero_按钮
	UImage* Image_difficulty_5;
	UImage* Image_difficulty_6;
	// 副本难度Abyss_按钮
	UImage* Image_difficulty_7;
	UImage* Image_difficulty_8;

	// 副本剩余开启时间倒计时_文本
	UTextBlock* TextBlock_21;

	// 副本名称1_文本 _对应上面的副本按钮
	UTextBlock* TextBlock_1;
	// 副本名称2_文本
	UTextBlock* TextBlock_2;
	// 副本名称3_文本
	UTextBlock* TextBlock_3;
	// 副本名称4_文本
	UTextBlock* TextBlock_4;
	// 副本名称5_文本
	UTextBlock* TextBlock_5;

	// 章节名称_文本
	UTextBlock* TextBlock_11;
	// 副本当前选中的难度_文本
	UTextBlock* TextBlock_12;
	// 副本推荐等级_文本
	UTextBlock* TextBlock_13;
	// 人数限制_文本
	UTextBlock* TextBlock_14;
	// 重生次数_文本
	UTextBlock* TextBlock_15;
	
	// 副本难度_Easy_文本
	UTextBlock* TextBlock_difficulty_1;
	// 副本难度_Normal_文本
	UTextBlock* TextBlock_difficulty_2;
	// 副本难度_Hero_文本
	UTextBlock* TextBlock_difficulty_3;
	// 副本难度_Abyss_文本
	UTextBlock* TextBlock_difficulty_4;

public:

	/*
	*	倒计时
	*/

	// text var desc
	UPROPERTY(EditAnywhere)
	int32 m_CountdownTime;

	void UpdateTimeDisplay();

	void AdvanceTimer();

	UFUNCTION(BlueprintNativeEvent)
	void CountdownHasFinished();
	virtual void CountdownHasFinished_Implementation();
	FTimerHandle CountdownTimerHandle;

	UFUNCTION(BlueprintNativeEvent)
	void CountdownReset();
	virtual void CountdownReset_Implementation();
public:

	/* 
	*	Data
	*/

	/* 左右Index */
	int32 m_nCurrentLeftAndRightIdx;
	/* 上下Index */
	int32 m_nCurrentTopAndBottomIdx;

	/* Current Dungeon Group ID, client test default = 1, 当前界面的章节ID */
	int32 m_nCurrentDungeonGroupID;

	/* Current Dungeon ID, 当前选中的副本的ID */
	int32 m_nCurrentDungeonID;

	/* Current Dungeon Diffcult, default = 1    /1 简单/ 2 普通/ 3 英雄/ 4 深渊, 当前选中的副本难度 */ 
	int32 m_nCurrentDungeonDifficulty;

	/* Current Select Dungeon Data, 当前选中的副本信息 */
	FsPADungeonData* m_CurrentDungeonData;

	/* Current Interface Show DungeonGroup Data, 当前的副本组信息 */
	FsPADungeonGroupData* m_CurrentDungeonGroupData;

	/* Current Dungeon group have all dungen counts, 当前副本组一共有多少个副本 */
	int32 m_nCurrentDungeonGroupHaveMaxDunCounts;

	/* Init current inferface */
	void InitCurrentInterface(int32 nDungeonGroupID);

	/* 数据更新 */
	void UpdateCurrentNeedData();
	/* 界面更新 LR = Left And Right */
	/* 界面更新 TB = Top And Bottom */
	void UpdateCurrentInterfaceLR();
	void UpdateCurrentInterfaceTB();

	// 副本ID 和 副本信息_Client
	TMap<int32, FsPADungeonData> m_DungeonData;

	// 副本组ID 和 副本组信息_Client
	TMap<int32, FsPADungeonGroupData> m_DungeonGroupData;
public:

	/*
	*	Parse Server Data
	*/

	/* Server Data */
	proto3::ChapterData Proto3_ChapterData;
	proto3::StageData Proto3_StageData;
	proto3::StageLootRewardData Proto3_StageLootRewardData;
	void SetProto3_ChapterData(proto3::ChapterData data);
	void SetProto3_StageData(proto3::StageData data);
	void SetProto3_StageLootRewardData(proto3::StageLootRewardData data);

	/* Client Data */
	FsPADungeonGroupData Client_ChapterData;
	FsPADungeonData Client_StageData;
	FsPAStageLootRewardData Client_StageLootRewardData;
	void SetClient_ChapterData(FsPADungeonGroupData data);
	void SetClient_StageData(FsPADungeonData data);
	void SetClient_StageLootRewardData(FsPAStageLootRewardData data);

	/* 服务端请求获取玩家通关章节信息 */
	void GetServerChapterData();

	/* 服务端请求获取玩家通关关卡信息 */
	void GetServerStageData();

	/* 解析服务端下发的章节信息 */
	void ParseServerChapterData();

	/* 解析服务端下发的关卡信息 */
	void ParseServerStageData();

	/* 保存到客户端数据结构中 */
	void SaveClientChapterData();

	/* 保存到客户端数据结构中 */
	void SaveClientStageData();

	/* 设置UI显示数据 */
	void ShowUIData();

	/* 读取本地信息 */
	void ClientReadJsonChapterData();
	void ClientReadJsonStageData();

	/* 
	*	Generated Loot Data 
	*	生成掉落数据
	*	传入关卡ID输出一个掉落数组
	*	Parameter: state_id
	*   Return: FsPAItemData*
	*/
	TMap<int32, FsPAItemData*> GetLootDataByStageID(int32 nStageID);
};
