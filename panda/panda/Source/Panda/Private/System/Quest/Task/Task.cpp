// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "System/Quest/Task/Task.h"
#include "UnrealType.h"

UTask::UTask(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	CompleteValue = 0;
}


void UTask::InitDefaults(int TaskId, FsTaskInfo info)
{
	m_TaskId = TaskId;

	m_conKillMonster.m_KillAmount = 0;
	m_TaskType = emTaskTypeDefine::TTD_KillMonster;

}

bool UTask::IsSupportedForNetworking() const
{
	bool ret = Super::IsSupportedForNetworking();
	return true;
}

//-----replicated
void UTask::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// only to local owner: weapon change requests are locally instigated, other clients don't need it
	DOREPLIFETIME_CONDITION(UTask, m_TaskId, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UTask, m_ConditionId, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UTask, m_PreconditionId, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UTask, m_emTaskProgress, COND_OwnerOnly);

	//DOREPLIFETIME(UQuestComponent, m_TaskContainer);

}