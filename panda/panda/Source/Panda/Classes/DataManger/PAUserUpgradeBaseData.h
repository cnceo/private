// Fill out your copyright notice in the Description page of Project Settings.
//
//  PAUserBaseData.h
//  Panda
//  
//  Created by White.tian on 16-5-6 20:09.
//  Copyright (c) 2016�� White.tian All rights reserved.
//

#pragma once
#include "CommonDefine.h"
#include "PAUserUpgradeBaseData.generated.h"

/** User Base Data. ��ɫ���������.xlsx*/
USTRUCT(BlueprintType)
struct PANDA_API FsPAUserUpgradeBaseData : public FsTableBase
{
public:
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAUserUpgradeBaseData")
	int32 nLevel;				// ��ҵȼ� = FsTableBase::nID

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAUserUpgradeBaseData")
	int32 nExperience;			// ��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAUserUpgradeBaseData")
	int32 nSumExperience;		// ��Ҫ�ܾ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAUserUpgradeBaseData")
	int32 nPower;				// ��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FsPAUserUpgradeBaseData")
	int32 nSkillPoint;			// ����ֵ����
		
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
