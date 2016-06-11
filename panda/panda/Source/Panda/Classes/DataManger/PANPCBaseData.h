// Fill out your copyright notice in the Description page of Project Settings.
//
//  PANPCBaseData.h
//  Panda
//  Non-Player-Controlled Character Data Define
//  Created by White.tian on 16-5-9.
//  Copyright (c) 2016年 White.tian All rights reserved.
//
#pragma once
#include "CommonDefine.h"
#include "PANPCBaseData.generated.h"


/** Npc Base Data. NPC数据表.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPANPCBaseData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPANPCBaseData")
	int32 nNameId;								// npc name

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPANPCBaseData")
	int32 nCharacterBPId;						// 模型BP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPANPCBaseData")
	int32 nAnimBPId;							// 动画BP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPANPCBaseData")
	TArray<int32> nDialogeIdList;				// 对话ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPANPCBaseData")
	TArray<int32> nTaskIdList;					// 任务ID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPANPCBaseData")
	int32 nIntroductionId;						// NPC介绍文本ID

	FsPANPCBaseData()
		: nNameId(0)
		, nCharacterBPId(0)
		, nAnimBPId(0)
		, nIntroductionId(0)
	{
		nDialogeIdList.Reset(0);
		nTaskIdList.Reset(0);
	}
};


/**
 * 
 */
class PANDA_API PANPCBaseData
{
public:
	PANPCBaseData();
	~PANPCBaseData();
};
