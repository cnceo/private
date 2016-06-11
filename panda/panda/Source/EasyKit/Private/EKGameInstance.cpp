// Copyright 1995-2014 Î÷É½¾Ó. All Rights Reserved.
// Created by ÉòÇ« on Oct 20, 2014

#include "EasyKit.h"
#include "EKHUDManager.h"
#include "MoviePlayer.h"
#include "Runtime/MoviePlayer/Private/DefaultGameMoviePlayer.h"
#include "EKGameInstance.h"


UEKGameInstance::UEKGameInstance(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UEKGameInstance::Init()
{

	Super::Init();

#if WITH_EDITOR
#else
	FCoreUObjectDelegates::PreLoadMap.RemoveAll(FDefaultGameMoviePlayer::Get().Get());
#endif

}

void UEKGameInstance::PostInit()
{
	FEKGameFrame::Instance()->ProcedureManager()->SetWorld(GWorld);
}

void UEKGameInstance::InitGameProcedure()
{

}

void UEKGameInstance::InitNetwork()
{

}