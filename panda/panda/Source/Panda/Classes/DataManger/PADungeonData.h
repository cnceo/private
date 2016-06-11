// Fill out your copyright notice in the Description page of Project Settings.
//
//  PADungeonData.h
//  Panda
//  
//  Created by White.tian on 2016-05-11 20:34:58.
//  Copyright (c) 2016年 White.tian All rights reserved.
//

/*
*	统一的副本概念
*	dungeon: 地牢
*	ACT:章节
*/

#pragma once
#include "PADungeonData.generated.h"


/** Center Area Data. 中间区域表.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPADungeonCenterAreaData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonCenterAreaData")
	//int32 nID;						//中间区域id
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonCenterAreaData")
	TArray<int32> nNameId;				//中间区域名称

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonCenterAreaData")
	TArray<int32> nDungeonId;			//包含的副本组ID

	FsPADungeonCenterAreaData()
	{
		nNameId.Reset(0);
		nDungeonId.Reset(0);
	}
};


/** Dungeon Base Data. 副本组数据表.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPADungeonGroupData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	//int32 nID;				//章节id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonGroupData")
	int32 nNameId;								// 副本组名称_Id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonGroupData")
	int32 nType;								// 类型	 1 普通.2 精英.3 英雄.4 史诗.5 活动.6 工会副本

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonGroupData")
	int32 nDescId;								// 副本组描述_Id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonGroupData")
	int32 nLevel;								// 对话副本等级

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonGroupData")
	int32 nBackgroundImageID;					// 地图背景ID

	FsPADungeonGroupData()
		: nNameId(0)
		, nType(0)
		, nDescId(0)
		, nLevel(0)
		, nBackgroundImageID(0)
	{

	}
};

/** Stage Data. 副本数据表.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPADungeonData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	//int32 nID;								//副本id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nNameId;								//副本名称_Id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	int32 nGroupId;								//副本组id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nLevel;								//副本等级

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nDifficulty;							//副本难度

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nNeedMobility;						//消费体力

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nMapId;								//地图资源组

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nRewardExp;							//通关奖励经验（暂时不用）

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nRewardGold;							//通关奖励金币（暂时不用）

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nRewardExploit;						//增加战功（不使用）

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nRewardCourage;						//增加勇气点

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nRewardJustice;						//增加正义点

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nRewardPackId;						//掉落包id	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nNextInstanceIds;						//通关后激活下个关卡id	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nActivateInstanceId;					//上一关	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nFreeTimes;							//进入次数	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nCanBuyTimes;							//购买次数	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nPrice;								//价格

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nStar;								//副本评价

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> LimitPlayer;							//限制人数

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> RebornTimes;							//重生次数

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPADungeonData")
	TArray<int32> nBackgroundImageID;					//背景图片

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

/** Stage MonsterPosition Data. 副本英雄组表.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPAStageMonsterPositionData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageMonsterPositionData")
	//int32  nID;								//副本id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageMonsterPositionData")
	int32  nMonsterArrayID;						//怪物组id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageMonsterPositionData")
	TArray<int32> tArrPositions;				//站位

	FsPAStageMonsterPositionData()
		: nMonsterArrayID(0)
	{
		tArrPositions.Reset(0);
	}
};

/** Stage LootReward Data. 副本掉落表.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPAStageLootRewardData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	//int32 nID;									//掉落ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	int32 nNameId;									//名称

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	int32 nRewardType_Normal;						//掉落种类(怪物类型)_普通

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nItemId_Normal;					//道具ID(怪物类型)_普通

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nLoot_random_Normal;				//掉落几率(怪物类型)_普通

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	int32 nRewardType_Elite;						//掉落种类(怪物类型)_精英

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nItemId_Elite;					//道具ID(怪物类型)_精英

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nLoot_random_Elite;				//掉落几率(怪物类型)_精英

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	int32 nRewardType_BOSS;							//掉落种类(怪物类型)_BOSS

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nItemId_BOSS;						//道具ID(怪物类型)_BOSS

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nLoot_random_BOSS;				//掉落几率(怪物类型)_BOSS

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	int32 nRewardType_Activity;						//掉落种类(怪物类型)_活动

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nItemId_Activity;					//道具ID(怪物类型)_活动

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nLoot_random_Activity;			//掉落几率(怪物类型)_活动

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	int32 nRewardType_Task;							//掉落种类(怪物类型)_任务

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nItemId_Task;						//道具ID(怪物类型)_任务

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAStageLootRewardData")
	TArray<int32> nLoot_random_Task;				//掉落几率(怪物类型)_任务

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