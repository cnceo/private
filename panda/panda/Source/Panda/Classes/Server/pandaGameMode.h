// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "pandaGameMode.generated.h"

UCLASS(minimalapi,HideDropdown)
class ApandaGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ApandaGameMode();
	virtual TSubclassOf<class AGameSession> GetGameSessionClass() const;
};



