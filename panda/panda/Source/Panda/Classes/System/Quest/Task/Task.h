// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "System/Quest/Condition/Condition.h"
#include "Manager/QuestManager.h"
#include "Task.generated.h"



struct FPrecondition;
struct FCondition;
enum emTaskProgress;



/**
 *
 */
UCLASS()
class PANDA_API UTask : public UObject
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY(Replicated)
		int  m_TaskId;
	UPROPERTY(Replicated)
		TEnumAsByte<enum emTaskProgress> m_emTaskProgress;
	UPROPERTY(Replicated)
		int m_PreconditionId;
	UPROPERTY(Replicated)
		int m_ConditionId;

	float CompleteValue;
	FCondition  m_con;
	FCondition_KillMonster m_conKillMonster;
	emTaskTypeDefine    m_TaskType;

public:
	void InitDefaults(int TaskId, FsTaskInfo info);

public:

	virtual bool IsSupportedForNetworking() const override;




};
