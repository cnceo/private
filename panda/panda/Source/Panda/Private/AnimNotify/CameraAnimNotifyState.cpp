// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PandaUtils.h"
#include "PandaGameInstance.h"
#include "AnimNotify/CameraAnimNotifyState.h"



UCameraAnimNotifyState* GCameraAnimNotify = nullptr;
UCameraAnimNotifyState::UCameraAnimNotifyState()
{
	GCameraAnimNotify = this;
}
UCameraAnimNotifyState* UCameraAnimNotifyState::GetCameraAnimInstance()
{
	return GCameraAnimNotify;
}

void UCameraAnimNotifyState::NotifyBegin(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float TotalDuration)
{
	 Received_NotifyBegin(MeshComp, Animation, TotalDuration);
	 
	 StartCameraAnim(CameraAnim);
}

void UCameraAnimNotifyState::NotifyTick(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Received_NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UCameraAnimNotifyState::NotifyEnd(class USkeletalMeshComponent * MeshComp, class UAnimSequenceBase * Animation)
{
	Received_NotifyEnd(MeshComp, Animation);
}
void UCameraAnimNotifyState::StartCameraAnim(UCameraAnim* myCameraAnim)
{
	if (UPandaGameInstance::Instance())
	{
		auto cont = UPandaUtils::GetLocalPlayerController(UPandaGameInstance::Instance());
		if (cont)
		{
			cont->PlayerCameraManager->PlayCameraAnim(myCameraAnim, 0.5);
		}
	}
}

void UCameraAnimNotifyState::LocPlayCameraAnim(int id)
{
	UObject* test = UPandaUtils::CreateAsset(TEXT("/Game/CameraAnim/skill_LuoHanQuan.skill_LuoHanQuan"));
	GCameraAnimNotify->StartCameraAnim(Cast<UCameraAnim>(test));
}
//{
//	ACameraActor* camerA = NewObject<ACameraActor>(GCameraAnimNotify, TEXT(""), RF_MarkAsRootSet);
//	camerA->K2_AttachRootComponentTo(actor->GetRootComponent());
//	FTransform transf;
//	transf.SetLocation(FVector(684, 149, 56));
//	transf.SetRotation(FQuat(0, 0, -179, 0));
//	camerA->SetActorRelativeTransform(transf);
//
//	auto cont = UPandaUtils::GetLocalPlayerController(UPandaGameInstance::Instance());
//	cont->SetViewTargetWithBlend(camerA);
//}