// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CameraAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class PANDA_API UCameraAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UCameraAnimNotifyState();
	static UCameraAnimNotifyState* GetCameraAnimInstance();
	void StartCameraAnim(UCameraAnim* CameraAnim);

	UFUNCTION(BlueprintCallable, Category = "CameraAnimNotifyState")
	void LocPlayCameraAnim(int id);

	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trail)
	FName CameraAnimName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Trail)
	UCameraAnim* CameraAnim;
};

