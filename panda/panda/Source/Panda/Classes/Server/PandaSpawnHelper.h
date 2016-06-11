// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PandaSpawnHelper.generated.h"

UCLASS(Blueprintable)
class PANDA_API APandaSpawnHelper : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Parameters)
		float	spawnGap=100;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Parameters)
		AActor*	spawnPoint;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=Parameters)
		TArray<AActor*> spawnArray;

public:	
	// Sets default values for this actor's properties
	APandaSpawnHelper();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
