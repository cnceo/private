// Fill out your copyright notice in the Description page of Project Settings.
//************************************************************************
//* Desc.  to handle quest for client side & server side
//*
//* Created by ZP
//************************************************************************
#pragma once

#include "Object.h"
#include "System/Quest/Condition/Condition.h"
#include "CommonDefine.h"
#include "QuestManager.generated.h"




UENUM()
enum emTaskTypeDefine
{
	TTD_None,
	TTD_KillMonster,
	TTD_Dialogue,
	TTD_ItemCollection,
	TTD_UseItem,
	TTD_AnswerQuestion,
	TTD_Protected,
	TTD_Max
};


UENUM()
enum emTaskProgress
{
	TP_None,
	TP_Max
};


USTRUCT()
struct FPrecondition
{
	GENERATED_USTRUCT_BODY()

public:
	FPrecondition() :
		LevelLimit(0)
	{
	}
	UPROPERTY()
		int32 LevelLimit;
	//preset PROPERTYS
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "QuestPresetCondition", meta = (EditCondition = "m_bUseLevelLimit"))
	//	int32 m_nLevelLimit;
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, category = "QuestPresetCondition")
	//	bool m_bUseLevelLimit;
};


USTRUCT()
struct FPropertyAdd
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
		int PropertyType;
	UPROPERTY()
		int ValueType;
	UPROPERTY()
		int BaseValue;
	UPROPERTY()
		int GrowValue;
	FPropertyAdd()
	{

	}

};
USTRUCT()
struct FTestMyStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY()
		int id;
	UPROPERTY()
		int Position;
	UPROPERTY()
		FString Desc;
	UPROPERTY()
		bool bEquip;
	UPROPERTY()
		TArray<int> Items;
	UPROPERTY()
		float GrowCritRate;
	UPROPERTY()
		float BaseDamageBack;
	UPROPERTY()
		float GrowDamageBack;
	UPROPERTY()
		TArray<FPropertyAdd> PropertyAdd;
	FTestMyStruct()
	{

	}


};
/**
 *
 */
UCLASS()
class PANDA_API UQuestManager : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY()
		TArray<FPrecondition>  m_Preconditions;
	//UPROPERTY()
	//	TArray<FCondition>  m_Conditions;
	UPROPERTY()
		TArray<FsTaskInfo> m_TaskInfos;


public:
	void Init();

	void GetDatafromJson();

	void addTask();



};
