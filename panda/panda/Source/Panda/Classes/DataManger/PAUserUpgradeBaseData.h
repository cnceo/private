// Fill out your copyright notice in the Description page of Project Settings.
//
//  PAUserBaseData.h
//  Panda
//  
//  Created by White.tian on 16-5-6 20:09.
//  Copyright (c) 2016年 White.tian All rights reserved.
//

#pragma once
#include "CommonDefine.h"
#include "PAUserUpgradeBaseData.generated.h"

/** User Base Data. 角色升级经验表.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPAUserUpgradeBaseData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAUserUpgradeBaseData")
	int32 nLevel;				// 玩家等级 = FsTableBase::nID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAUserUpgradeBaseData")
	int32 nExperience;			// 升级经验

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAUserUpgradeBaseData")
	int32 nSumExperience;		// 需要总经验

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAUserUpgradeBaseData")
	int32 nPower;				// 体力上限

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAUserUpgradeBaseData")
	int32 nSkillPoint;			// 悟性值上限
		
	FsPAUserUpgradeBaseData()
		: nLevel(0)
		, nExperience(0)
		, nSumExperience(0)
		, nPower(0)
		, nSkillPoint(0)
	{

	}
};

/**
 * 
 */
class PANDA_API PAUserUpgradeBaseData
{
public:
	PAUserUpgradeBaseData();
	~PAUserUpgradeBaseData();
};
