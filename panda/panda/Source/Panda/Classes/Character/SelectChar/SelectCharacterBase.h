// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetworkingFwd.h"
#include "GameFramework/Character.h"
#include "SelectCharacterBase.generated.h"



UCLASS()
class PANDA_API ASelectCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASelectCharacterBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void InitSelectCharacter();

	proto3::PlayerInfo* m_Info;

};
