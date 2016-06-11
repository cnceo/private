// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_CameraAnim.generated.h"


UCLASS(editinlinenew, Blueprintable, const, hidecategories = Object, collapsecategories, meta = (ShowHiddenSelfPins, DisplayName = "ATK_AnimEnd"))
class EASYKIT_API UAnimNotify_CameraAnim : public UAnimNotify
{

	GENERATED_BODY()


	void FindEKPawnBySeq(class USkeletalMeshComponent * MeshComp, class AActor* & OutActor);
	void FindEKPawnBySeq(class USkeletalMeshComponent * MeshComp, class AEKCharacter* & OutPawn);

	virtual void Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation);

	class AEKCharacter* mPawn;

	UAnimNotify_CameraAnim(const FObjectInitializer& ObjectInitializer);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TViewTarget)
	UCameraAnim* Anim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TViewTarget)
	float BlendInTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TViewTarget)
	float BlendOutTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TViewTarget)
	float PlayRate;

};