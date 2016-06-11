// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "Condition.generated.h"


UENUM(BlueprintType)
enum emQuestState
{
	QR_None,
	QR_Success,
	QR_Fail,
	QR_Wait,
	QR_Max
};


USTRUCT()
struct FConditionInput
{
public:
	GENERATED_USTRUCT_BODY()
		int32   m_curKillCount;
};

USTRUCT()
struct FCondition
{

	GENERATED_USTRUCT_BODY()



public:
	virtual bool DoAction(FConditionInput &input) { return false; }

};

USTRUCT()
struct FCondition_KillMonster :public FCondition
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
		int32 m_monsterId;
	UPROPERTY()
		int32 m_KillAmount;

public:
	FCondition_KillMonster()
	{
		m_KillAmount = 0;
		m_monsterId = 0;
	}
	virtual bool DoAction(FConditionInput &input) override;

};