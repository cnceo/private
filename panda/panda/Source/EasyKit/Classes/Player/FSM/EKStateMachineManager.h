//
// EKStateMachineManager.h
//
// 状态机管理器 用来切换状态 等 
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
// time 2014/07/16

#pragma once

#include "Map.h"



namespace Player_State
{
	enum StateType
	{
		EKState_Run = 0x0,
		EKState_Attack,
		EKState_Death,
		EKState_Hit,
		EKState_Idle,
		EKStat_All
	};
}


class EASYKIT_API FEKStateMachineManager
{

public:

	FEKStateMachineManager();
	virtual ~FEKStateMachineManager();

	bool ChangeState(Player_State::StateType inType);

	bool Init();
	void Tick(float DeltaSecond);
	class FEKStateMachineBase* GetCurrentState();

	void RegisterState(Player_State::StateType inType, class FEKStateMachineBase* inState);

	void SetPlayerState(class FEKPlayerState* inPlayerState);
	void SetName(FString inName);
	void SetPawn(class APawn* inPlayer);

	void SetDefaultState(Player_State::StateType inType);
	void SetDefaultState(class FEKStateMachineBase* inState);

private:

	class APawn* mPlayer;
	TMap<Player_State::StateType, class FEKStateMachineBase*> mStateMap;
	class FEKStateMachineBase* mCurrentState;
	class FEKPlayerState * pPlayerState;
	Player_State::StateType mCurrentType;

	// 状态机名称 多组状态机用来区分的Key
	FString StateMachineName;
};