// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "System/Quest/QuestComponent.h"
#include "QuestManager.h"
#include "DataManager.h"
#include "PandaGameInstance.h"

class UActorChannel;
// Sets default values for this component's properties
UQuestComponent::UQuestComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	bReplicates = true;

	m_CurrentTaskContainer.Empty();
	m_FinishTaskContainer.Empty();
	// ...
}


// Called when the game starts
void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();

	auto gameInstance = UPandaGameInstance::Instance();
	if (gameInstance) 
	{
		for (auto& task : gameInstance->SafeGetDataManager()->m_FsTaskInfo)
		{
			// 任务ID 和 任务信息
			m_TaskInfo.Add(task.Value.TaskId, task.Value);
		}
	}
}


// Called every frame
void UQuestComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UQuestComponent::ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags)
{
	bool wroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (auto& task : m_CurrentTaskContainer)
	{
		wroteSomething |= Channel->ReplicateSubobject(task.Value, *Bunch, *RepFlags);
	}

	return wroteSomething;
}

bool UQuestComponent::HasTask(int taskId)
{
	bool ret = false;
	for (auto& task : m_CurrentTaskContainer)
	{
		if (task.Value->m_TaskId == taskId)
		{
			ret = true;
			break;
		}
	}
	return ret;
}

bool UQuestComponent::IsTaskCompleted(int taskId)
{
	bool ret = false;

	if (m_CurrentTaskContainer.Num() == 0)
		return ret;

	UTask* pinfo = nullptr;
	for (auto& task : m_CurrentTaskContainer)
	{
		if (task.Value->m_TaskId == taskId)
		{
			pinfo = task.Value;
			break;
		}
	}
	// 没有找到任务
	if (pinfo == nullptr)
		return ret;

	// 判断任务类型
	if (pinfo->CompleteValue > 99.1f)
	{
		ret = true;
	}

	return ret;
}

bool UQuestComponent::CheakTaskFinish(int taskId)
{
	bool ret = false;

	if (m_FinishTaskContainer.Num() == 0)
		return ret;

	UTask* pinfo = nullptr;
	for (auto& task : m_FinishTaskContainer)
	{
		if (task == taskId)
		{
			ret = true;
			break;
		}
	}
	// 没有找到任务
	if (pinfo == nullptr)
		return ret;

	return ret;
}

void UQuestComponent::ServerMakeTask(int taskId)
{
	FName name = *FString::Printf(TEXT("taskId_%d"), taskId);
	auto task = NewObject<UTask>(this, name, RF_MarkAsRootSet);
	if (task)
	{
		//get TaskInfoData
		FsTaskInfo infoTemp;
		FsTaskInfo* pinfo = m_TaskInfo.Find(taskId);
		if (pinfo)
		{
			infoTemp = *pinfo;
		}
		task->InitDefaults(taskId, infoTemp);
		m_CurrentTaskContainer.Add(taskId,task);
	}

}

void UQuestComponent::ServerDeleteTask(int taskId)
{
	UTask** task = m_CurrentTaskContainer.Find(taskId);
	
	if (task != nullptr)
	{
		UTask* uTask = *task;
		m_CurrentTaskContainer.Remove(taskId);
		// 加入到完成列表
		m_FinishTaskContainer.Add(taskId);

		class APlayerCharacter* player = Cast<APlayerCharacter>(GetOuter());
		if (player != nullptr)
		{
			player->AcquireQuestReward(taskId);
		}
	}
	
}

void UQuestComponent::UpdateTaskContainer(emTaskTypeDefine TaskType)
{
	for (auto &task : m_CurrentTaskContainer)
	{
		if (task.Value->m_TaskType == TaskType)
		{
			task.Value->m_conKillMonster.m_KillAmount++;
		}
	}
}

void UQuestComponent::OnRep_UpdateContainer()
{
	for (auto &task : m_CurrentTaskContainer)
	{
		UE_LOG(LogTemp, Display, TEXT("current taskid =%d"), task.Value->m_TaskId);
	}
}

