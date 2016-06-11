// Fill out your copyright notice in the Description page of Project Settings.
//
//  PADungeonData.h
//  Panda
//  
//  Created by White.tian on 2016-05-11 20:34:58.
//  Copyright (c) 2016�� White.tian All rights reserved.
//

/*
*	ͳһ�ĸ�������
*	dungeon: ����
*	ACT:�½�
*/

#pragma once
#include "PADungeonData.generated.h"


/** Center Area Data. �м������.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPADungeonCenterAreaData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonCenterAreaData")
	//int32 nID;						//�м�����id
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonCenterAreaData")
	TArray<int32> nNameId;				//�м���������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonCenterAreaData")
	TArray<int32> nDungeonId;			//�����ĸ�����ID

	FsPADungeonCenterAreaData()
	{
		nNameId.Reset(0);
		nDungeonId.Reset(0);
	}
};


/** Dungeon Base Data. ���������ݱ�.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPADungeonGroupData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	//int32 nID;				//�½�id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonGroupData")
	int32 nNameId;								// ����������_Id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonGroupData")
	int32 nType;								// ����	 1 ��ͨ.2 ��Ӣ.3 Ӣ��.4 ʷʫ.5 �.6 ���ḱ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonGroupData")
	int32 nDescId;								// ����������_Id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonGroupData")
	int32 nLevel;								// �Ի������ȼ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonGroupData")
	int32 nBackgroundImageID;					// ��ͼ����ID

	FsPADungeonGroupData()
		: nNameId(0)
		, nType(0)
		, nDescId(0)
		, nLevel(0)
		, nBackgroundImageID(0)
	{

	}
};

/** Stage Data. �������ݱ�.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPADungeonData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	//int32 nID;								//����id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nNameId;								//��������_Id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	int32 nGroupId;								//������id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nLevel;								//�����ȼ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nDifficulty;							//�����Ѷ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nNeedMobility;						//��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nMapId;								//��ͼ��Դ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nRewardExp;							//ͨ�ؽ������飨��ʱ���ã�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nRewardGold;							//ͨ�ؽ�����ң���ʱ���ã�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nRewardExploit;						//����ս������ʹ�ã�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nRewardCourage;						//����������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nRewardJustice;						//���������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nRewardPackId;						//�����id	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nNextInstanceIds;						//ͨ�غ󼤻��¸��ؿ�id	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nActivateInstanceId;					//��һ��	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nFreeTimes;							//�������	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nCanBuyTimes;							//�������	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nPrice;								//�۸�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nStar;								//��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> LimitPlayer;							//��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> RebornTimes;							//��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nBackgroundImageID;					//����ͼƬ

	FsPADungeonData()
		: nGroupId(0)
	{
		nNameId.Reset(0);
		nLevel.Reset(0);
		nDifficulty.Reset(0);
		nNeedMobility.Reset(0);
		nMapId.Reset(0);
		nRewardExp.Reset(0);
		nRewardGold.Reset(0);
		nRewardExploit.Reset(0);
		nRewardCourage.Reset(0);
		nRewardJustice.Reset(0);
		nRewardPackId.Reset(0);
		nNextInstanceIds.Reset(0);
		nActivateInstanceId.Reset(0);
		nFreeTimes.Reset(0);
		nCanBuyTimes.Reset(0);
		nPrice.Reset(0);
		nStar.Reset(0);
		RebornTimes.Reset(0);
		nBackgroundImageID.Reset(0);
	}
};

/** Stage MonsterPosition Data. ����Ӣ�����.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPAStageMonsterPositionData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageMonsterPositionData")
	//int32  nID;								//����id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageMonsterPositionData")
	int32  nMonsterArrayID;						//������id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageMonsterPositionData")
	TArray<int32> tArrPositions;				//վλ

	FsPAStageMonsterPositionData()
		: nMonsterArrayID(0)
	{
		tArrPositions.Reset(0);
	}
};

/** Stage LootReward Data. ���������.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPAStageLootRewardData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	//int32 nID;									//����ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	int32 nNameId;									//����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	int32 nRewardType_Normal;						//��������(��������)_��ͨ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nItemId_Normal;					//����ID(��������)_��ͨ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nLoot_random_Normal;				//���伸��(��������)_��ͨ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	int32 nRewardType_Elite;						//��������(��������)_��Ӣ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nItemId_Elite;					//����ID(��������)_��Ӣ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nLoot_random_Elite;				//���伸��(��������)_��Ӣ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	int32 nRewardType_BOSS;							//��������(��������)_BOSS

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nItemId_BOSS;						//����ID(��������)_BOSS

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nLoot_random_BOSS;				//���伸��(��������)_BOSS

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	int32 nRewardType_Activity;						//��������(��������)_�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nItemId_Activity;					//����ID(��������)_�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nLoot_random_Activity;			//���伸��(��������)_�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	int32 nRewardType_Task;							//��������(��������)_����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nItemId_Task;						//����ID(��������)_����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nLoot_random_Task;				//���伸��(��������)_����

	FsPAStageLootRewardData()
		: nNameId(0)
		, nRewardType_Normal(0)
		, nRewardType_Elite(0)
		, nRewardType_BOSS(0)
		, nRewardType_Activity(0)
		, nRewardType_Task(0)
	{
		nItemId_Normal.Reset(0);
		nLoot_random_Normal.Reset(0);
		nItemId_Elite.Reset(0);
		nLoot_random_Elite.Reset(0);
		nItemId_BOSS.Reset(0);
		nLoot_random_BOSS.Reset(0);
		nItemId_Activity.Reset(0);
		nLoot_random_Activity.Reset(0);
		nItemId_Task.Reset(0);
		nLoot_random_Task.Reset(0);
	}
};


/**
 * 
 */
class PANDA_API PACombatCopyData
{
public:
	PACombatCopyData();
	~PACombatCopyData();
};