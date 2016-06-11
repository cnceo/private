// Fill out your copyright notice in the Description page of Project Settings.
//modify by yang 20160512 怪物受击处理
#pragma once

#include "../BaseCharacter.h"
#include "CommonDefine.h"
#include "MonsterBaseCharacter.h"
#include "MonsterCharacter.generated.h"

/**
 *
 */
UCLASS(HideDropdown)
class PANDA_API AMonsterCharacter : public AMonsterBaseCharacter
{
	GENERATED_BODY()

public:
	AMonsterCharacter();
	~AMonsterCharacter();
	void OnHit_Implementation(AActor* HitCauser, FsSkillHitResult sHitResult);

public:

	virtual void Landed(const FHitResult& Hit) override;
	virtual void PlayHit(AActor* HitCauser, FsSkillHitResult sHitResult) override;
	virtual CHARACTER_SUB_STATE GetPlayHitSubState(CHARACTER_SUB_STATE emSubState) override;
	virtual void PlayDeadFly(AActor* HitCauser) override;

public:

};
