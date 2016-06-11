// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "panda.h"
#include "pandaGameMode.h"
#include "Server/PandaGameSession.h"

ApandaGameMode::ApandaGameMode()
{
}
TSubclassOf<AGameSession> ApandaGameMode::GetGameSessionClass() const
{
	return APandaGameSession::StaticClass();
}
