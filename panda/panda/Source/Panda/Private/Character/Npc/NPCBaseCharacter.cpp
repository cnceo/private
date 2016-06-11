// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "NPCBaseCharacter.h"

ANPCBaseCharacter::ANPCBaseCharacter()
{
	// Create monster base data component
	// BaseDataComponent = CreateDefaultSubobject<UPAMonsterHeroBaseData>(TEXT("MonsterBaseDataComponent"));

	// Init
	InitCapsuleCollsionData();

	// ...
}

void ANPCBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called to bind functionality to input
void ANPCBaseCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ANPCBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ANPCBaseCharacter::InitCapsuleCollsionData()
{
	/*TouchingActorEntryPosition = FVector::ZeroVector;*/
}

bool ANPCBaseCharacter::CheckAIParamComponentExist()
{
	return AMonsterBaseCharacter::CheckAIParamComponentExist();
}

bool ANPCBaseCharacter::CheckHaveTaskId()
{
	return AMonsterBaseCharacter::CheckHaveTaskId();
}

bool ANPCBaseCharacter::CheckNeedToCreateTaskUI()
{
	return AMonsterBaseCharacter::CheckNeedToCreateTaskUI();
}

bool ANPCBaseCharacter::CheckBNPC()
{
	return AMonsterBaseCharacter::CheckBNPC();
}

bool ANPCBaseCharacter::CheckBMonster()
{
	return AMonsterBaseCharacter::CheckBMonster();
}

int32 ANPCBaseCharacter::GetTaskId()
{
	return AMonsterBaseCharacter::GetTaskId();
}

int32 ANPCBaseCharacter::GetNPCId()
{
	return AMonsterBaseCharacter::GetNPCId();
}