// Fill out your copyright notice in the Description page of Project Settings.
//add by yang
#pragma once

#include "PhysicsEngine/DestructibleActor.h"
#include "ActiveActorInterface.h"
#include "BaseDestructibleActor.generated.h"
/**
 * 
 */
UCLASS()
class PANDA_API ABaseDestructibleActor : public ADestructibleActor, public IActiveActorInterface
{
	GENERATED_BODY()

public:
	void OnAnimTick_Implementation(float fTime, const FString& AnimName);
	void OnAnimBegin_Implementation(float fTime, const FString& AnimName);
	void OnAnimEnd_Implementation(const FString& AnimName);
	void OnHit_Implementation(AActor* HitCauser, FsSkillHitResult sHitResult);
};
