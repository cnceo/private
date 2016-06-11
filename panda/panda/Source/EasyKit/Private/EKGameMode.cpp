// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "EasyKit.h"
#include "EKGameMode.h"
#include "EKProcedureManager.h"
#include "EKGameFrame.h"




AEKGameMode::AEKGameMode(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FObjectFinder<UClass> PlayerPawnBPClass(TEXT("Class'/Game/Blueprints/Hero.Hero_C'"));

	//if (PlayerPawnBPClass.Object != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Object;
	//}

	// 点击暂停时 仍然Tick
	SetTickableWhenPaused(true);
}

AEKGameMode::~AEKGameMode()
{

}

void AEKGameMode::RestartPlayer(class AController* NewPlayer)
{
	// don't restart
}

APawn* AEKGameMode::SpawnDefaultPawnFor(AController* NewPlayer, AActor* StartSpot)
{
	APawn*  player = Super::SpawnDefaultPawnFor(NewPlayer, StartSpot);

	FEKGameFrame::Instance()->SceneManager()->SetLocalPlayer(Cast<AEKCharacter>(player));

	return player;
}

APlayerController* AEKGameMode::SpawnPlayerController(ENetRole RemoteRole, FVector const& SpawnLocation, FRotator const& SpawnRotation)
{
	FVector inLocation = SpawnLocation;
	FRotator inRotation = SpawnRotation;

	//for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	//{
	//	APlayerStart* Start = *It;
	//	if (Start)
	//	{
	//		inLocation = Start->GetActorLocation();
	//		inRotation = Start->GetActorRotation();
	//	}
	//}
	// 创建一个我们自己的PC 
	APlayerController* PC = Super::SpawnPlayerController(RemoteRole, SpawnLocation, SpawnRotation);
	PC->UnPossess();
	FEKGameFrame::Instance()->SceneManager()->SetController(PC);

	return PC;
}
