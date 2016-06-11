// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameSession.h"
#include "PandaGameSession.generated.h"

class APandaSpawnHelper;
/**
 * 
 */
UCLASS()
class PANDA_API APandaGameSession : public AGameSession
{
	GENERATED_BODY()
public:
	APandaSpawnHelper*	spawnHelper;
public:
	virtual FString	ApproveLogin(const FString& Options);
	virtual void	PostLogin(APlayerController* NewPlayer);
	virtual void	NotifyLogout(const APlayerController* PC);
};
