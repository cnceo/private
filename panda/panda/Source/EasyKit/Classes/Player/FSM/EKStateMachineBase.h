//
// EKStateMachineBase.h
//
// 状态机中的状态（角色的状态 一般是指行为）基类
//
// Created by  EasyKit Team's xsj Games, Inc.
// Copyright (c) 2014-2017 Yinjunxu. All Rights Reserved. 
// time 2014/07/16

#pragma once

#include "EKStateMachineManager.h"


class EASYKIT_API FEKStateMachineBase
{

public:

	FEKStateMachineBase(){};
	FEKStateMachineBase(Player_State::StateType inType);
	FEKStateMachineBase(class FEKStateMachineManager* inStateMgr);
	virtual ~FEKStateMachineBase(){};

	virtual bool Init(){ return true; };
	virtual bool Enter(){ return true; };
	virtual void Leave(){};
	virtual void Tick(float DeltaSecond){};
	virtual Player_State::StateType GetState(){ return mStatType; };

	virtual void SetType(Player_State::StateType inType){ mStatType = inType; };
	virtual void SetStaticMeshesManager(class FEKStateMachineManager* inStateMgr);
	virtual void SetPawn(class APawn* inPlayer);


	// 流逝时间
	float fElapseTime;
	APawn* mPlayer;

	Player_State::StateType mStatType;
	class FEKStateMachineManager* mStateMachineManager;

};