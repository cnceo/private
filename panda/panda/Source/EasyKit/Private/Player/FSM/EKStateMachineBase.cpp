
#include "EasyKit.h"
#include "EKCharacter.h"
#include "EKStateMachineBase.h"



FEKStateMachineBase::FEKStateMachineBase(class FEKStateMachineManager* inStateMgr)
{
	mStateMachineManager = inStateMgr;
}

FEKStateMachineBase::FEKStateMachineBase(Player_State::StateType inType)
{
	mStatType = inType;
}

void FEKStateMachineBase::SetStaticMeshesManager(class FEKStateMachineManager* inStateMgr)
{
	mStateMachineManager = inStateMgr;
}

void FEKStateMachineBase::SetPawn(class APawn* inPlayer)
{
	mPlayer = inPlayer;
}