//RPC Implement  accept
bool UQuestComponent::Rpc2ServerAccept_Validate(int taskId)
{
	//UE_LOG(LogTemp, Warning, TEXT("Rpc2ServerAccept_Validate questId=%d"), taskId);
	return true;
}

void UQuestComponent::Rpc2ServerAccept_Implementation(int taskId)
{
	UE_LOG(LogTemp, Display, TEXT("Request task=%d"), taskId);

	emAcceptResult  ret = emAcceptResult::AR_None;
	//check taskId in QuestManager&Database
	if (HasTask(taskId))
	{
		ret = emAcceptResult::AR_Alreadyhas;
	}else
	{
		ServerMakeTask(taskId);
		ret = emAcceptResult::AR_Success;
	}
	
	Rpc2ClientAccept(taskId, ret);
}
void UQuestComponent::Rpc2ClientAccept_Implementation(int taskId, emAcceptResult emQR)
{

	if (emQR == emAcceptResult::AR_Success)
	{
		UE_LOG(LogTemp, Display, TEXT("AcceptSuccess=%d"), taskId);
	}
	else if (emQR >= emAcceptResult::AR_Fail)
	{
		UE_LOG(LogTemp, Display, TEXT("AcceptFail=%d"), taskId);
	}

}

//RPC Implement  update
bool UQuestComponent::Rpc2ServerUpdate_Validate(int taskId)
{
	return true;
}

void UQuestComponent::Rpc2ServerUpdate_Implementation(int taskId)
{

}
void UQuestComponent::Rpc2ClientUpdate_Implementation(int taskId, emAcceptResult emQR)
{

}

//RPC Implement  commit
bool UQuestComponent::Rpc2ServerCommit_Validate(int taskId)
{
	return true;
}

void UQuestComponent::Rpc2ServerCommit_Implementation(int taskId)
{
	UE_LOG(LogTemp, Display, TEXT("CommitTask=%d"), taskId);
	emCommitResult ret = emCommitResult::CR_None;
	if (IsTaskCompleted(taskId))
	{
		ServerDeleteTask(taskId);
		ret = emCommitResult::CR_Success;
	}
	else
	{
		ret = emCommitResult::CR_Fail;
	}

	Rpc2ClientCommit(taskId, ret);
}

void UQuestComponent::Rpc2ClientCommit_Implementation(int taskId, emCommitResult emCR)
{
	if (emCR == emCommitResult::CR_Success)
	{
		UE_LOG(LogTemp, Display, TEXT("CommitTaskSuccess=%d"), taskId);
	}
	else if( emCR >= emCommitResult::CR_Fail )
	{
		UE_LOG(LogTemp, Display, TEXT("CommitTaskSuccess=%d"), taskId);
	}
}

//-----replicated
void UQuestComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// only to local owner: weapon change requests are locally instigated, other clients don't need it
	DOREPLIFETIME_CONDITION(UQuestComponent, m_CurrentTaskContainer, COND_OwnerOnly);

	//DOREPLIFETIME(UQuestComponent, m_TaskContainer);

}

// 找到NPC
void UQuestComponent::FindNPC(int inNPCID)
{
	for (auto& task : m_CurrentTaskContainer)
	{
		FsTaskInfo* taskinfo = m_TaskInfo.Find(task.Value->m_TaskId);
		// 1 是找人
		if (taskinfo->TaskType == 1)
		{
			// 找到了交付的NPC
			if (taskinfo->ConsignNPCID == inNPCID)
			{
				// 设置任务值为满
				task.Value->CompleteValue += 100;
			}
		}
	}
}

// 杀死NPC
void UQuestComponent::KillNPC(int inNPCID)
{
	for (auto& task : m_CurrentTaskContainer)
	{
		FsTaskInfo* taskinfo = m_TaskInfo.Find(task.Value->m_TaskId);

		// 2 是杀怪
		if (taskinfo->TaskType == 2)
		{
			// 找到了交付的NPC
			if (taskinfo->TargetID == inNPCID)
			{
				// 设置任务值为满
				task.Value->CompleteValue += (100.0f / (float)taskinfo->TargetNum);
			}
		}
	}
}