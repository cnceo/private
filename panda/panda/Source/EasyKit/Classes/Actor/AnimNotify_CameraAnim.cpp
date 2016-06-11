// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "EasyKit.h"
#include "EKCharacter.h"
#include "AnimNotify_CameraAnim.h"



UAnimNotify_CameraAnim::UAnimNotify_CameraAnim(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, mPawn(NULL)
{

#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(255, 0, 0, 255);
#endif // WITH_EDITORONLY_DATA

	BlendInTime = 0.1f;
	BlendOutTime = 0.1f;
	PlayRate = 1.0f;
}

void UAnimNotify_CameraAnim::FindEKPawnBySeq(class USkeletalMeshComponent * MeshComp, class AActor* & OutActor)
{
	OutActor = MeshComp->GetTypedOuter<AActor>();
}

void UAnimNotify_CameraAnim::FindEKPawnBySeq(class USkeletalMeshComponent * MeshComp, class AEKCharacter* & OutPawn)
{
	OutPawn = MeshComp->GetTypedOuter<AEKCharacter>();
}


void UAnimNotify_CameraAnim::Notify(class USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// 通知角色攻击结束了 

	FindEKPawnBySeq(MeshComp, mPawn);

	if (mPawn == NULL)
		return;

	if (Anim)
	{
		APlayerController* pc = Cast<APlayerController>(mPawn->GetController());
			
		if (pc && pc->PlayerCameraManager)
		{
			AEKPlayerCameraManager* CameraMgr = Cast<AEKPlayerCameraManager>(pc->PlayerCameraManager);
			if (CameraMgr)
			{
				/**
				* Play the indicated CameraAnim on this camera.
				*
				* @param Anim The animation that should play on this instance.
				* @param Rate				How fast to play the animation. 1.0 is normal.
				* @param Scale				How "intense" to play the animation. 1.0 is normal.
				* @param BlendInTime		Time to linearly ramp in.
				* @param BlendOutTime		Time to linearly ramp out.
				* @param bLoop				True to loop the animation if it hits the end.
				* @param bRandomStartTime	Whether or not to choose a random time to start playing. Useful with bLoop=true and a duration to randomize things like shakes.
				* @param Duration			Optional total playtime for this animation, including blends. 0 means to use animations natural duration, or infinite if looping.
				* @param PlaySpace			Which space to play the animation in.
				* @param UserPlaySpaceRot  Custom play space, used when PlaySpace is UserDefined.
				* @return The CameraAnim instance, which can be stored to manipulate/stop the anim after the fact.
				*/
				pc->PlayerCameraManager->PlayCameraAnim(Anim, PlayRate, 1.0f, BlendInTime, BlendOutTime, false);// ClientPlayCameraAnim_Implementation();
			}
		}
		
	}



}
