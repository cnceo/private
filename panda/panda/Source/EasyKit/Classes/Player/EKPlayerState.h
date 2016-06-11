//
// EKPlayerState.h
//
// 角色状态（角色的状态 不一定是状态机 可能是状态序列）
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
// time 2014/07/16
#pragma once

#include "Tickable.h"
#include "FSM/EKStateMachineManager.h"
#include "FSM/EKStateMachineBase.h"


class EASYKIT_API FEKPlayerState// : public FTickableObjectBase
{

public:

	FEKPlayerState();
	virtual ~FEKPlayerState();

	/* 两种类型 第一种为状态机 **/
	bool CreateStateMachine(FString inStateName = "DefaultStateMachine");
	void AddState(Player_State::StateType inType, FEKStateMachineBase* inState, FString inStateName = "DefaultStateMachine");


	/* 强烈注意 ： 如果Key不给 得不到其他的 状态机管理器 ！！！！！！！ **/
	FEKStateMachineManager* GetFSMManager(FString inName = "DefaultStateMachine");

	void Init();
	void Init(class APawn* inPlayer);
	virtual void Tick(float DeltaSecond);

	virtual bool IsTickable()const{ return true; };
	/** return the stat id to use for this tickable **/
	virtual TStatId GetStatId()const{ return nullptr; };

	/* 设置角色 因为可能会在状态机里改变属性 **/
	void SetPawn(class APawn* inPlayer);
	void SetDefaultState(Player_State::StateType inType, FString inStateName = "DefaultStateMachine");
	void SetDefaultState(FEKStateMachineBase* inState, FString inStateName = "DefaultStateMachine");

private:
	/* 第二种为状态序列 **/
	bool InitSequenceState(){ return true; };
	void AddSequence(){};

	TMap<FString, FEKStateMachineManager*> StateMachineMgrMap;
};