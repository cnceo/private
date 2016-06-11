// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "PACameraManager.h"
#include "PandaUtils.h"
#include "PandaGameInstance.h"
#include "MainPlayerController.h"

UPACameraManager* GCameraManager = nullptr;
UPACameraManager::UPACameraManager()
{
	GCameraManager = this;
}
UPACameraManager* UPACameraManager::GetCameraManagerInstance()
{
	return GCameraManager;
}
void UPACameraManager::PlayTaskCameraAnim(USceneComponent* pCom)
{
	if (!pCom)
	{
		UE_LOG(LogTemp, Log, TEXT("task Actor is null....."));
		return;
	}
	pCom->SetActive(true);
	//Òþ²ØÖ÷½Ç
	AMainPlayerController* contro = Cast<AMainPlayerController>(UPandaUtils::GetLocalPlayerController(UPandaGameInstance::Instance()));
	APlayerCharacter* character = contro->GetMainPlayer();
	character->SetActorHiddenInGame(true);
	//character->
	//FTransform transf;
	//transf.SetLocation(FVector(0, 190, 10));
	//transf.SetRotation(FQuat(0, 0, -90, 0));
	ACameraActor* camerA = GWorld->SpawnActor<ACameraActor>();
	//UCameraComponent* camerA = NewObject<UCameraComponent>(UCameraComponent::StaticClass());
	//camerA->AttachTo(pCom);
	camerA->K2_AttachRootComponentTo(pCom);
	//camerA->SetActorRelativeTransform(transf);
	auto cont = UPandaUtils::GetLocalPlayerController(UPandaGameInstance::Instance());
	cont->SetViewTargetWithBlend(pCom->GetOwner(),0.5);

	//camerA->Deactivate
}

void UPACameraManager::StopTaskCameraAnim(USceneComponent* pcom)
{
	if (!pcom)
	{
		UE_LOG(LogTemp, Log, TEXT("task Actor is null....."));
		return;
	}
	//ÏÔÊ¾Ö÷½Ç
	AMainPlayerController* contro = Cast<AMainPlayerController>(UPandaUtils::GetLocalPlayerController(UPandaGameInstance::Instance()));
	APlayerCharacter* character = contro->GetMainPlayer();
	character->SetActorHiddenInGame(false);

	APlayerController* cont = UPandaUtils::GetLocalPlayerController(UPandaGameInstance::Instance());
	cont->SetViewTargetWithBlend(cont->GetPawn(),0.5);
	pcom->SetActive(false);
// 	TArray<USceneComponent*> Children;
// 	pcom->GetChildrenComponents(false , Children);
// 	for (USceneComponent* chidl : Children)
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("%s"), *chidl->GetName());
// 		if (chidl->GetName() == TEXT("SceneComponent"))
// 		{
// 			ACameraActor* camer = Cast<ACameraActor>(chidl->GetOwner());
// 			if (chidl->GetOwner())
// 			{
// 				chidl->DestroyComponent();
// 				GWorld->DestroyActor(chidl->GetOwner());
// 				
// 				//camer->getActorRelativeTransform()
// 				//camer->actorrelativetrans
// 
// 			}
// 		}
// 	}
}
void UPACameraManager::PlayLocCameraAnim(int id)
{
	UCameraAnimNotifyState* Notify = UCameraAnimNotifyState::GetCameraAnimInstance();
	if (Notify)
	{
		Notify->LocPlayCameraAnim(id);
	}
}