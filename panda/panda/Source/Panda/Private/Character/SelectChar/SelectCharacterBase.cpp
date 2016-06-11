// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "SelectCharacterBase.h"


// Sets default values
ASelectCharacterBase::ASelectCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASelectCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASelectCharacterBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ASelectCharacterBase::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

// Called to bind functionality to input
void ASelectCharacterBase::InitSelectCharacter()
{

}