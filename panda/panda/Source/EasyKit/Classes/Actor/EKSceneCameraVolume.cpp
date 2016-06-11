// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "EasyKit.h"
#include "EKSceneCameraVolume.h"

AEKSceneCameraVolume::AEKSceneCameraVolume(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	static FName CollisionProfileName(TEXT("EKSceneCamera"));
	GetBrushComponent()->SetCollisionProfileName(CollisionProfileName);

	if (GetBrushComponent() != nullptr)
	{
		// set up a notification for when this component hits something blocking
		GetBrushComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEKSceneCameraVolume::SceneCameraVolumeBeginOverlap);
		GetBrushComponent()->OnComponentEndOverlap.AddDynamic(this, &AEKSceneCameraVolume::SceneCameraVolumeEndOverlap);
	}

	bColored = true;
	BrushColor.R = 0;
	BrushColor.G = 0;
	BrushColor.B = 255;
	BrushColor.A = 255;


	CameraBlendTime = 1.0f;
	CameraBlendFunc = EViewTargetBlendFunction::VTBlend_Linear;
	CameraBlendExp = 0.0;
	CameraLockOutgoing = false;
}

#if WITH_EDITOR

void AEKSceneCameraVolume::LoadedFromAnotherClass(const FName& OldClassName)
{
	Super::LoadedFromAnotherClass(OldClassName);

	if (GetLinkerUE4Version() < VER_UE4_REMOVE_DYNAMIC_VOLUME_CLASSES)
	{
		static FName DynamicTriggerVolume_NAME(TEXT("DynamicTriggerVolume"));

		if (OldClassName == DynamicTriggerVolume_NAME)
		{
			GetBrushComponent()->Mobility = EComponentMobility::Movable;
		}
	}
}

#endif

void AEKSceneCameraVolume::SceneCameraVolumeBeginOverlap( class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && Camera != nullptr)
	{
		AEKCharacter* character = Cast<AEKCharacter>(OtherActor);
		if (character != nullptr)
		{
			class APlayerController* PC = Cast<class APlayerController>(character->Controller);
			if (character->Controller != nullptr  && PC != nullptr)
			{
				AEKPlayerCameraManager* CameraMgr = Cast<AEKPlayerCameraManager>(PC->PlayerCameraManager);
				if (CameraMgr != nullptr)
				{
					// 临时这个做 先
					CameraMgr->AddSceneCamera(Camera);

					FViewTargetTransitionParams TransitionParams;
					TransitionParams.BlendTime = CameraBlendTime;
					TransitionParams.BlendFunction = CameraBlendFunc;
					TransitionParams.BlendExp = CameraBlendExp;
					TransitionParams.bLockOutgoing = CameraLockOutgoing;

					CameraMgr->SetViewTarget(Camera, TransitionParams);
				}
			}
		}
	}
}

void AEKSceneCameraVolume::SceneCameraVolumeEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && Camera != nullptr)
	{
		AEKCharacter* character = Cast<AEKCharacter>(OtherActor);
		if (character != nullptr)
		{
			class APlayerController* PC = Cast<class APlayerController>(character->Controller);
			if (character->Controller != nullptr  && PC != nullptr)
			{
				AEKPlayerCameraManager* CameraMgr = Cast<AEKPlayerCameraManager>(PC->PlayerCameraManager);
				if (CameraMgr != nullptr)
				{
					// 临时这个做 先
					CameraMgr->RemoveSceneCamera(Camera);

					FViewTargetTransitionParams TransitionParams;
					TransitionParams.BlendTime = CameraBlendTime;
					TransitionParams.BlendFunction = CameraBlendFunc;
					TransitionParams.BlendExp = CameraBlendExp;
					TransitionParams.bLockOutgoing = CameraLockOutgoing;

					CameraMgr->SetViewTarget(character, TransitionParams);
				}
			}
		}
	}
}


