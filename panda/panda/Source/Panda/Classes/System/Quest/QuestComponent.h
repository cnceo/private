// Fill out your copyright notice in the Description page of Project Settings.
//************************************************************************
//* Desc.  to handle quest for client side & server side
//*
//* Created by ZP
//************************************************************************
#pragma once

#include "Components/ActorComponent.h"
#include "System/Quest/Task/Task.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "QuestComponent.generated.h"


//[server result]
UENUM()
enum emAcceptResult
{
	AR_None,
	AR_Success,
	AR_Fail,   //no reason just fail
	AR_Alreadyhas,   //Specific  reason
	AR_Max
};

UENUM()
enum emCommitResult
{
	CR_None,
	CR_Success,
	CR_Fail,
	CR_Max
};

 
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PANDA_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UQuestComponent();
public:
	// 当前人物身上的任务列表
	UPROPERTY(Transient, ReplicatedUsing = OnRep_UpdateContainer)
	TMap<int32, UTask*>   m_CurrentTaskContainer;

	// 已完成的人物身上的任务列表
	UPROPERTY(Transient, ReplicatedUsing = OnRep_UpdateContainer)
	TArray<int32>   m_FinishTaskContainer;

	// 任务ID 和 任务属性
	TMap<int32, FsTaskInfo> m_TaskInfo;
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//[Server tick] replicated TaskContainer manually
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;


public:

	bool HasTask(int taskId);
	bool IsTaskCompleted(int taskId);
	// 检查一下任务完成
	bool CheakTaskFinish(int taskId);
	//[Server] Add new Task to TaskContainer
	void ServerMakeTask(int taskId);
	//[Server] Delete Task from TaskContainer
	void ServerDeleteTask(int taskId);

	// 找到NPC
	void FindNPC(int inNPCID);
	// 杀死NPC
	void KillNPC(int inNPCID);
	//
	void UpdateTaskContainer(emTaskTypeDefine  TaskType);
public:
	//**********OnPropertyEvent
	UFUNCTION()
		void OnRep_UpdateContainer();

public:
	// [Server]  request Accept
	UFUNCTION(Server, Reliable, WithValidation)
		void Rpc2ServerAccept(int taskId);
	// [client]  response Accept
	UFUNCTION(Client, Reliable)
	void Rpc2ClientAccept(int taskId, emAcceptResult emAR);

	// [Server]  request update 
	UFUNCTION(Server, Reliable, WithValidation)
	void Rpc2ServerUpdate(int taskId);
	// [client]  response update
	UFUNCTION(Client, Reliable)
	void Rpc2ClientUpdate(int taskId, emAcceptResult emAR);

	// [Server]  request commit
	UFUNCTION(Server, Reliable, WithValidation)
	void Rpc2ServerCommit(int taskId);
	// [client]  response commit
	UFUNCTION(Client, Reliable)
	void Rpc2ClientCommit(int taskId, emCommitResult emCR);

};
