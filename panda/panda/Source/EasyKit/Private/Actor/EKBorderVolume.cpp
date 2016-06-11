// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "EasyKit.h"
#include "EKBorderVolume.h"

AEKBorderVolume::AEKBorderVolume(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	static FName CollisionProfileName(TEXT("EKBorder"));
	GetBrushComponent()->SetCollisionProfileName(CollisionProfileName);

	bColored = true;
	BrushColor.R = 0;
	BrushColor.G = 0;
	BrushColor.B = 255;
	BrushColor.A = 255;

}

#if WITH_EDITOR

void AEKBorderVolume::LoadedFromAnotherClass(const FName& OldClassName)
{
	Super::LoadedFromAnotherClass(OldClassName);

	if(GetLinkerUE4Version() < VER_UE4_REMOVE_DYNAMIC_VOLUME_CLASSES)
	{
		static FName DynamicTriggerVolume_NAME(TEXT("DynamicTriggerVolume"));

		if(OldClassName == DynamicTriggerVolume_NAME)
		{
			GetBrushComponent()->Mobility = EComponentMobility::Movable;
		}
	}
}

#endif