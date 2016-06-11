// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "AnimNotify/CameraEffectNotifyState.h"
#include "PandaGameInstance.h"
#include "PandaUtils.h"

UCameraEffectNotifyState::UCameraEffectNotifyState()
{
	speed = 0.f;
}
void UCameraEffectNotifyState::NotifyBegin(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float TotalDuration)
{
	Received_NotifyBegin(MeshComp, Animation, TotalDuration);
	switch (CameraType)
	{
	case emCameraType::ManJingTou:
		if (UPandaGameInstance::Instance())
		{
			UGameplayStatics::SetGlobalTimeDilation(UPandaGameInstance::Instance(), speed);
		}
		break;
	case emCameraType::DouDong:
		if (UPandaGameInstance::Instance())
		{
			APlayerController* cont = UPandaUtils::GetLocalPlayerController(UPandaGameInstance::Instance());
			if (cont && myCameraShake)
			{
				//Cast<UCameraShake>(myCameraShake->GetDefaultObject())->OscillationDuration = ShakeTime;
				//Cast<UCameraShake>(myCameraShake->GetDefaultObject())->OscillationBlendInTime = ShakeScope;
				//Cast<UCameraShake>(myCameraShake->GetDefaultObject())->OscillationBlendOutTime = ShakeScope;
				//Cast<UCameraShake>(myCameraShake->GetDefaultObject())->AnimPlayRate = speed;
				//Cast<UCameraShake>(myCameraShake->GetDefaultObject())->AnimScale = 1;
				//Cast<UCameraShake>(myCameraShake->GetDefaultObject())->AnimBlendInTime = speed;
				//Cast<UCameraShake>(myCameraShake->GetDefaultObject())->AnimBlendOutTime = speed;
				cont->ClientPlayCameraShake(myCameraShake);
			}
		}
		break;
	case emCameraType::MoHu:
		break;
	case emCameraType::BianSe:
		break;
	default:
		break;
	}
}

void UCameraEffectNotifyState::NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Received_NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UCameraEffectNotifyState::NotifyEnd(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation)
{
	Received_NotifyEnd(MeshComp, Animation);
	switch (CameraType)
	{
	case emCameraType::ManJingTou:
		if (UPandaGameInstance::Instance())
		{
			UGameplayStatics::SetGlobalTimeDilation(UPandaGameInstance::Instance(), 1);
		}
		
		break;
	case emCameraType::DouDong:

		break;
	case emCameraType::MoHu:
		break;
	case emCameraType::BianSe:
		break;
	default:
		break;
	}
}