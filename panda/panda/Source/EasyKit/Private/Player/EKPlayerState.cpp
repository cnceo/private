
#include "EasyKit.h"
#include "EKCharacter.h"
#include "EKPlayerState.h"

FEKPlayerState::FEKPlayerState()
{

}

FEKPlayerState::~FEKPlayerState()
{
	for (auto &FSMMgr : StateMachineMgrMap)
	{
		delete FSMMgr.Value;
		FSMMgr.Value = NULL;
	}

	StateMachineMgrMap.Empty();
}

FEKStateMachineManager* FEKPlayerState::GetFSMManager(FString inName)
{
	FEKStateMachineManager * StatManager = StateMachineMgrMap[inName];

	if (StatManager != NULL)
		return StatManager;

	return NULL;
}

bool FEKPlayerState::CreateStateMachine(FString inStateName)
{
	class FEKStateMachineManager* StatrMachineMgr = new FEKStateMachineManager();

	if (StatrMachineMgr != NULL)
	{
		if (StateMachineMgrMap.Find(inStateName) == NULL)
		{
			StateMachineMgrMap.Add(inStateName, StatrMachineMgr);
		}
		else
		{
			// 转一下数量为名字
			inStateName += FString::FromInt(StateMachineMgrMap.Num());
			StateMachineMgrMap.Add(inStateName, StatrMachineMgr);
		}

		// 设置下名字
		StatrMachineMgr->SetName(inStateName);
	}
	else
		return false;

	return true;
}

void FEKPlayerState::AddState(Player_State::StateType inType, FEKStateMachineBase* inState, FString inStateName)
{
	class FEKStateMachineManager* StatrMachineMgr = *(StateMachineMgrMap.Find(inStateName));

	if (StatrMachineMgr != NULL)
	{
		StatrMachineMgr->RegisterState(inType, inState);
	}
}

void FEKPlayerState::Tick(float DeltaSecond)
{
	for (auto &FSMMgr : StateMachineMgrMap)
	{
		if (FSMMgr.Value != NULL)
			FSMMgr.Value->Tick(DeltaSecond);
	}
}

void FEKPlayerState::SetPawn(APawn* inPlayer)
{
	for (auto &FSMMgr : StateMachineMgrMap)
	{
		FSMMgr.Value->SetPawn(inPlayer);
	}
}

void FEKPlayerState::Init()
{
	for (auto &FSMMgr : StateMachineMgrMap)
	{
		FSMMgr.Value->Init();
	}
}

void FEKPlayerState::Init(APawn* inPlayer)
{
	for (auto &FSMMgr : StateMachineMgrMap)
	{
		FSMMgr.Value->SetPawn(inPlayer);
		FSMMgr.Value->Init();
	}
}

void FEKPlayerState::SetDefaultState(Player_State::StateType inType, FString inStateName)
{
	class FEKStateMachineManager* StatrMachineMgr = *(StateMachineMgrMap.Find(inStateName));

	if (StatrMachineMgr != NULL)
	{
		StatrMachineMgr->SetDefaultState(inType);
	}
}

void FEKPlayerState::SetDefaultState(FEKStateMachineBase* inState, FString inStateName)
{
	class FEKStateMachineManager* StatrMachineMgr = *(StateMachineMgrMap.Find(inStateName));

	if (StatrMachineMgr != NULL)
	{
		StatrMachineMgr->SetDefaultState(inState);
	}

}