// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.


#pragma once
#include "EKBorderVolume.generated.h"

UCLASS()
class AEKBorderVolume : public AVolume
{
	GENERATED_UCLASS_BODY()

	// Begin UObject interface.
#if WITH_EDITOR
	virtual void LoadedFromAnotherClass(const FName& OldClassName) override;

	//UPROPERTY(Category = Movement, VisibleAnywhere, BlueprintReadOnly)
	//TSubobjectPtr<class UMovementComponent> MovementComponent;

#endif // WITH_EDITOR	
	// End UObject interface.
};



