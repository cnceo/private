// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.


#pragma once
#include "EKSceneCameraVolume.generated.h"

UCLASS()
class AEKSceneCameraVolume : public AVolume
{
	GENERATED_UCLASS_BODY()

	// Begin UObject interface.
#if WITH_EDITOR
	virtual void LoadedFromAnotherClass(const FName& OldClassName) override;

	//UPROPERTY(Category = Movement, VisibleAnywhere, BlueprintReadOnly)
	//TSubobjectPtr<class UMovementComponent> MovementComponent;

#endif // WITH_EDITOR	
	// End UObject interface.

public:

	UPROPERTY(EditAnywhere)
	class ACameraActor* Camera;

	UPROPERTY(EditAnywhere)
	float CameraBlendTime;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EViewTargetBlendFunction> CameraBlendFunc;

	UPROPERTY(EditAnywhere)
	float CameraBlendExp;

	UPROPERTY(EditAnywhere)
	bool CameraLockOutgoing;

	UFUNCTION()
	virtual void SceneCameraVolumeBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
	virtual void SceneCameraVolumeEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};


