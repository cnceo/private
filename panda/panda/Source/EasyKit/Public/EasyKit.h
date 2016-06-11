// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#ifndef __SHOOTERGAMELOADINGSCREEN_H__
#define __SHOOTERGAMELOADINGSCREEN_H__


#include "Engine.h"
#include "SlateBasics.h"
#include "SlateCore.h"

#include "EasyKitClasses.h"

#include "ModuleInterface.h"
#include "SoundDefinitions.h"
#include "ParticleDefinitions.h"
#include "BlueprintUtilities.h"
#include "Net/UnrealNetwork.h"


//////////////////////////////////////////////////////////////////////////
#include "EKGameFrame.h"



//////////////////////////

DECLARE_LOG_CATEGORY_EXTERN(LogEasyKit, Log, All);


/** when you modify this, please note that this information can be saved with instances
* also DefaultEngine.ini [/Script/Engine.CollisionProfile] should match with this list **/
#define COLLISION_WEAPON		ECC_GameTraceChannel1
#define COLLISION_PROJECTILE	ECC_GameTraceChannel2
#define COLLISION_PIKCUP		ECC_GameTraceChannel3

#define MAX_PLAYER_NAME_LENGTH 16


#endif // __SHOOTERGAMELOADINGSCREEN_H__
