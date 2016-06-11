
#include "EasyKit.h"
#include "EKCharacter.h"
#include "../EKPlayerState.h"
#include "EKStateMachineBase.h"
#include "EKStateMachineManager.h"

FEKStateMachineManager::FEKStateMachineManager() :
mPlayer(NULL),
mCurrentState(NULL),
pPlayerState(NULL),
StateMachineName("")
{

}

FEKStateMachineManager::~FEKStateMachineManager()
{

}


bool FEKStateMachineManager::ChangeState(Player_State::StateType inType)
{
	if (mCurrentState != NULL && mCurrentType != inType && mStateMap.Num()>0)
	{
		FEKStateMachineBase* InputStat = *(mStateMap.Find(inType));

		if (InputStat)
		{
			mCurrentState->Leave();
			mCurrentState = InputStat;
			mCurrentState->Enter();
			mCurrentType = inType;
		}
	}

	return true;
}

bool FEKStateMachineManager::Init()
{
	for (auto &State : mStateMap)
	{
		State.Value->Init();
	}

	return true;
}

void FEKStateMachineManager::SetPlayerState(FEKPlayerState* inPlayerState)
{
	pPlayerState = inPlayerState;
}

void FEKStateMachineManager::RegisterState(Player_State::StateType inType, class FEKStateMachineBase* inState)
{
	mStateMap.Add(inType, inState);
	inState->SetStaticMeshesManager(this);
	inState->SetPawn(mPlayer);
}

FEKStateMachineBase* FEKStateMachineManager::GetCurrentState()
{
	if (mCurrentState != NULL)
		return mCurrentState;

	return NULL;
}

void FEKStateMachineManager::SetName(FString inName)
{
	StateMachineName = inName;
}

void FEKStateMachineManager::SetPawn(APawn* inPlayer)
{
	mPlayer = inPlayer;
}

void FEKStateMachineManager::Tick(float DeltaSecond)
{
	if (mCurrentState != NULL)
		mCurrentState->Tick(DeltaSecond);
}

void FEKStateMachineManager::SetDefaultState(Player_State::StateType inType)
{
	if (mCurrentState != NULL)
		mCurrentState->Leave();

	mCurrentState = mStateMap[inType];
	mCurrentState->Enter();
	mCurrentType = inType;
}

void FEKStateMachineManager::SetDefaultState(class FEKStateMachineBase* inState)
{
	if (mCurrentState != NULL)
		mCurrentState->Leave();

	mCurrentState = inState;
	mCurrentState->Enter();
	mCurrentType = *(mStateMap.FindKey(inState));
}