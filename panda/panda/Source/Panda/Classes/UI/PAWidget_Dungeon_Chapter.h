// Fill out your copyright notice in the Description page of Project Settings.
//
//  PAWidget_Dungeon_Chapter.h
//  Panda
//  Dungeon ACT UI.
//  Created by White.tian on 2016-05-12 19:23:44.
//  Copyright (c) 2016�� White.tian All rights reserved.
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

	// �½ڵı���ͼ_ͼƬ
	UImage* Image_background_1;
	// ���½ǵ��½ڽ���ͼ_ͼƬ
	UImage* Image_background_2;

	// ����1_��ť
	UImage* Image_1;
	UImage* Image_2;
	// ����2_��ť
	UImage* Image_3;
	UImage* Image_4;
	// ����3_��ť
	UImage* Image_5;
	UImage* Image_6;
	// ����4_��ť
	UImage* Image_7;
	UImage* Image_8;
	// ����5_��ť
	UImage* Image_9;
	UImage* Image_10;

	// �����Ѷ�Easy_��ť
	UImage* Image_difficulty_1;
	UImage* Image_difficulty_2;
	// �����Ѷ�Normal_��ť
	UImage* Image_difficulty_3;
	UImage* Image_difficulty_4;
	// �����Ѷ�Hero_��ť
	UImage* Image_difficulty_5;
	UImage* Image_difficulty_6;
	// �����Ѷ�Abyss_��ť
	UImage* Image_difficulty_7;
	UImage* Image_difficulty_8;

	// ����ʣ�࿪��ʱ�䵹��ʱ_�ı�
	UTextBlock* TextBlock_21;

	// ��������1_�ı� _��Ӧ����ĸ�����ť
	UTextBlock* TextBlock_1;
	// ��������2_�ı�
	UTextBlock* TextBlock_2;
	// ��������3_�ı�
	UTextBlock* TextBlock_3;
	// ��������4_�ı�
	UTextBlock* TextBlock_4;
	// ��������5_�ı�
	UTextBlock* TextBlock_5;

	// �½�����_�ı�
	UTextBlock* TextBlock_11;
	// ������ǰѡ�е��Ѷ�_�ı�
	UTextBlock* TextBlock_12;
	// �����Ƽ��ȼ�_�ı�
	UTextBlock* TextBlock_13;
	// ��������_�ı�
	UTextBlock* TextBlock_14;
	// ��������_�ı�
	UTextBlock* TextBlock_15;
	
	// �����Ѷ�_Easy_�ı�
	UTextBlock* TextBlock_difficulty_1;
	// �����Ѷ�_Normal_�ı�
	UTextBlock* TextBlock_difficulty_2;
	// �����Ѷ�_Hero_�ı�
	UTextBlock* TextBlock_difficulty_3;
	// �����Ѷ�_Abyss_�ı�
	UTextBlock* TextBlock_difficulty_4;

public:

	/*
	*	����ʱ
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

	/* ����Index */
	int32 m_nCurrentLeftAndRightIdx;
	/* ����Index */
	int32 m_nCurrentTopAndBottomIdx;

	/* Current Dungeon Group ID, client test default = 1, ��ǰ������½�ID */
	int32 m_nCurrentDungeonGroupID;

	/* Current Dungeon ID, ��ǰѡ�еĸ�����ID */
	int32 m_nCurrentDungeonID;

	/* Current Dungeon Diffcult, default = 1    /1 ��/ 2 ��ͨ/ 3 Ӣ��/ 4 ��Ԩ, ��ǰѡ�еĸ����Ѷ� */ 
	int32 m_nCurrentDungeonDifficulty;

	/* Current Select Dungeon Data, ��ǰѡ�еĸ�����Ϣ */
	FsPADungeonData* m_CurrentDungeonData;

	/* Current Interface Show DungeonGroup Data, ��ǰ�ĸ�������Ϣ */
	FsPADungeonGroupData* m_CurrentDungeonGroupData;

	/* Current Dungeon group have all dungen counts, ��ǰ������һ���ж��ٸ����� */
	int32 m_nCurrentDungeonGroupHaveMaxDunCounts;

	/* Init current inferface */
	void InitCurrentInterface(int32 nDungeonGroupID);

	/* ���ݸ��� */
	void UpdateCurrentNeedData();
	/* ������� LR = Left And Right */
	/* ������� TB = Top And Bottom */
	void UpdateCurrentInterfaceLR();
	void UpdateCurrentInterfaceTB();

	// ����ID �� ������Ϣ_Client
	TMap<int32, FsPADungeonData> m_DungeonData;

	// ������ID �� ��������Ϣ_Client
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

	/* ����������ȡ���ͨ���½���Ϣ */
	void GetServerChapterData();

	/* ����������ȡ���ͨ�عؿ���Ϣ */
	void GetServerStageData();

	/* ����������·����½���Ϣ */
	void ParseServerChapterData();

	/* ����������·��Ĺؿ���Ϣ */
	void ParseServerStageData();

	/* ���浽�ͻ������ݽṹ�� */
	void SaveClientChapterData();

	/* ���浽�ͻ������ݽṹ�� */
	void SaveClientStageData();

	/* ����UI��ʾ���� */
	void ShowUIData();

	/* ��ȡ������Ϣ */
	void ClientReadJsonChapterData();
	void ClientReadJsonStageData();

	/* 
	*	Generated Loot Data 
	*	���ɵ�������
	*	����ؿ�ID���һ����������
	*	Parameter: state_id
	*   Return: FsPAItemData*
	*/
	TMap<int32, FsPAItemData*> GetLootDataByStageID(int32 nStageID);
};
