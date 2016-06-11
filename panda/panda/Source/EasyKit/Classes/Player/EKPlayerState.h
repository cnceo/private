//
// EKPlayerState.h
//
// ��ɫ״̬����ɫ��״̬ ��һ����״̬�� ������״̬���У�
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

	/* �������� ��һ��Ϊ״̬�� **/
	bool CreateStateMachine(FString inStateName = "DefaultStateMachine");
	void AddState(Player_State::StateType inType, FEKStateMachineBase* inState, FString inStateName = "DefaultStateMachine");


	/* ǿ��ע�� �� ���Key���� �ò��������� ״̬�������� �������������� **/
	FEKStateMachineManager* GetFSMManager(FString inName = "DefaultStateMachine");

	void Init();
	void Init(class APawn* inPlayer);
	virtual void Tick(float DeltaSecond);

	virtual bool IsTickable()const{ return true; };
	/** return the stat id to use for this tickable **/
	virtual TStatId GetStatId()const{ return nullptr; };

	/* ���ý�ɫ ��Ϊ���ܻ���״̬����ı����� **/
	void SetPawn(class APawn* inPlayer);
	void SetDefaultState(Player_State::StateType inType, FString inStateName = "DefaultStateMachine");
	void SetDefaultState(FEKStateMachineBase* inState, FString inStateName = "DefaultStateMachine");

private:
	/* �ڶ���Ϊ״̬���� **/
	bool InitSequenceState(){ return true; };
	void AddSequence(){};

	TMap<FString, FEKStateMachineManager*> StateMachineMgrMap;
};