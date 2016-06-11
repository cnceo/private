// Fill out your copyright notice in the Description page of Project Settings.

#include "panda.h"
#include "BaseDestructibleActor.h"

void ABaseDestructibleActor::OnAnimTick_Implementation(float fTime, const FString& AnimName)
{

}

void ABaseDestructibleActor::OnAnimBegin_Implementation(float fTime, const FString& AnimName)
{

}

void ABaseDestructibleActor::OnAnimEnd_Implementation(const FString& AnimName)
{

}

void ABaseDestructibleActor::OnHit_Implementation(AActor* HitCauser, FsSkillHitResult sHitResult)
{ 
	GetDestructibleComponent()->ApplyRadiusDamage(-sHitResult.nCurHP, GetActorLocation(), 32, 10, true);
}