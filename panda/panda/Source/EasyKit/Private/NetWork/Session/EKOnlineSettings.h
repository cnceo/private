// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Runtime/Online/OnlineSubsystem/Public/OnlineSessionSettings.h"

/**
 * General session settings for a Shooter game
 */
class FEKOnlineSessionSettings : public FOnlineSessionSettings
{
public:

	FEKOnlineSessionSettings(bool bIsLAN = false, bool bIsPresence = false, int32 MaxNumPlayers = 4);
	virtual ~FEKOnlineSessionSettings() {}
};

/**
 * General search setting for a Shooter game
 */
class FEKOnlineSearchSettings : public FOnlineSessionSearch
{
public:
	FEKOnlineSearchSettings(bool bSearchingLAN = false, bool bSearchingPresence = false);

	virtual ~FEKOnlineSearchSettings() {}
};

/**
 * Search settings for an empty dedicated server to host a match
 */
class FEKOnlineSearchSettingsEmptyDedicated : public FEKOnlineSearchSettings
{
public:
	FEKOnlineSearchSettingsEmptyDedicated(bool bSearchingLAN = false, bool bSearchingPresence = false);

	virtual ~FEKOnlineSearchSettingsEmptyDedicated() {}
};
